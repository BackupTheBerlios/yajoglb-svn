/*
 * OpenGL_OpenGLContext.c
 *
 * $Id$
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 *
 * This implements the native methods for OpenGLContext --- methods that 
 * create, manipulate, and destroy the current OpenGL context.
 */

#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include <X11/X.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include "OpenGL_Context.h"
#include "SystemError.h"
#include "JNIInterface.h"
#include "Memory.h"
#include "ErrorHandling.h"
#include "linuxDPYDictionary.h"
#include "CapabilitiesAccessors.h"

/* Our context exception class. */
#define OPENGL_CONTEXT_EXCEPTION "OpenGL/ContextException"



////////////////////////////////////////////////////////////////////////
// Functions for our private use.
////////////////////////////////////////////////////////////////////////

/* This throws an OpenGLContextException Java exception that uses the current
   system error as the error message. */
static void throwContextException(JNIEnv *env, const char *errorMessage)
{
  handleError(env, OPENGL_CONTEXT_EXCEPTION, errorMessage);
}


/* Get the Capabilities object for the supplied canvas.  We
   return 0 if everything worked out and non-zero otherwise. */
static int getCapabilities(JNIEnv *env, jobject canvas, jobject *capabilities)
{
  jclass    canvasClass  = NULL;
  jmethodID methodID     = NULL;
  int       error        = 0;

  canvasClass = (*env)->GetObjectClass(env, canvas);
  methodID = getMethodID(env, canvasClass, 
			 "capabilities", "()LOpenGL/Capabilities;",
			 "Unable to get the capabilities method.");
  if (methodID && (NULL != capabilities)) {
    *capabilities = (*env)->CallObjectMethod(env, canvas, methodID);
  } else {
    error = 1;
  }

  return !error;
}



/* Return the visual that matches our capabilities most closely. */
static XVisualInfo *findVisual(Display *display, 
			       JNIEnv *env, jobject capabilities)
{
  XVisualInfo *visual = NULL;
  jint alphaDepthSize = 0,
       depthBufferSize = 0, stencilBufferSize = 0,
       colorTypeChoice = 0, doubleBufferChoice;

  int error = 0;

  /* Get the capabilities values. */
  if (!error) {
    alphaDepthSize = alphaDepth(env, capabilities);
    error = (alphaDepthSize < 0);
  }

  if (!error) {
    depthBufferSize = depthBuffer(env, capabilities);
    error = (depthBufferSize < 0);
  }
  
  if (!error) {
    stencilBufferSize = stencilBuffer(env, capabilities);
    error = (stencilBufferSize < 0);
  }

  if (!error) {
    colorTypeChoice = colorType(env, capabilities);
    error = (colorTypeChoice  < 0);
  }

  if (!error) {
    doubleBufferChoice = isDoubleBufferEnabled(env, capabilities);
    error = (doubleBufferChoice < 0);
  }

  if (!error)  {
    int visualAttribList[15];

    /* Ask GLX for a visual that matches the attributes we want: */
    int i = 0;

    /* If it's an RGBA color type then set it.*/
    if (0 == colorTypeChoice) {
      visualAttribList[i++] = GLX_RGBA;             /* 0 */
    }

    visualAttribList[i++] = GLX_RED_SIZE;         /* 1 */
    visualAttribList[i++] = 1;                    /* 2 */
    visualAttribList[i++] = GLX_GREEN_SIZE;       /* 3 */
    visualAttribList[i++] = 1;                    /* 4 */
    visualAttribList[i++] = GLX_BLUE_SIZE;        /* 5 */
    visualAttribList[i++] = 1;                    /* 6 */
    
    if (JNI_TRUE == doubleBufferChoice) {
      visualAttribList[i++] = GLX_DOUBLEBUFFER;   /* 7 */
    }

    visualAttribList[i++] = GLX_DEPTH_SIZE;       /* 8 */
    visualAttribList[i++] = depthBufferSize;      /* 9 */
    visualAttribList[i++] = GLX_ALPHA_SIZE;       /* 10 */
    visualAttribList[i++] = alphaDepthSize;       /* 11 */
    visualAttribList[i++] = GLX_STENCIL_SIZE;     /* 12 */
    visualAttribList[i++] = stencilBufferSize;    /* 13 */
    visualAttribList[i++] = None;                 /* 14 */
    visual = glXChooseVisual(display, DefaultScreen(display), 
			     visualAttribList);
  }

  return visual;
}



////////////////////////////////////////////////////////////////////////
// Implementations of our native methods.
////////////////////////////////////////////////////////////////////////



/* Let the current context go. */
JNIEXPORT void JNICALL Java_OpenGL_Context_nativeReleaseCurrentContext
  (JNIEnv *env, jclass class)
{
    int        error = 0;
    Display   *display = 0;

    if (!error) {
      GLXContext context;
      context = glXGetCurrentContext();
      if (NULL == context) {
	return; // There is no current context.
      }
    }

    if (!error) {
      display = glXGetCurrentDisplay();
      if (NULL == display) {
	error = 1;
	throwContextException(env, 
			      "Unable to get current display.");
      }
    }
    
    if (!error) {
      if (GL_FALSE == glXMakeCurrent(display, None, NULL)) {
	/* Something really bad must have happened. */
	throwContextException(env, 
			      "Unable to release the current context.");
      }
    }
}



/* Make the given context and canvas current. */
JNIEXPORT void JNICALL Java_OpenGL_Context_makeCanvasCurrent
  (JNIEnv *env, jobject contextObject, jlong jcontext, jobject canvas)
{
  CanvasInfo  info;
  GLXContext  context  = (GLXContext)(TO_POINTER(jcontext));
  int         error    = 0;

  if (!error && (context != 0)) {
    info = getCanvasInfo(env, canvas);
    error = (NULL == info.display) || (None == info.drawable);
  }
  
  if (!error) {
    fflush(stdout);
    if (GL_FALSE == glXMakeCurrent(info.display, info.drawable, context)) {
      error = 1;
    }
    fflush(stdout);
  }

  if (error) {
    /* Something went wrong, and we need to throw an exception. */
    throwContextException(env, "Unable to make the context current.");
  }

  freeCanvasInfo(env, info);
}



/* Create the context for a supplied canvas. */
JNIEXPORT jlong JNICALL Java_OpenGL_Context_createCanvasContext
  (JNIEnv *env, jobject contextObject, jobject canvas, jlong otherContext)
{
  CanvasInfo   info;
  GLXContext   context      = NULL;
  XVisualInfo *visualInfo   = NULL;
  int          error        = 0;
  jobject      capabilities = NULL;
  const char  *errorMessage = NULL;

  /* Get our capabilities object. */
  if (0 == getCapabilities(env, canvas, &capabilities)) {
    error = 1;
    errorMessage = "Unable to get the capabilities object for the canvas.";
  }

  /* Get the display variable. */
  if (!error) {
    info = getCanvasInfo(env, canvas);
    if ((NULL == info.display) || (None == info.drawable)) {
      error = 1;
      errorMessage = "Unable to get the X11 display for the canvas.";
    }
  }

  /* Find the right visual. */
  if (!error) {
    visualInfo = findVisual(info.display, env, capabilities);
    if (NULL == visualInfo) {
      error = 1;
      errorMessage = "Unable to get a matching visual for the canvas's capabilities.";
    }
  }

  /* Actually create the context, using our display, visualInfo, and possibly
     the shared context. */
  if (!error) {
    fflush(stdout);
    context = glXCreateContext(info.display, visualInfo, 
			       (GLXContext)(TO_POINTER(otherContext)), GL_TRUE);
    if (NULL == context) {
      error = 1;
      errorMessage = "Unable to create a context.";
    }
    fflush(stdout);
  }

  if (error) {
    /* Something went wrong, and we need to throw an exception. */
    throwContextException(env, errorMessage);
  }
  
  freeCanvasInfo(env, info);
  return FROM_POINTER(context);
}



/* Free the OpenGL context. */
JNIEXPORT void JNICALL Java_OpenGL_Context_deleteContext
  (JNIEnv *env, jobject contextObject, jlong context)
{
  glXDestroyContext(NULL, (GLXContext)(TO_POINTER(context)));
}


JNIEXPORT void JNICALL Java_OpenGL_Context_nativeFlushBuffer(JNIEnv *env, jobject jContextObject, jlong contextPointer)
{
	// swap or flush the contexts buffer
}
JNIEXPORT void JNICALL Java_OpenGL_Context_nativeSyncToVBL(JNIEnv *env, jobject jContextObject, jlong contextPointer, jboolean aFlag)
{
	// enable or disable vbl-sync here
}



