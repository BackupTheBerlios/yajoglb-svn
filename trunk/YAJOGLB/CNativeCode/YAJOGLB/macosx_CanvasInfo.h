// Copyright 2004
// Alexander Spohr
// created by atze aet freeport de


#include "jawt_md.h"

typedef struct {
	NSView *view;
	JAWT_DrawingSurface *ds;
	JAWT_DrawingSurfaceInfo *dsi;
} CanvasInfo;

CanvasInfo getCanvasInfo(JNIEnv *env, jobject canvas);
void freeCanvasInfo(JNIEnv *env, CanvasInfo info);
