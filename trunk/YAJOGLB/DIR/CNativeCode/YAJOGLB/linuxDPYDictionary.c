/*
 * linuxDPYDictionary.c
 *
 * $Id: linuxDPYDictionary.c,v 1.3 1999/05/03 00:04:35 razeh Exp $
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


/* Get the data access object for a canvas.  We can then use the data
   access object to get the Display and Drawable for the canvas. */
static jobject getDataAccess(JNIEnv*env, jobject canvas)
{
  jmethodID getDataAccessMethodID = NULL;
  jclass    canvasClass = (*env)->GetObjectClass(env, canvas);  
  jobject   dataAccess = NULL;

  getDataAccessMethodID = 
    getMethodID(env, canvasClass, "getDataAccess", 
		"()LOpenGL/OpenGLpDataAccess;", 
		"Unable to get the getDataAccess() method.");

  if (NULL != getDataAccessMethodID) {
    /* Now get the data access object for our canvas. */
    dataAccess = (*env)->CallObjectMethod(env, canvas, getDataAccessMethodID);
  }

  return dataAccess;
}


/* Returns the display connection for canvas.  We end up opening up a
   single display for each canvas.  I've tried using the display that the
   AWT opens up for the canvas, and that doesn't work --- the display
   dies after complaining about synchronization problems.  I've tried
   using a single display for all of the canvas objects, and that works
   for a while.  Eventually, however, the windows freeze up.  */
Display* getDisplayForCanvas(JNIEnv* env, jobject canvas) 
{
  jobject dataAccess = getDataAccess(env, canvas);
  Display* display = NULL;

  if (NULL != dataAccess) {
    jclass    dataAccessClass = (*env)->GetObjectClass(env, dataAccess);
    jmethodID getDisplayMethodID = NULL;
    
    getDisplayMethodID = getMethodID(env, dataAccessClass, "getDisplay",
				     "()I", 
				     "Unable to get the getDisplay() method.");
    if (NULL != getDisplayMethodID) {
      /* Make sure that only one thread is doing this at a time. */
      (*env)->MonitorEnter(env, canvas);
      
      display = (Display*) (*env)->CallIntMethod(env, dataAccess, getDisplayMethodID);
      
      /* The display hasn't been set yet, so we have to set it here. */
      if (NULL == display) {
	jmethodID setDisplayMethodID = 
	  getMethodID(env, dataAccessClass, "setDisplay", "(I)V",
		      "Unable to get the setDisplay(int) method.");
	display = XOpenDisplay(NULL);
	(*env)->CallVoidMethod(env, dataAccess, setDisplayMethodID, (int) display);
      }
      /* Let other threads have at the canvas object. */
      (*env)->MonitorExit(env, canvas);
    }
  }

  return display;
}



/* Gets the drawable for the canvas by asking the data access object
   hanging off the canvas for it. */
GLXDrawable getDrawableForCanvas(JNIEnv* env, jobject canvas)
{
  jobject      dataAccess = getDataAccess(env, canvas);
  GLXDrawable  drawable = 0;

  if (NULL != dataAccess) {
    jmethodID    getDrawableMethodID = NULL;
    jclass       dataAccessClass = (*env)->GetObjectClass(env, dataAccess);
  
    getDrawableMethodID = getMethodID(env, dataAccessClass, "getDrawable", "(Ljava/awt/Canvas;)I", "Unable to get the getDrawable() method.");

    if (NULL != getDrawableMethodID) {
      drawable = (GLXDrawable)(*env)->CallObjectMethod(env, dataAccess, getDrawableMethodID, canvas);
      if (0 == drawable) {
	handleError(env, OPENGL_NATIVE_EXCEPTION, "Unable to obtain a drawable for the canvas.");
      }
    }
  }

  return drawable;
}




