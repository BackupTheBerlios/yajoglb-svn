/*
  Canvas methods for Linux.
 
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
 * $Id$
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 *
 * This implements the OpenGL methods needed to setup our canvas for OpenGL
 * rendering.  
 */

#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include <GL/glx.h>
#include <X11/X.h>
#include "OpenGL_Canvas.h"
#include "SystemError.h"
#include "memory.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"
#include "linuxDPYDictionary.h"


/* Our native hook for setting up this canvas. */
JNIEXPORT jboolean JNICALL Java_OpenGL_Canvas_setupCanvas
  (JNIEnv *env, jobject canvas)
{
  /* Under X11 most of the setup is handled in the context creation. */
  return JNI_TRUE;
}



/* Swap the double buffers for this canvas. */
JNIEXPORT void JNICALL Java_OpenGL_Canvas_nativeSwapBuffers
  (JNIEnv *env, jobject canvas)
{
  CanvasInfo  info = getCanvasInfo(env, canvas);
  if ((0 != info.display) && (0 != info.drawable)) {
    glXSwapBuffers(info.display, info.drawable);
  }
  freeCanvasInfo(env, info);
}
