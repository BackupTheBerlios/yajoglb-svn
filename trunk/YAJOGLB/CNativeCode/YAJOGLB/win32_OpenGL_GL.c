/*
  Lets us set the viewport (because we have problems under Linux).
 
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
 * win32_OpenGL_GL.c
 *
 * $Id$
 *
 * This implements some generic GL methods that need extra care under
 * win32.
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

