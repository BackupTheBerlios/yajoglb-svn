/*
 * OpenGL_OpenGLWidget.c
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

void (*idleFunc)(HDC hDC);

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


HPALETTE hPalette  = NULL;

/* Get the OpenGL context for widget into the current thread. */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getOpenGLContextIntoMyThread
  (JNIEnv *env, jobject widget)
{
  /* If we already have an OpenGL context there is no reason to do
     anything. */
  if (wglGetCurrentContext() == NULL) {
    HGLRC currentGLRC;
    HDC   currentDC = getDCForWidget(env, widget);

    if (getDCForWidget(env, widget) == NULL) {
      MessageBox(WindowFromDC(currentDC), "BadDC", "Error",
		 MB_ICONERROR | MB_OK);
    }

    if (getGLRCForWidget(env, widget) == NULL) {
      MessageBox(WindowFromDC(currentDC), "BadGLRC", "Error",
		 MB_ICONERROR | MB_OK);
    }
    
    currentGLRC = wglCreateContext(currentDC);
    if (currentGLRC == NULL) {
      MessageBox(WindowFromDC(currentDC), 
		 "CreateGLContext returns NULL", "Error",
		 MB_ICONERROR | MB_OK);
    }
    
    if (wglCopyContext(getGLRCForWidget(env, widget), currentGLRC, 
		       GL_ALL_ATTRIB_BITS)  == FALSE) {
      MessageBox(WindowFromDC(WindowFromDC(currentDC)), 
		 "Unable to copy context.", "Error",
		 MB_ICONERROR | MB_OK);
    }
    
    if (wglMakeCurrent(currentDC, currentGLRC) == FALSE) {
      MessageBox(WindowFromDC(currentDC), 
		 "Unable to make context current.", "Error",
		 MB_ICONERROR | MB_OK);
    }
    
    if (wglGetCurrentContext() == NULL) 
      MessageBox(WindowFromDC(currentDC), 
		 "Current context is still NULL", "Error",
		 MB_ICONERROR | MB_OK);
  }
}



void
setupPixelFormat(HDC hDC)
{
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),  /* size */
        1,                              /* version */
        PFD_SUPPORT_OPENGL |
        PFD_DRAW_TO_WINDOW |
        PFD_DOUBLEBUFFER,               /* support double-buffering */
        PFD_TYPE_RGBA,                  /* color type */
        16,                             /* prefered color depth */
        0, 0, 0, 0, 0, 0,               /* color bits (ignored) */
        0,                              /* no alpha buffer */
        0,                              /* alpha bits (ignored) */
        0,                              /* no accumulation buffer */
        0, 0, 0, 0,                     /* accum bits (ignored) */
        16,                             /* depth buffer */
        0,                              /* no stencil buffer */
        0,                              /* no auxiliary buffers */
        PFD_MAIN_PLANE,                 /* main layer */
        0,                              /* reserved */
        0, 0, 0,                        /* no layer, visible, damage masks */
    };
    int pixelFormat;

    pixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (pixelFormat == 0) {
        MessageBox(WindowFromDC(hDC), "ChoosePixelFormat failed.", "Error",
                MB_ICONERROR | MB_OK);
    }

    if (SetPixelFormat(hDC, pixelFormat, &pfd) != TRUE) {
        MessageBox(WindowFromDC(hDC), "SetPixelFormat failed.", "Error",
                MB_ICONERROR | MB_OK);
    }
}




void
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



static void handleWindowCreation(HWND hWnd) 
{
  /* Set things up for OpenGL rendering */
  HDC     currentDC;
  HGLRC   currentGLRC;
  JNIEnv  *widgetEnvironment;
  jobject widget;
  
  currentDC = GetDC(hWnd);
  setupPixelFormat(currentDC);
  setupPalette(currentDC);
  currentGLRC = wglCreateContext(currentDC);
  
  if (currentGLRC == NULL) {
    MessageBox(hWnd, "Unable to create GL context", 
	       "Error", MB_ICONERROR | MB_OK);
  }
  
  if (wglMakeCurrent(currentDC, currentGLRC) == FALSE) {
    MessageBox(hWnd, "Unable to make GL context current.",  "Error", 
	       MB_ICONERROR | MB_OK);
  }
  
  widgetEnvironment = environmentForWindow(hWnd);
  widget            = widgetForWindow(hWnd);

  log(widgetEnvironment, "In window creation\n");
  if (widgetEnvironment == NULL) {
    MessageBox(hWnd, "Unable to get widget environment",  "Error", 
	       MB_ICONERROR | MB_OK);
  }

  if (widget == NULL) {
    MessageBox(hWnd, "Unable to get widget",  "Error", 
	       MB_ICONERROR | MB_OK);
  }

  setDCForWidget(widgetEnvironment, widget, currentDC);
  setGLRCForWidget(widgetEnvironment, widget, currentGLRC);
  
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
      HGLRC currentGLRC = wglGetCurrentContext();
     
      if (currentGLRC) {
	int     winWidth          = (int) LOWORD(lParam);
	int     winHeight         = (int) HIWORD(lParam);
	JNIEnv *widgetEnvironment = environmentForWindow(hWnd);
	jobject widget            = widgetForWindow(hWnd);
       
	if ((widgetEnvironment != NULL) && (widget != NULL))
	  handOffWindowResized(widgetEnvironment, widget, winWidth, 
			       winHeight);
	return 0;
      } else {
	MessageBox(hWnd, "Unknown GLRC in WM_SIZE", "Error",
		   MB_ICONERROR | MB_OK);
      }
    }
  break;
  case WM_PALETTECHANGED:
    /* realize palette if this is *not* the current window */
    {
      HGLRC   currentGLRC       = wglGetCurrentContext();
      HDC     currentDC         = GetWindowDC(hWnd);
      JNIEnv *widgetEnvironment = environmentForWindow(hWnd);
      jobject widget            = widgetForWindow(hWnd);
     
      if (currentGLRC && hPalette && (HWND) wParam != hWnd) {
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
      HGLRC   currentGLRC       = wglGetCurrentContext();
      JNIEnv *widgetEnvironment = environmentForWindow(hWnd);
      jobject widget            = widgetForWindow(hWnd);
     
      if (currentGLRC && hPalette) {
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
     
      if ((widgetEnvironment != NULL) && (wglGetCurrentContext() != NULL) &&
	  (widget != NULL)) {
	handOffWindowExposed(widgetEnvironment, widget);
      } else {
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



JNIEXPORT jboolean 
Java_OpenGL_OpenGLWidget_openOpenGLWidget(JNIEnv *env, jobject obj,
					  jint x, jint y, 
					  jint width, jint height,
					  jstring titleUTFString)
{
    WNDCLASS wndClass;
    HWND hWnd;
    HINSTANCE hCurrentInst = NULL;
    int nCmdShow           = 1;

    int winX     = x,   winY      = y;
    int winWidth = width, winHeight = height;
    
    const char *className      = "OpenGLWidget";
    const char *windowName     = "";
    
    jboolean copy              = JNI_TRUE;

    log(env, "HAPPY HAPPY JOY JOY\n");

    /* Make sure that only one thread is trying to create a window at
       a time. */
    getWidgetLock();

    windowName = (*env)->GetStringUTFChars(env, titleUTFString, &copy);
    if (windowName == NULL) {
      releaseWidgetLock();
      handleError(env, "OpenGL/OpenGLNativeException",
		  "Unable to get title string for widget");
      return JNI_FALSE;
    }

    /* register window class */
    wndClass.style         = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc   = WndProc;
    wndClass.cbClsExtra    = 0;
    wndClass.cbWndExtra    = 0;
    wndClass.hInstance     = hCurrentInst;
    wndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName  = NULL;
    wndClass.lpszClassName = className;
    RegisterClass(&wndClass);

    /* create window */
    hWnd = CreateWindow(
        className, windowName,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        winX, winY, winWidth, winHeight,
        NULL, NULL, hCurrentInst, NULL);
    
    setWidgetForWindow(hWnd, env, obj);
    setEnvironmentForWindow(hWnd, env, obj);
    log(env, "the widget is");
    logHex(env, obj);
    log(env, "\n");

    if (windowForWidget(env, obj) != hWnd)
      log(env, "uhoh --- no match\n");

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
    /* execute idle function while no messages to process */

    while(1) {
      while (idleFunc &&
	     PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == FALSE) {
	(*idleFunc)(getDCForWidget(env, obj));
      }
      if (GetMessage(&msg, NULL, 0, 0) != TRUE) {
	break;
      }
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

  log(env, "starting setTitle\n");
  title = (*env)->GetStringUTFChars(env, jtitle, &copy);
  if (title == NULL) {
    handleError(env, "OpenGL/OpenGLNativeException",
		"Unable to get new title string for widget");
    return;
  }

  window = windowForWidget(env, widget);
  log(env, title);
  log(env, "the widget is");
  logHex(env, widget);
  log(env, "\n");
  if (window != NULL) {
    log(env, "setting window text\n");
    SetWindowText(window, title);
  } else
    {
      log(env, "null window\n");
    }
  log(env, "exiting settitle\n");
}





