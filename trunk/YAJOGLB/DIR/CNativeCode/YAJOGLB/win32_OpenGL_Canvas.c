/*
  Canvas methods for win32.

  Copyright 2001, Robert Allan Zeh (razeh@yahoo.com)
  7346 Lake Street #3W
  River Forest, IL 60305

  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA
*/

/*
 * OpenGL_Canvas.c
 *
 * $Id: win32_OpenGL_Canvas.c,v 1.6 2001/08/11 02:16:20 razeh Exp $
 *
 * This implements the OpenGL methods needed to setup our canvas for OpenGL
 * rendering.  It assumes that we have some nice way to get the HDC and HWnd
 * from the canvas.
 */

#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include "OpenGL_Canvas.h"
#include "SystemError.h"
#include "memory.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"
#include "win32DCDictionary.h"
#include "CapabilitiesAccessors.h"



////////////////////////////////////////////////////////////////////////
// Functions for our private use.
////////////////////////////////////////////////////////////////////////



/* This throws an OpenGLCanvasException Java exception that uses the current
   system error as the error message. */
static void throwCanvasException(JNIEnv *env)
{
  char *errorMessage = systemErrorMessage();
  handleError(env, OPENGL_CANVAS_EXCEPTION, errorMessage);
  privateFree((void*)errorMessage);
}



/* Throw an OpenGLCanvasException with the supplied message. */
static void throwCanvasExceptionWithMessage(JNIEnv *env, const char *errorMessage)
{
  handleError(env, OPENGL_CANVAS_EXCEPTION, errorMessage);
}



static void
setupPixelFormat(JNIEnv *env, jobject capabilities, HDC hDC)
{
  BYTE colorTypeChoice = 0, colorDepthSize = 0, alphaDepthSize = 0,
       depthBufferSize = 0, stencilBufferSize = 0;
  jint doubleBufferChoice;

  int error = 0;
  
  /* Get the capabilities values. */
  if (!error) {
    alphaDepthSize = (BYTE)alphaDepth(env, capabilities);
    error = (alphaDepthSize < 0);
  }

  if (!error) {
    colorDepthSize = (BYTE)colorDepth(env, capabilities);
    error = (colorDepthSize < 0);
  }

  if (!error) {
    depthBufferSize = (BYTE)depthBuffer(env, capabilities);
    error = (depthBufferSize < 0);
  }
  
  if (!error) {
    stencilBufferSize = (BYTE)stencilBuffer(env, capabilities);
    error = (stencilBufferSize < 0);
  }

  if (!error) {
	jint newColorTypeChoice = colorType(env, capabilities);
				
	if (0 == newColorTypeChoice) {
		colorTypeChoice = PFD_TYPE_RGBA;
	} 

	if (1 == newColorTypeChoice) {
		colorTypeChoice = PFD_TYPE_COLORINDEX;
	}

    error = (newColorTypeChoice  < 0);
  }

  if (!error) {
    doubleBufferChoice = isDoubleBufferEnabled(env, capabilities);
    error = (doubleBufferChoice < 0);
  }


  if (!error) {
        PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),         /* size */
        1,                                     /* version */
        PFD_SUPPORT_OPENGL |
        PFD_DRAW_TO_WINDOW |
        PFD_DOUBLEBUFFER & doubleBufferChoice, /* support double-buffering */
        colorTypeChoice,                       /* color type */
        colorDepthSize,                        /* prefered color depth */
        0, 0, 0, 0, 0, 0,                      /* color bits (ignored) */
        alphaDepthSize != 0,                   /* alpha buffer */
        alphaDepthSize,                        /* alpha bits (ignored) */
        0,                                     /* no accumulation buffer */
        0, 0, 0, 0,                            /* accum bits (ignored) */
        depthBufferSize,                       /* bits per pixel --- depth buffer */
        stencilBufferSize,                     /* bits per pixel --- stencil buffer */
        0,                                     /* no auxiliary buffers */
        PFD_MAIN_PLANE,                        /* main layer */
        0,                                     /* reserved */
        0, 0, 0,                               /* no layer, visible, damage masks */
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



////////////////////////////////////////////////////////////////////////
// Implementation of our native methods.
////////////////////////////////////////////////////////////////////////



JNIEXPORT jboolean JNICALL Java_OpenGL_Canvas_setupCanvas
  (JNIEnv *env, jobject canvas)
{
  jobject  capabilities  = NULL;
  CanvasInfo info        = getCanvasInfo(env, canvas);
  jboolean returnCode    = JNI_TRUE;

  if (NULL != info.hDC) {
		/* Get the capabilities object out of our widget. */
    jclass canvasClass             = NULL;
    jmethodID capabilitiesMethodID = NULL;
    canvasClass = (*env)->GetObjectClass(env, canvas);

    capabilitiesMethodID = 
      getMethodID(env, canvasClass,
		"capabilities", "()LOpenGL/Capabilities;",
		"Unable to get capabilities() method");
    if (capabilitiesMethodID) {
      capabilities = (*env)->CallObjectMethod(env, canvas, capabilitiesMethodID);
    }
	setupPixelFormat(env, capabilities, info.hDC);
	setupPalette(env, info.hDC);
  } else {
	throwCanvasExceptionWithMessage(env, "Unable to obtain hDC for canvas.");
	returnCode = JNI_FALSE;
  }

  freeCanvasInfo(env, info);
  return returnCode;
}



JNIEXPORT void JNICALL Java_OpenGL_Canvas_nativeSwapBuffers
  (JNIEnv *env, jobject canvas)
{
  CanvasInfo info = getCanvasInfo(env, canvas);
  SwapBuffers(info.hDC);
  freeCanvasInfo(env, info);
}



/* Returns the string for our data access class. */
JNIEXPORT jstring JNICALL Java_OpenGL_Canvas_dataAccessClass
  (JNIEnv *env, jclass clasz)
{
  return (*env)->NewStringUTF(env, "sun.awt.windows.WindowspDataAccess");
}
