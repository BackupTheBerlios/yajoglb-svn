/*
 * linuxDPYDictionary.c
 *
 * $Id: linuxDPYDictionary.c,v 1.1 1999/02/13 19:27:40 razeh Exp $
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
#include "linuxDPYDictionary.h"

/* Returns the display object for the canvas by asking the canvas for it. */
Display* getDisplayForCanvas(JNIEnv* env, jobject canvas) 
{
  jmethodID getDisplayMethodID = NULL;
  Display*  display = NULL;
  jclass    canvasClass = (*env)->GetObjectClass(env, canvas);
  
  getDisplayMethodID = getMethodID(env, canvasClass, "getDisplay", "()I", "Unable to get the getDisplay() method.");
  if (getDisplayMethodID) {
    display = (Display*) (*env)->CallIntMethod(env, canvas, getDisplayMethodID);
  }
  return display;
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
  }
  return drawable;
}




