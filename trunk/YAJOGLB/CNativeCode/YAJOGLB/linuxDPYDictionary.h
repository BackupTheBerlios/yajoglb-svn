/*
 * linuxDPYDictionary.h
 *
 * $Id$
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@yahoo.com)
 *
 * This allows access to the display and drawable from a canvas. 
 */



#include "SystemIncludes.h"
#include <GL/glx.h>
#include <X11/X.h>

#include <jawt_md.h>

typedef struct {
  Display *display;
  GLXDrawable drawable;
  JAWT_DrawingSurface *ds;
  JAWT_DrawingSurfaceInfo *dsi;
} CanvasInfo;


CanvasInfo getCanvasInfo(JNIEnv *env, jobject canvas);
void freeCanvasInfo(JNIEnv *env, CanvasInfo info);

