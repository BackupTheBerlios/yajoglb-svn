
// Copyright 2004
// Alexander Spohr
// created by atze aet freeport de

#include <AppKit/AppKit.h>

#include "SystemIncludes.h"

JNIEXPORT void JNICALL Java_OpenGL_GL_viewport
(JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height)
{
	glViewport(x, y, width, height);
}

