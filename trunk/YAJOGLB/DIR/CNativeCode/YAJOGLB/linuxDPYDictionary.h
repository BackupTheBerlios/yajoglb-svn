/*
 * linuxDPYDictionary.h
 *
 * $Id: linuxDPYDictionary.h,v 1.2 2001/07/06 23:41:24 razeh Exp $
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@yahoo.com)
 *
 * This allows access to the display and drawable from a canvas. 
 */



#include "SystemIncludes.h"
#include <GL/glx.h>
#include <X11/X.h>

#ifdef USE_JAWT
#include <jawt_md.h>
#endif

typedef struct {
  Display *display;
  GLXDrawable drawable;
#ifdef USE_JAWT
  JAWT_DrawingSurface *ds;
  JAWT_DrawingSurfaceInfo *dsi;
#endif
} CanvasInfo;


CanvasInfo getCanvasInfo(JNIEnv *env, jobject canvas);
void freeCanvasInfo(JNIEnv *env, CanvasInfo info);

