/*
 * linuxDPYDictionary.c
 *
 * $Id: linuxDPYDictionary.c,v 1.2 1999/03/24 01:47:00 razeh Exp $
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements the linux functions that aquire the display related
 * information from an OpenGLCanvas.  
 */

#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include "JNIInterface.h"
#include "ErrorHandling.h"
#include "linuxDPYDictionary.h"


/* Returns the display connection. */
Display* getDisplayForCanvas(JNIEnv* env, jobject canvas) 
{
  /* We are going to try creating our own display, rather than using
     the one provided by AWT.  If we use our own we do not have to worry
     about the synrchornization problems that arise from two toolkits 
     going through the same display connection. */
  static Display *ourOwnDisplay = NULL;

  if (NULL == ourOwnDisplay) {
    ourOwnDisplay = XOpenDisplay(NULL);
    if (NULL == ourOwnDisplay) {
      handleError(env, OPENGL_NATIVE_EXCEPTION, "Unable to obtain a display.");
    }
  }

  return ourOwnDisplay;
}



/* Gets the drawable for the canvas by asking for it. */
GLXDrawable getDrawableForCanvas(JNIEnv* env, jobject canvas)
{
  jmethodID    getDrawableMethodID = NULL;
  GLXDrawable  drawable = 0;
  jclass       canvasClass = (*env)->GetObjectClass(env, canvas);
  
  getDrawableMethodID = getMethodID(env, canvasClass, "getDrawable", "()I", "Unable to get the getDrawable() method.");
  if (getDrawableMethodID) {
    drawable = (GLXDrawable)(*env)->CallObjectMethod(env, canvas, getDrawableMethodID);
    if (0 == drawable) {
      handleError(env, OPENGL_NATIVE_EXCEPTION, "Unable to obtain a drawable for the canvas.");
    }
  } else {
      handleError(env, OPENGL_NATIVE_EXCEPTION, "Unable to get the getDrawable() method.");
  }
  return drawable;
}




