/*
 * OpenGL_GLNativeFloatArray.c
 *
 * $Id: OpenGL_GLNativeFloatArray.c,v 1.2 1999/02/13 19:27:40 razeh Exp $
 *
 * This implements the native methods for the native float array class.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

#include "SystemIncludes.h"
#include <GL/gl.h>

#include "cygnusFixes.h"
#include "ErrorHandling.h"
#include "OpenGL_GLNativeFloatArray.h"
#include "memory.h"
#include "JNIInterface.h"



JNIEXPORT jint JNICALL Java_OpenGL_GLNativeFloatArray_mapBuffer
(JNIEnv *env, jobject feedbackBuffer, jfloatArray jbuffer)
{
	GLfloat  *buffer   = NULL;
	jboolean  isCopy   = 0;
	jmethodID setNativeArrayIsCopyMethod = NULL;
	jclass    feedbackClass              = NULL;
	
	buffer = (*env)->GetFloatArrayElements(env, jbuffer, &isCopy);
	if (NULL != buffer) {
		feedbackClass = (*env)->GetObjectClass(env, feedbackBuffer);
		if (NULL != feedbackClass) {
			setNativeArrayIsCopyMethod = getMethodID(env, feedbackClass,
			      "setNativeArrayIsCopy", "(Z)V", "Unable to find setNativeArrayIsCopy");
			if (NULL != setNativeArrayIsCopyMethod) {
					(*env)->CallVoidMethod(env, feedbackBuffer, 
						                     setNativeArrayIsCopyMethod, isCopy);
			}
		}
	}
	return (int) buffer;
}



JNIEXPORT void JNICALL Java_OpenGL_GLNativeFloatArray_unmapBuffer
  (JNIEnv *env, jobject feedbackBuffer, jfloatArray jbuffer, jint buffer)
{
	(*env)->ReleaseFloatArrayElements(env, jbuffer, (float*)buffer, 0);
}



JNIEXPORT void JNICALL Java_OpenGL_GLNativeFloatArray_copyBuffer
  (JNIEnv *env, jobject feedbackBuffer, jfloatArray jbuffer, jint buffer)
{
	(*env)->ReleaseFloatArrayElements(env, jbuffer, (float*)buffer, JNI_COMMIT);
}
