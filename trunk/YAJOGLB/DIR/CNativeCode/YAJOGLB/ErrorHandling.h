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
void logMessage(JNIEnv *env, const char *string);
void fatalUnreportableError(const char *errorString);

#define NATIVE_PROBLEM -1
#define OPENGL_NATIVE_EXCEPTION "OpenGL/OpenGLNativeException"
#define OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION "OpenGL/OpenGLNativeMemoryExhaustedException"
#define OPENGL_UNSUPPORTED_METHOD_EXCEPTION "OpenGL/OpenGLUnsupportedMethodException"

