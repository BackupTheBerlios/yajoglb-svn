/*
 * linux_OpenGL_GL.c
 *
 * $Id: linux_OpenGL_GL.c,v 1.1 1999/04/18 14:24:59 razeh Exp $
 *
 * This implements some generic GL methos that need extra care to work
 * properly under linux.
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@balr.com)
 */

/* With the Cygnus tools you need to include the GL stuff first. */
#include "SystemIncludes.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/xmesa.h>

#include "cygnusFixes.h"
#include "OpenGL_GL.h"


JNIEXPORT void JNICALL Java_OpenGL_GL_viewport
  (JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height)
{
  /* We have to take some special steps before calling glViewport under
     the Linux port, because we are using two display connections to talk
     with our canvas.  If we do not synchronize the display that Mesa uses
     before calling glViewport it's possible that Mesa will use out of date
     information about the Canvas size.

     What's happening is that the Java display is receiving the resize
     event before the Mesa display does.  The Java code then updates its
     viewport, but Mesa thinks that the viewport is its old size.  As a result,
     the Mesa display gets clipped.
  */

  XMesaContext context = glXGetCurrentContext();
  XMesaFlush(context);

  glViewport(x, y, width, height);
}

