/*
 * win32_OpenGL_GL.c
 *
 * $Id: win32_OpenGL_GL.c,v 1.1 1999/04/18 14:26:57 razeh Exp $
 *
 * This implements some generic GL methods that need extra care under
 * win32.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */


/* With the Cygnus tools you need to include the GL stuff first. */
#include "SystemIncludes.h"
#include <GL/gl.h>

#include "cygnusFixes.h"
#include "OpenGL_GL.h"


/* We do not do anything special with viewport under win32, but we
   can not include it in OpenGL_GL.c because we have synchronize the
   X display under Linux.
*/
JNIEXPORT void JNICALL Java_OpenGL_GL_viewport
  (JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height)
{
  glViewport(x, y, width, height);
}

