/*
 * EnvDictionary.h 
 *
 * $Id$
 *
 * This defines the interface for setting and getting the JNI environment
 * pointer for the current thread.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

#include <jni.h>

void setEnvironmentPointerForCurrentThread(JNIEnv *env);
void unsetEnvironmentPointerForCurrentThread();
JNIEnv *environmentPointerForCurrentThread();
jobject getActiveObjectOfClass(jclass objectClass);
