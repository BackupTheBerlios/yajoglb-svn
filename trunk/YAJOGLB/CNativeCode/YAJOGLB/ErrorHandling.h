/*
 * ErrorHandling.h
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@yahoo.com)
 */

#include <jni.h>

void handleError(JNIEnv *env, 
		 const char *exceptionClass, 
		 const char *errorMessage);
void handleOutOfMemoryError(JNIEnv *env, const char *errorMessage);
void logMessage(JNIEnv *env, const char *string);
void fatalUnreportableError(const char *errorString);

#define NATIVE_PROBLEM -1
#define OPENGL_NATIVE_EXCEPTION "OpenGL/NativeException"
#define OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION "OpenGL/NativeMemoryExhaustedException"
#define OPENGL_UNSUPPORTED_METHOD_EXCEPTION "OpenGL/UnsupportedMethodException"
#define OPENGL_CANVAS_EXCEPTION "OpenGL/CanvasSetupFailedException"
#define OPENGL_CONTEXT_EXCEPTION "OpenGL/ContextException"


