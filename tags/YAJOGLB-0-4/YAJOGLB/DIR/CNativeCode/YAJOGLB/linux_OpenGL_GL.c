/*
  Some Linux specific OpenGL methods.
 
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
 * linux_OpenGL_GL.c
 *
 * $Id: linux_OpenGL_GL.c,v 1.2 2001/07/06 23:40:05 razeh Exp $
 *
 * This implements some generic GL methos that need extra care to work
 * properly under linux.
 */

/* With the Cygnus tools you need to include the GL stuff first. */
#include "SystemIncludes.h"
#include <GL/gl.h>
#include <GL/glx.h>
#ifdef MESA
#include <GL/xmesa.h>
#endif
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

#ifdef MESA
  XMesaContext context = glXGetCurrentContext();
  XMesaFlush(context);
#endif
  glViewport(x, y, width, height);
}

