/*
 * OpenGL_OpenGLWidget.c
 *
 * $Id: OpenGL_OpenGLWidget.c,v 1.3 1998/11/01 21:42:58 razeh Exp $
 *
 * This module implements the NT portion of the main event loop for
 * our OpenGLWidget.
 *
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com) 
 */


/* With the Cygnus tools you need to include the GL stuff first. */
#include <windows.h>
#include <GL/gl.h>

#include "cygnusFixes.h"
#include "OpenGL_OpenGLWidget.h"
#include "EventHandling.h"
#include "DCDictionary.h"
#include "ErrorHandling.h"
#include "memory.h"
#include "JNIInterface.h"
#include "SystemError.h"

CRITICAL_SECTION WidgetCriticalSection;
/* This is called to setup all of our locking methods. */
void setupWidgetLocks() 
{
  InitializeCriticalSection(&WidgetCriticalSection);
}

/* This gets a global lock on widgets. */
static void getWidgetLock()
{
  EnterCriticalSection(&WidgetCriticalSection);
}

/* This releases a global lock on widgets. */
static void releaseWidgetLock()
{
  LeaveCriticalSection(&WidgetCriticalSection);
}


static HPALETTE hPalette  = NULL;




static void
setupPixelFormat(JNIEnv *env, jobject capabilities, HDC hDC)
{
  int colorDepth = 0, alphaDepth = 0, depthBuffer = 0, stencilBuffer = 0;

  lookupIntField(env, capabilities, 
		 "colorDepth", &colorDepth);
  lookupIntField(env, capabilities, 
		 "alphaDepth", &alphaDepth);
  lookupIntField(env, capabilities, 
		 "depthBuffer", &depthBuffer);
  lookupIntField(env, capabilities,
		 "stencilBuffer", &stencilBuffer);
  {
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),  /* size */
        1,                              /* version */
        PFD_SUPPORT_OPENGL |
        PFD_DRAW_TO_WINDOW |
        PFD_DOUBLEBUFFER,               /* support double-buffering */
        PFD_TYPE_RGBA,                  /* color type */
        colorDepth,                     /* prefered color depth */
        0, 0, 0, 0, 0, 0,               /* color bits (ignored) */
        alphaDepth != 0,                /* alpha buffer */
        alphaDepth,                     /* alpha bits (ignored) */
        0,                              /* no accumulation buffer */
        0, 0, 0, 0,                     /* accum bits (ignored) */
        depthBuffer,                    /* bits per pixel --- depth buffer */
        stencilBuffer,                  /* bits per pixel --- stencil buffer */
        0,                              /* no auxiliary buffers */
        PFD_MAIN_PLANE,                 /* main layer */
        0,                              /* reserved */
        0, 0, 0,                        /* no layer, visible, damage masks */
    };

    int pixelFormat;


    pixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (pixelFormat == 0) {
      handleError(env, "OpenGL/OpenGLNativeException",
		  "ChoosePixelFormat failed");
      return;
    }

    if (SetPixelFormat(hDC, pixelFormat, &pfd) != TRUE) {
      handleError(env, "OpenGL/OpenGLNativeException",
		  "SetPixelFormat failed");
      return;
    }
  }
}




static void
setupPalette(HDC hDC)
{
    int pixelFormat = GetPixelFormat(hDC);
    PIXELFORMATDESCRIPTOR pfd;
    LOGPALETTE* pPal;
    int paletteSize;

    DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    if (pfd.dwFlags & PFD_NEED_PALETTE) {
        paletteSize = 1 << pfd.cColorBits;
    } else {
        return;
    }

    pPal = (LOGPALETTE*)
        privateMalloc(sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
    pPal->palVersion = 0x300;
    pPal->palNumEntries = paletteSize;

    /* build a simple RGB color palette */
    {
        int redMask = (1 << pfd.cRedBits) - 1;
        int greenMask = (1 << pfd.cGreenBits) - 1;
        int blueMask = (1 << pfd.cBlueBits) - 1;
        int i;

        for (i=0; i<paletteSize; ++i) {
            pPal->palPalEntry[i].peRed =
                    (((i >> pfd.cRedShift) & redMask) * 255) / redMask;
            pPal->palPalEntry[i].peGreen =
                    (((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask;
            pPal->palPalEntry[i].peBlue =
                    (((i >> pfd.cBlueShift) & blueMask) * 255) / blueMask;
            pPal->palPalEntry[i].peFlags = 0;
        }
    }

    hPalette = CreatePalette(pPal);
    privateFree(pPal);

    if (hPalette) {
        SelectPalette(hDC, hPalette, FALSE);
        RealizePalette(hDC);
    }
}


/* Set things up for OpenGL rendering in hWnd. */
static void handleWindowCreation(HWND hWnd) 
{
  HDC       currentDC            = NULL;
  HGLRC     currentGLRC          = NULL;
  JNIEnv   *widgetEnvironment    = NULL;
  jobject   widget               = NULL,
	        capabilities         = NULL;
  
  widgetEnvironment = environmentForWindow(hWnd);
  widget            = widgetForWindow(hWnd);

  if (widgetEnvironment == NULL) {
    MessageBox(hWnd, "Unable to get widget environment",  "Error", 
	       MB_ICONERROR | MB_OK);
    return;
  }

  if (widget == NULL) {
    handleError(widgetEnvironment, "OpenGL/OpenGLNativeException",
		"Unable to get widget");
    return;
  }

  /* Get the capabilities object out of our widget. */
  {
    jclass widgetClass             = NULL;
    jmethodID capabilitiesMethodID = NULL;
    widgetClass = 
      (*widgetEnvironment)->GetObjectClass(widgetEnvironment, widget);

    capabilitiesMethodID = 
      getMethodID(widgetEnvironment, widgetClass,
		"capabilities", "()LOpenGL/OpenGLCapabilities;",
		"Unable to get capabilities() method");
    if (capabilitiesMethodID) {
      capabilities = 
	(*widgetEnvironment)->CallObjectMethod(widgetEnvironment, 
					       widget, capabilitiesMethodID);
    }
  }

  currentDC = GetDC(hWnd);
  setupPixelFormat(widgetEnvironment, capabilities, currentDC);
  setupPalette(currentDC);

  log(widgetEnvironment, "In window creation\n");
  setDCForWidget(widgetEnvironment, widget, currentDC);
  
  handOffWindowActivated(widgetEnvironment, widget);
  log(widgetEnvironment, "done with window creation\n");
}



LRESULT APIENTRY
WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
  switch (message) {
#ifdef NOTINWINDOWS
    /* We should be able to handle window creation here, but we have to
       handle it in the handleWindowCreation method so that we have
       enough information to get our Java thread and widget. */
  case WM_CREATE:
    handleWindowCreation(hWnd);
    return 0;
    break;
#endif
  case WM_DESTROY:
    /* Finish up OpenGL */
    {
      HDC     currentDC;
      HGLRC   currentGLRC;
      
      currentGLRC = wglGetCurrentContext();
      currentDC   = GetWindowDC(hWnd);
     
      if (currentGLRC != NULL) {
	    wglMakeCurrent(NULL, NULL);
	    wglDeleteContext(currentGLRC);
      }
      if (hPalette) {
	DeleteObject(hPalette);
      }
      ReleaseDC(hWnd, currentDC);
      PostQuitMessage(0);
      return 0;
    }
  break;
  case WM_SIZE:
    /* track window size changes */
	{
      	int     winWidth          = (int) LOWORD(lParam);
	    int     winHeight         = (int) HIWORD(lParam);
	    JNIEnv *widgetEnvironment = environmentForWindow(hWnd);
	    jobject widget            = widgetForWindow(hWnd);
       
	    if ((widgetEnvironment != NULL) && (widget != NULL))
	      handOffWindowResized(widgetEnvironment, widget, winWidth, 
			       winHeight);
	      return 0;
    }
  break;
  case WM_PALETTECHANGED:
    /* realize palette if this is *not* the current window */
    {
      HDC     currentDC         = GetWindowDC(hWnd);
      JNIEnv *widgetEnvironment = environmentForWindow(hWnd);
      jobject widget            = widgetForWindow(hWnd);
     
      if (hPalette && (HWND) wParam != hWnd) {
		UnrealizeObject(hPalette);
		SelectPalette(currentDC, hPalette, FALSE);
		RealizePalette(currentDC);
	  if ((widgetEnvironment != NULL) && (widget != NULL)) {
		handOffWindowExposed(widgetEnvironment, widget);
		}	
      }
    }
  break;
  case WM_QUERYNEWPALETTE:
    /* realize palette if this is the current window */
    {
      JNIEnv *widgetEnvironment = environmentForWindow(hWnd);
      jobject widget            = widgetForWindow(hWnd);
     
      if (hPalette) {
    	HDC currentDC = GetWindowDC(hWnd);
       
	    UnrealizeObject(hPalette);
	    SelectPalette(currentDC, hPalette, FALSE);
	    RealizePalette(currentDC);
      if ((widgetEnvironment != NULL) && (widget != NULL)) {
	    handOffWindowExposed(widgetEnvironment, widget);
	  }
	    return TRUE;
      }
    }
  break;
  case WM_PAINT: 
    {
      JNIEnv     *widgetEnvironment = environmentForWindow(hWnd);
      jobject     widget            = widgetForWindow(hWnd);
      PAINTSTRUCT ps;
      BeginPaint(hWnd, &ps);
     
      if ((widgetEnvironment != NULL) && (widget != NULL)) {
	     handOffWindowExposed(widgetEnvironment, widget);
      } else {
	   if (widgetEnvironment == NULL)
	       MessageBox(hWnd, "no widget environment.",  "Error", 
		              MB_ICONERROR | MB_OK);

       if (widget == NULL)
	       MessageBox(hWnd, "no widget.",  "Error", 
		              MB_ICONERROR | MB_OK);

	   MessageBox(hWnd, "Unable to handoff paint event.",  "Error", 
		          MB_ICONERROR | MB_OK);
      }
     
      EndPaint(hWnd, &ps);
      return 0;
    }
  break;   

  /* A key has been pressed. */
  case WM_KEYDOWN:
    {
      JNIEnv *widgetEnvironment = environmentForWindow(hWnd);
      jobject widget            = widgetForWindow(hWnd);
     
      if ((widgetEnvironment != NULL) && (widget != NULL))
	      handOffKeyPressed(widgetEnvironment, widget, (int) wParam);
    }
  break;

  /* A key has been released. */
  case WM_KEYUP:
    {
      JNIEnv *widgetEnvironment = environmentForWindow(hWnd);
      jobject widget            = widgetForWindow(hWnd);
     
      if ((widgetEnvironment != NULL) && (widget != NULL))
		handOffKeyReleased(widgetEnvironment, widget, (int) wParam);
    }
  break;


 
  case WM_RBUTTONUP:
  case WM_LBUTTONUP:
  case WM_MBUTTONUP:
    {
      JNIEnv *widgetEnvironment = environmentForWindow(hWnd);
      jobject widget            = widgetForWindow(hWnd);
     
      if ((widget != NULL) && (widgetEnvironment != NULL)) {
		handOffMouseUp(widgetEnvironment, widget,
					   LOWORD(lParam), HIWORD(lParam));
      }
      return 0;
    }
  break;
 
 
  case WM_RBUTTONDOWN:
  case WM_LBUTTONDOWN:  
  case WM_MBUTTONDOWN:
    {
      JNIEnv *widgetEnvironment = environmentForWindow(hWnd);
      jobject widget            = widgetForWindow(hWnd);
     
      if ((widget != NULL) && (widgetEnvironment != NULL)) {
		handOffMouseDown(widgetEnvironment, widget,
						 LOWORD(lParam), HIWORD(lParam));
      }
      return 0;
    }
  break;
  case WM_MOUSEMOVE:
    {
      JNIEnv *widgetEnvironment = environmentForWindow(hWnd);
      jobject widget            = widgetForWindow(hWnd);
     
      if ((widget != NULL) && (widgetEnvironment != NULL)) {
		handOffMouseMove(widgetEnvironment, widget,
						 LOWORD(lParam), HIWORD(lParam));
      }
      return 0;
    }
  break;
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_swapBuffers
  (JNIEnv *env, jobject object)
{
  HDC currentDC = wglGetCurrentDC();
  if (currentDC != NULL)
    SwapBuffers(currentDC);
}



/* This should be called to register our window class with windows.
   If things work out fine return 0; when there are problems we return
   1. */
static int registerWindowClass(JNIEnv *env,
			       WNDCLASS wndClass, const char *className,
			       HANDLE hCurrentInst)
{
  static int callCount   = 0;

  if (callCount == 0) {
    /* register window class */
    wndClass.style         = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc   = WndProc;
    wndClass.cbClsExtra    = 0;
    wndClass.cbWndExtra    = 0;
    wndClass.hInstance     = hCurrentInst;
    wndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = NULL; // redraw our own background;
    wndClass.lpszMenuName  = NULL;
    wndClass.lpszClassName = className;
  
    if(!RegisterClass(&wndClass)) {
      handleError(env, "OpenGL/OpenGLWidgetOpenFailedException",
		  "Unable to register our window class");
      return 1;
    }
    callCount++;
  }
  return 0;
}



/* This native method handles opening up our widget. */
JNIEXPORT jboolean JNICALL
Java_OpenGL_OpenGLWidget_openOpenGLWidget(JNIEnv *env, jobject obj,
					  jint x, jint y, 
					  jint width, jint height,
					  jstring titleUTFString)
{
    WNDCLASS wndClass;
    HWND hWnd;
    HINSTANCE hCurrentInst = GetModuleHandle(NULL);
    int nCmdShow           = 1;

    int winX     = x,   winY      = y;
    int winWidth = width, winHeight = height;
    
    const char *windowName     = "";
    const char *className      = "OpenGLWidget";
    
    jboolean copy              = JNI_TRUE;
    jobject  widget            = NULL;

    /* Make sure that only one thread is trying to create a window at
       a time. */
    getWidgetLock();

    log(env, "Attempting to create widget\n");

    windowName = (*env)->GetStringUTFChars(env, titleUTFString, &copy);
    if (windowName == NULL) {
      releaseWidgetLock();
      handleError(env, "OpenGL/OpenGLNativeException",
		  "Unable to get title string for widget");
      return JNI_FALSE;
    }

    /* Register our window class. */
    if (registerWindowClass(env, wndClass, className, hCurrentInst)) {
      releaseWidgetLock();
      return JNI_FALSE;
    }

    /* create window */
    hWnd = CreateWindow(
        className, windowName,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        winX, winY, winWidth, winHeight,
        NULL, NULL, hCurrentInst, NULL);
    
    widget = (*env)->NewGlobalRef(env, obj);
    setWidgetForWindow(hWnd, env, widget);
    setEnvironmentForWindow(hWnd, env, widget);

    handleWindowCreation(hWnd);

    /* display window */
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    (*env)->ReleaseStringUTFChars(env, titleUTFString, windowName);
    log(env, "Created widget\n");

    /* Let other threads create windows. */
    releaseWidgetLock();
    return JNI_TRUE;
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_eventLoop
  (JNIEnv *env, jobject obj)
{
    MSG msg;

    log(env, "Starting event loop\n");
    /* process messages */
    while (GetMessage(&msg, NULL, 0, 0) == TRUE) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
    }
    
    log(env, "Exiting event loop\n");
}



/* This attempts to set the window title. */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_setNativeTitle
  (JNIEnv *env, jobject widget, jstring jtitle)
{
  const char *title  = NULL;
  jboolean    copy   = JNI_TRUE;
  HWND        window = NULL;

  title = (*env)->GetStringUTFChars(env, jtitle, &copy);
  if (title == NULL) {
	char *errorMessage = systemErrorMessage();
	handleError(env, "OpenGL/OpenGLNativeException", errorMessage);
	privateFree(errorMessage);
    return;
  }

  window = windowForWidget(env, widget);
  if (window != NULL) {
    SetWindowText(window, title);
  }
}





