/*
 * EnvDictionary.h 
 *
 * $Id$
 *
 * This defines the interface for getting the JNI environment
 * pointer for the current thread.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

#include <jni.h>

JNIEnv *environmentPointerForCurrentThread();
jobject getActiveObjectOfClass(jclass objectClass);
