/*
 * OpenGL_GLFeedbackBuffer.c
 *
 * $Id: OpenGL_GLFeedbackBuffer.c,v 1.3 1999/02/13 19:27:40 razeh Exp $
 *
 * This implements the native methods for the feedback buffer.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */


/* With the Cygnus tools you need to include the GL stuff first. */
#include "SystemIncludes.h"
#include <GL/gl.h>

#include "cygnusFixes.h"
#include "OpenGL_GLFeedbackBuffer.h"

/* This file contains the C implementation for the feedback buffer.  The actual
buffer needs to be mapped into a persistent array so that OpenGL can write into it is called.
All of the persistence handling is taken care of by our Java superclass.
*/

JNIEXPORT void JNICALL Java_OpenGL_GLFeedbackBuffer_feedbackBuffer
  (JNIEnv *env, jobject feedbackBuffer, jint size, jint type, jint bufferPointer)
{
	glFeedbackBuffer(size, type, (GLfloat*) bufferPointer);
}
