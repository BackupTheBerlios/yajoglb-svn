/*
 * OpenGL_GLSelectionBuffer.c
 *
 * $Id: OpenGL_GLSelectionBuffer.c,v 1.1 1999/01/26 23:55:44 razeh Exp $
 *
 * This implements the selection buffer portion of the OpenGL Java binding.
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@balr.com)
 */

#include <windows.h>
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

