/*
 * OpenGL_GLSelectionBuffer.c
 *
 * $Id: OpenGL_GLSelectionBuffer.c,v 1.2 1999/02/13 19:27:40 razeh Exp $
 *
 * This implements the selection buffer portion of the OpenGL Java binding.
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@balr.com)
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

