/*
 * OpenGL_OpenGLContext.c
 *
 * $Id: win32_OpenGL_Context.c,v 1.2 1998/11/04 00:34:13 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements the native methods for OpenGLContext --- methods that 
 * create, manipulate, and destroy the current OpenGL context.
 */

#include "cygnusFixes.h"
#include "OpenGL_OpenGLContext.h"
#include "win32DCDictionary.h"
#include "SystemError.h"
#include "memory.h"
#include "ErrorHandling.h"

/* Our context exception class. */
#define OPENGL_CONTEXT_EXCEPTION "OpenGL/OpenGLContextException"



/* This throws an OpenGLContextException Java exception that uses the current
   system error as the error message. */
static void throwContextException(JNIEnv *env)
{
	char *errorMessage = systemErrorMessage();
	handleError(env, OPENGL_CONTEXT_EXCEPTION, errorMessage);
    privateFree((void*)errorMessage);
}



/*
 * Class:     OpenGL_OpenGLContext
 * Method:    nativeReleaseCurrentContext
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLContext_nativeReleaseCurrentContext
  (JNIEnv *env, jclass class)
{
	if (FALSE == wglMakeCurrent(NULL, NULL)) {
		/* Something really bad must have happened. */
		throwContextException(env);
	}
}



/*
 * Class:     OpenGL_OpenGLContext
 * Method:    makeCanvasCurrent
 * Signature: (ILOpenGL/OpenGLCanvas;)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLContext_makeCanvasCurrent
  (JNIEnv *env, jobject contextObject, jint context, jobject canvas)
{
    HDC dc = NULL;

	if (context != 0) {
		dc = getDCForCanvas(env, canvas);
	}
	if (FALSE == wglMakeCurrent(dc, (HGLRC*) context)) {
		/* Something went wrong, and we need to throw an exception. */
		throwContextException(env);
	}
}



/*
 * Class:     OpenGL_OpenGLContext
 * Method:    createCanvasContext
 * Signature: (LOpenGL/OpenGLCanvas;I)I
 */
JNIEXPORT jint JNICALL Java_OpenGL_OpenGLContext_createCanvasContext
  (JNIEnv *env, jobject contextObject, jobject canvas, jint otherContext)
{
	HDC   dc      = getDCForCanvas(env, canvas);
	HGLRC context = wglCreateContext(dc);
	if (NULL == context) {
		/* Something went wrong, and we need to throw an exception. */
		throwContextException(env);
	}

	if (otherContext != 0) {
		if (FALSE == wglShareLists((HGLRC) otherContext, context))
			throwContextException(env);
	}
	return (int) context;
}



/*
 * Class:     OpenGL_OpenGLContext
 * Method:    deleteContext
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLContext_deleteContext
  (JNIEnv *env, jobject contextObject, jint context)
{
	if (FALSE == wglDeleteContext((HGLRC)context)) {
		/* Something went wrong, and we need to throw an exception. */
		throwContextException(env);
	}
}
