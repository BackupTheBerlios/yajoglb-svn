/*
 * CanvasInfo.h
 *
 * $Id: $
 *
 * Methods for getting to Canvas information.
 */

#ifndef _CANVASINFO_H
#define _CANVASINFO_H

#include <jawt.h>

typedef struct {
  JAWT awt;
  JAWT_DrawingSurface *ds;
  JAWT_DrawingSurfaceInfo *dsi;
} CanvasInfo;

CanvasInfo getCanvasInfo(JNIEnv *env, jobject canvas);
void freeCanvasInfo(JNIEnv *env, CanvasInfo info);

#endif
