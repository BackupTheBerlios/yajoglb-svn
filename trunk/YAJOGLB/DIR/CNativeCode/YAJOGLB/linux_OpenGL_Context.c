/*
 * OpenGL_OpenGLContext.c
 *
 * $Id: linux_OpenGL_Context.c,v 1.1 1999/02/13 19:27:40 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements the native methods for OpenGLContext --- methods that 
 * create, manipulate, and destroy the current OpenGL context.
 */

#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include <X11/X.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include "OpenGL_OpenGLContext.h"
#include "SystemError.h"
#include "JNIInterface.h"
#include "Memory.h"
#include "ErrorHandling.h"
#include "linuxDPYDictionary.h"
#include "OpenGLCapabilitiesAccessors.h"

/* Our context exception class. */
#define OPENGL_CONTEXT_EXCEPTION "OpenGL/OpenGLContextException"



////////////////////////////////////////////////////////////////////////
// Functions for our private use.
////////////////////////////////////////////////////////////////////////

/* This throws an OpenGLContextException Java exception that uses the current
   system error as the error message. */
static void throwContextException(JNIEnv *env, const char *errorMessage)
{
  handleError(env, OPENGL_CONTEXT_EXCEPTION, errorMessage);
}


/* Get the OpenGLCapabilities object for the supplied canvas.  We
   return 0 if everything worked out and non-zero otherwise. */
static int getCapabilities(JNIEnv *env, jobject canvas, jobject *capabilities)
{
  jclass    canvasClass  = NULL;
  jmethodID methodID     = NULL;
  int       error        = 0;

  canvasClass = (*env)->GetObjectClass(env, canvas);
  methodID = getMethodID(env, canvasClass, 
			 "capabilities", "()LOpenGL/OpenGLCapabilities;",
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
JNIEXPORT void JNICALL Java_OpenGL_OpenGLContext_nativeReleaseCurrentContext
  (JNIEnv *env, jclass class)
{
  if (GL_FALSE == glXMakeCurrent(NULL, None, NULL)) {
    /* Something really bad must have happened. */
    throwContextException(env, "Unable to release the current context.");
  }
}



/* Make the given context and canvas current. */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLContext_makeCanvasCurrent
  (JNIEnv *env, jobject contextObject, jint jcontext, jobject canvas)
{
  Display    *display  = NULL;
  GLXDrawable drawable = 0;
  GLXContext  context  = (GLXContext)jcontext;
  int         error    = 0;

  if (!error && (context != 0)) {
    display = getDisplayForCanvas(env, canvas);
    drawable = getDrawableForCanvas(env, canvas);
    error = (NULL == display) || (None == drawable);
  }
  
  if (!error) {
    if (GL_FALSE == glXMakeCurrent(display, drawable, context)) {
      error = 1;
    }
  }

  if (error) {
    /* Something went wrong, and we need to throw an exception. */
    throwContextException(env, "Unable to make the context current.");
  }
}



/* Create the context for a supplied canvas. */
JNIEXPORT jint JNICALL Java_OpenGL_OpenGLContext_createCanvasContext
  (JNIEnv *env, jobject contextObject, jobject canvas, jint otherContext)
{
  Display     *display      = NULL;
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
    display = getDisplayForCanvas(env, canvas);
    if (NULL == display) {
      error = 1;
      errorMessage = "Unable to get the X11 display for the canvas.";
    }
  }

  /* Find the right visual. */
  if (!error) {
    visualInfo = findVisual(display, env, capabilities);
    if (NULL == visualInfo) {
      error = 1;
      errorMessage = "Unable to get a matching visual for the canvas's capabilities.";
    }
  }

  /* Actually create the context, using our display, visualInfo, and possibly
     the shared context. */
  if (!error) {
    context = glXCreateContext(display, visualInfo, 
			       (GLXContext)otherContext, GL_TRUE);
    if (NULL == context) {
      error = 1;
      errorMessage = "Unable to create a context.";
    }
  }

  if (error) {
    /* Something went wrong, and we need to throw an exception. */
    throwContextException(env, errorMessage);
  }
  
  return (int) context;
}



/* Free the OpenGL context. */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLContext_deleteContext
  (JNIEnv *env, jobject contextObject, jint context)
{
  printf("delete context\n");
  glXDestroyContext(NULL, (GLXContext)context);
}

