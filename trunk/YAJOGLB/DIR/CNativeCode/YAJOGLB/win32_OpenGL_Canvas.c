/*
 * OpenGL_OpenGLCanvas.c
 *
 * $Id: win32_OpenGL_Canvas.c,v 1.3 1998/12/23 00:42:24 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements the OpenGL methods needed to setup our canvas for OpenGL
 * rendering.  It assumes that we have some nice way to get the HDC and HWnd
 * from the canvas.
 */

#include <windows.h>
#include "cygnusFixes.h"
#include "OpenGL_OpenGLCanvas.h"
#include "SystemError.h"
#include "memory.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"

#define OPENGL_CANVAS_EXCEPTION "OpenGL/OpenGLCanvasSetupFailedException"

/* This throws an OpenGLContextException Java exception that uses the current
   system error as the error message. */
static void throwCanvasException(JNIEnv *env)
{
	char *errorMessage = systemErrorMessage();
	handleError(env, OPENGL_CANVAS_EXCEPTION, errorMessage);
    privateFree((void*)errorMessage);
}

static void
setupPixelFormat(JNIEnv *env, jobject capabilities, HDC hDC)
{
  jint colorDepth = 0, alphaDepth = 0, depthBuffer = 0, stencilBuffer = 0;

  {
	jclass    capabilitiesClass = NULL;
	jmethodID methodID          = NULL;

	capabilitiesClass = (*env)->GetObjectClass(env, capabilities);
	/* The color depth. */
	methodID = getMethodID(env, capabilitiesClass, "colorDepth", "()I",
		"Unable to get colorDepth method.");
	if (methodID) {
		colorDepth = (*env)->CallIntMethod(env, capabilities, methodID);
	} else {
		return;
	}

	/* The alpha depth. */
	methodID = getMethodID(env, capabilitiesClass, "alphaDepth", "()I",
		"Unable to get the alphaDepth method.");
	if (methodID) {
		alphaDepth = (*env)->CallIntMethod(env, capabilities, methodID);
	} else {
		return;
	}

	/* The depth buffer depth. */
	methodID = getMethodID(env, capabilitiesClass, "depthBuffer", "()I",
		"Unable to get the depthBuffer method.");
	if (methodID) {
		depthBuffer = (*env)->CallIntMethod(env, capabilities, methodID);
	} else {
		return;
	}

	/* The stencil buffer. */
	methodID = getMethodID(env, capabilitiesClass, "stencilBuffer", "()I",
		"Unable to get the stencilBuffer method.");
	if (methodID) {
		stencilBuffer = (*env)->CallIntMethod(env, capabilities, methodID);
	} else {
		return;
	}
  }

  {
	PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),  /* size */
        1,                              /* version */
        PFD_SUPPORT_OPENGL |
        PFD_DRAW_TO_WINDOW |
        PFD_DOUBLEBUFFER,               /* support double-buffering */
        PFD_TYPE_RGBA,                  /* color type */
        (unsigned char)colorDepth,      /* prefered color depth */
        0, 0, 0, 0, 0, 0,               /* color bits (ignored) */
        alphaDepth != 0,                /* alpha buffer */
        (unsigned char)alphaDepth,      /* alpha bits (ignored) */
        0,                              /* no accumulation buffer */
        0, 0, 0, 0,                     /* accum bits (ignored) */
        (unsigned char)depthBuffer,     /* bits per pixel --- depth buffer */
        (unsigned char)stencilBuffer,   /* bits per pixel --- stencil buffer */
        0,                              /* no auxiliary buffers */
        PFD_MAIN_PLANE,                 /* main layer */
        0,                              /* reserved */
        0, 0, 0,                        /* no layer, visible, damage masks */
    };

    int pixelFormat = 0;
	int setPixelFormatResult = 0; 

    pixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (pixelFormat == 0) {
      throwCanvasException(env);
      return;
    }

	setPixelFormatResult = SetPixelFormat(hDC, pixelFormat, &pfd);
    if (setPixelFormatResult != TRUE) {
      throwCanvasException(env);
      return;
    }
  }
}



static void
setupPalette(JNIEnv *env, HDC hDC)
{
    HPALETTE hPalette  = NULL;
    int pixelFormat = GetPixelFormat(hDC);
    PIXELFORMATDESCRIPTOR pfd;
    LOGPALETTE* pPal;
    int paletteSize;

    if (0 ==
		DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd)) {
      throwCanvasException(env);
	  return;
	}

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

	if (NULL == hPalette) {
		throwCanvasException(env);
		return;
	}

    if (NULL == SelectPalette(hDC, hPalette, FALSE)) {
		throwCanvasException(env);
		return;
	}
    if (GDI_ERROR == RealizePalette(hDC)) {
		throwCanvasException(env);
		return;
	}
}



/*
 * Class:     OpenGL_OpenGLCanvas
 * Method:    setupOpenGLCanvas
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_OpenGL_OpenGLCanvas_setupOpenGLCanvas
  (JNIEnv *env, jobject canvas, jint hDC, jint HWnd)
{
  jobject capabilities             = NULL;

  /* Get the capabilities object out of our widget. */
  {
    jclass canvasClass             = NULL;
    jmethodID capabilitiesMethodID = NULL;
    canvasClass = (*env)->GetObjectClass(env, canvas);

    capabilitiesMethodID = 
      getMethodID(env, canvasClass,
		"capabilities", "()LOpenGL/OpenGLCapabilities;",
		"Unable to get capabilities() method");
    if (capabilitiesMethodID) {
      capabilities = (*env)->CallObjectMethod(env, canvas, capabilitiesMethodID);
    }
  }

  setupPixelFormat(env, capabilities, (HDC) hDC);
  setupPalette(env, (HDC) hDC);

  return JNI_TRUE;
}

/*
 * Class:     OpenGL_OpenGLCanvas
 * Method:    nativeSwapBuffers
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLCanvas_nativeSwapBuffers
  (JNIEnv *env, jobject canvas, jint hDC)
{
	SwapBuffers((HDC) hDC);
}

