/*
 * ErrorHandling.h
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

#include <jni.h>

void handleError(JNIEnv *env, 
		 const char *exceptionClass, const char *errorMessage);
void log(JNIEnv *env, const char *string);

#define NATIVE_PROBLEM -1

