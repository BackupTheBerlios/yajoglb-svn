/*
 * linuxDPYDictionary.h
 *
 * $Id: linuxDPYDictionary.h,v 1.1 1999/02/13 19:29:04 razeh Exp $
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This allows access to the display and drawable from a canvas. 
 */

#include "SystemIncludes.h"
#include <GL/glx.h>
#include <X11/X.h>

Display* getDisplayForCanvas(JNIEnv* env, jobject canvas);
GLXDrawable getDrawableForCanvas(JNIEnv* env, jobject canvas);
