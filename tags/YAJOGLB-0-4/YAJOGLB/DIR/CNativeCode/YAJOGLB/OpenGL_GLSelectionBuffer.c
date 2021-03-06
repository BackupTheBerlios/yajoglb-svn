/*
  The selection bufffer.
 
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
 * OpenGL_GLSelectionBuffer.c
 *
 * $Id: OpenGL_GLSelectionBuffer.c,v 1.3 2001/07/06 23:40:05 razeh Exp $
 *
 * This implements the selection buffer portion of the OpenGL Java binding.
 *
 */

#include "SystemIncludes.h"
#include <GL/gl.h>

#include "cygnusFixes.h"
#include "ErrorHandling.h"
#include "OpenGL_GLSelectionBuffer.h"

/* This files contains the C implementation for the selection buffer.
The actual buffer needs to be mapped into a persistent array so that OpenGL can
write into it when it is called.
All of the persistence handling is taken care of by our Java superclass.
*/

JNIEXPORT void JNICALL Java_OpenGL_GLSelectionBuffer_selectBuffer
  (JNIEnv *env, jobject selectionBuffer, jint size, jint bufferPointer)
{
	glSelectBuffer(size, (GLint*) bufferPointer);
}

