/*
 * ErrorHandling.h
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

#include <jni.h>

void handleError(JNIEnv *env, 
		         const char *exceptionClass, 
		         const char *errorMessage);
void handleOutOfMemoryError(JNIEnv *env, const char *errorMessage);
void log(JNIEnv *env, const char *string);
void fatalUnreportableError(const char *errorString);

#define NATIVE_PROBLEM -1
#define OPENGL_NATIVE_EXCEPTION "OpenGL/OPENGL_NATIVE_EXCEPTION"
#define OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION "OpenGL/OpenGLNativeMemoryExhaustedException"
