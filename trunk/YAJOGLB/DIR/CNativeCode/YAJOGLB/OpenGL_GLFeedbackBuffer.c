/*
 * OpenGL_GL.c
 *
 * $Id: OpenGL_GLFeedbackBuffer.c,v 1.1 1998/11/04 00:29:23 razeh Exp $
 *
 * This implements the generic GL methods.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */


/* With the Cygnus tools you need to include the GL stuff first. */
#include <windows.h>
#include <GL/gl.h>

#include "cygnusFixes.h"
#include "ErrorHandling.h"
#include "OpenGL_GLFeedbackBuffer.h"
#include "memory.h"
#include "JNIInterface.h"

/* This file contains the C implementation for the feedback buffer.  The actual
buffer needs to be mapped into a persistent array so that OpenGL can write into it is called.
*/

/*
 * Class:     OpenGL_GLFeedbackBuffer
 * Method:    feedbackBuffer
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLFeedbackBuffer_feedbackBuffer
  (JNIEnv *env, jobject feedbackBuffer, jint size, jint type, jint bufferPointer)
{
	glFeedbackBuffer(size, type, (GLfloat*) bufferPointer);
}



/*
 * Class:     OpenGL_GLFeedbackBuffer
 * Method:    mapBuffer
 * Signature: ([F)I
 */
JNIEXPORT jint JNICALL Java_OpenGL_GLFeedbackBuffer_mapBuffer
  (JNIEnv *env, jobject feedbackBuffer, jfloatArray jbuffer)
{
	GLfloat  *buffer;
	jboolean  isCopy;
	jmethodID setNativeArrayIsCopyMethod;
	jclass    feedbackClass;
	
	buffer = (*env)->GetFloatArrayElements(env, jbuffer, &isCopy);
 
	feedbackClass = (*env)->GetObjectClass(env, feedbackBuffer);

	setNativeArrayIsCopyMethod = getMethodID(env, feedbackClass,
	      "setNativeArrayIsCopy", "(Z)V", "Unable to find setNativeArrayIsCopy");
	if (setNativeArrayIsCopyMethod) {
			(*env)->CallVoidMethod(env, feedbackBuffer, 
				                     setNativeArrayIsCopyMethod, isCopy);
	}

	return (int) buffer;
}



/*
 * Class:     OpenGL_GLFeedbackBuffer
 * Method:    unmapBuffer
 * Signature: ([FI)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLFeedbackBuffer_unmapBuffer
  (JNIEnv *env, jobject feedbackBuffer, jfloatArray jbuffer, jint buffer)
{
	(*env)->ReleaseFloatArrayElements(env, jbuffer, (float*)buffer, 0);
}



/*
 * Class:     OpenGL_OpenGLFeedbackBuffer
 * Method:    copyBuffer
 * Signature: ([FI)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLFeedbackBuffer_copyBuffer
  (JNIEnv *env, jobject feedbackBuffer, jfloatArray jbuffer, jint buffer)
{
	(*env)->ReleaseFloatArrayElements(env, jbuffer, (float*)buffer, JNI_COMMIT);
}