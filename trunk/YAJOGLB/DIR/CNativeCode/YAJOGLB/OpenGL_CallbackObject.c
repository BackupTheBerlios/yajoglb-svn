/*
 * OpenGL_CallbackObject.c
 *
 * $Id: OpenGL_CallbackObject.c,v 1.1 1999/01/04 02:02:29 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements some of the support that is need to make callback objects 
 * work properly.
 */

#include "cygnusFixes.h"
#include "OpenGL_CallbackObject.h"
#include "EnvDictionary.h"

/* Set the current thread's environment pointer for our callbacks.*/
JNIEXPORT void JNICALL Java_OpenGL_CallbackObject_setEnvironmentPointer
  (JNIEnv *env, jclass clasz)
{
	setEnvironmentPointerForCurrentThread(env);
}



/* Clears the environment pointer set above. */
JNIEXPORT void JNICALL Java_OpenGL_CallbackObject_unsetEnvironmentPointer
  (JNIEnv *env, jclass clasz)
{
	unsetEnvironmentPointerForCurrentThread();
}