/*
  Support for the feedback buffer.
 
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
 * OpenGL_GLFeedbackBuffer.c
 *
 * $Id$
 *
 * This implements the native methods for the feedback buffer.
 *
 */


/* With the Cygnus tools you need to include the GL stuff first. */
#include "SystemIncludes.h"

#include "cygnusFixes.h"
#include "OpenGL_GLFeedbackBuffer.h"

/* This file contains the C implementation for the feedback buffer.
   The actual buffer needs to be mapped into a persistent array so
   that OpenGL can write into it is called.  All of the persistence
   handling is taken care of by our Java superclass.  */

JNIEXPORT void JNICALL Java_OpenGL_GLFeedbackBuffer_feedbackBuffer
  (JNIEnv *env, jobject feedbackBuffer, jint size, jint type, jint bufferPointer)
{
	glFeedbackBuffer(size, type, (GLfloat*) bufferPointer);
}
