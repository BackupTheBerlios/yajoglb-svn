/*
 * EnvDictionary.h 
 *
 * $Id: EnvDictionary.h,v 1.2 1999/01/26 23:58:23 razeh Exp $
 *
 * This defines the interface for setting and getting the JNI environment
 * pointer for the current thread.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

#include <jni.h>

void setEnvironmentPointerForCurrentThread(JNIEnv *env);
void unsetEnvironmentPointerForCurrentThread();
JNIEnv *environmentPointerForCurrentThread();
jobject getActiveObjectOfClass(jclass objectClass);
