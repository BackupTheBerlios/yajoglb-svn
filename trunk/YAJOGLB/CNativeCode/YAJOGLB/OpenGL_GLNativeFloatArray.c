/*
  Implements a native float array.
 
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
 * OpenGL_GLNativeFloatArray.c
 *
 * $Id$
 *
 * This implements the native methods for the native float array class.
 *
 */

#include "SystemIncludes.h"

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
