/*
 * OpenGL_OpenGLCanvas.c
 *
 * $Id: linux_OpenGL_Canvas.c,v 1.1 1999/02/13 19:27:40 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements the OpenGL methods needed to setup our canvas for OpenGL
 * rendering.  
 */

#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include <GL/glx.h>
#include <X11/X.h>
#include "OpenGL_OpenGLCanvas.h"
#include "SystemError.h"
#include "memory.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"
#include "linuxDPYDictionary.h"


/* Our native hook for setting up this canvas. */
JNIEXPORT jboolean JNICALL Java_OpenGL_OpenGLCanvas_setupOpenGLCanvas
  (JNIEnv *env, jobject canvas)
{
  /* Under X11 most of the setup is handled in the context creation. */
  return JNI_TRUE;
}



/* Swap the double buffers for this canvas. */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLCanvas_nativeSwapBuffers
  (JNIEnv *env, jobject canvas)
{
  Display    *display  = getDisplayForCanvas(env, canvas);
  GLXDrawable drawable = getDrawableForCanvas(env, canvas);
  
  glXSwapBuffers(display, drawable);
}



/* Returns the string for our data access class. */
JNIEXPORT jstring JNICALL Java_OpenGL_OpenGLCanvas_dataAccessClass
  (JNIEnv *env, jclass clasz)
{
  return (*env)->NewStringUTF(env, "sun.awt.motif.X11pDataAccess");
}
