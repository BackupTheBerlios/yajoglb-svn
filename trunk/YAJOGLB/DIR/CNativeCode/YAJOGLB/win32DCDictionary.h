/*
 * win32DCDictionary.h
 *
 * $Id: win32DCDictionary.h,v 1.2 2001/07/06 23:41:30 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */



#include <windows.h>

#ifdef USE_JAWT
#include "jawt_md.h"
#endif

typedef struct {
	HDC hDC;
#ifdef USE_JAWT
	JAWT_DrawingSurface *ds;
	JAWT_DrawingSurfaceInfo *dsi;
#endif
} CanvasInfo;

CanvasInfo getCanvasInfo(JNIEnv *env, jobject canvas);
void freeCanvasInfo(JNIEnv *env, CanvasInfo info);
