/*
 * OpenGL_GLNativeIntArray.c
 *
 * $Id: OpenGL_GLNativeIntArray.c,v 1.1 1999/01/26 23:55:44 razeh Exp $
 *
 * This implements the native methods for the native float array class.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

#include <windows.h>
#include <GL/gl.h>

#include "cygnusFixes.h"
#include "ErrorHandling.h"
#include "OpenGL_GLNativeIntArray.h"
#include "memory.h"
#include "JNIInterface.h"



JNIEXPORT jint JNICALL Java_OpenGL_GLNativeIntArray_mapBuffer
(JNIEnv *env, jobject feedbackBuffer, jintArray jbuffer)
{
	GLint    *buffer   = NULL;
	jboolean  isCopy   = 0;
	jmethodID setNativeArrayIsCopyMethod = NULL;
	jclass    feedbackClass              = NULL;
	
	buffer = (*env)->GetIntArrayElements(env, jbuffer, &isCopy);
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



JNIEXPORT void JNICALL Java_OpenGL_GLNativeIntArray_unmapBuffer
  (JNIEnv *env, jobject feedbackBuffer, jintArray jbuffer, jint buffer)
{
	(*env)->ReleaseIntArrayElements(env, jbuffer, (int*)buffer, 0);
}



JNIEXPORT void JNICALL Java_OpenGL_GLNativeIntArray_copyBuffer
  (JNIEnv *env, jobject feedbackBuffer, jintArray jbuffer, jint buffer)
{
	(*env)->ReleaseIntArrayElements(env, jbuffer, (int*)buffer, JNI_COMMIT);
}