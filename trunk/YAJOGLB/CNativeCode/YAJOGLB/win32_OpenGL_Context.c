/*
  win32 OpenGL context methods.
 
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
 * win32OpenGL_OpenGLContext.c
 *
 * $Id$
 *
 * This implements the native methods for OpenGLContext --- methods that 
 * create, manipulate, and destroy the current OpenGL context.
 */

#include "cygnusFixes.h"
#include "OpenGL_Context.h"
#include "win32DCDictionary.h"
#include "SystemError.h"
#include "memory.h"
#include "ErrorHandling.h"

/* Our context exception class. */
#define OPENGL_CONTEXT_EXCEPTION "OpenGL/ContextException"



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
JNIEXPORT void JNICALL Java_OpenGL_Context_nativeReleaseCurrentContext
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
JNIEXPORT void JNICALL Java_OpenGL_Context_makeCanvasCurrent
  (JNIEnv *env, jobject contextObject, jlong context, jobject canvas)
{
	if (context != 0) {
		CanvasInfo info = getCanvasInfo(env, canvas);
		if (FALSE == wglMakeCurrent(info.hDC, (HGLRC) context)) {
			/* Something went wrong, and we need to throw an exception. */
			throwContextException(env);
		}
		freeCanvasInfo(env, info);
	}	
}



/*
 * Class:     OpenGL_OpenGLContext
 * Method:    createCanvasContext
 * Signature: (LOpenGL/OpenGLCanvas;I)I
 */
JNIEXPORT jlong JNICALL Java_OpenGL_Context_createCanvasContext
  (JNIEnv *env, jobject contextObject, jobject canvas, jlong otherContext)
{
	CanvasInfo info = getCanvasInfo(env, canvas);	
	HGLRC context = wglCreateContext(info.hDC);
	if (NULL == context) {
		/* Something went wrong, and we need to throw an exception. */
		throwContextException(env);
	}

	if (otherContext != 0) {
		if (FALSE == wglShareLists((HGLRC) otherContext, context))
			throwContextException(env);
	}
	freeCanvasInfo(env, info);
	return (int) context;
}



/*
 * Class:     OpenGL_OpenGLContext
 * Method:    deleteContext
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_Context_deleteContext
  (JNIEnv *env, jobject contextObject, jlong context)
{
	if (FALSE == wglDeleteContext((HGLRC)context)) {
		/* Something went wrong, and we need to throw an exception. */
		throwContextException(env);
	}
}
