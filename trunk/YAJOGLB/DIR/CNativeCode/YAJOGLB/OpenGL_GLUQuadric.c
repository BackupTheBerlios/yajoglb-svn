/*
 * OpenGL_GLUQuadric.c
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements the native methods that allocate and free gluQuadrics
 * for the OpenGL.GLUQuadric class.
 */


#include <windows.h>
#include <GL/glu.h>

#include "cygnusFixes.h"
#include "OpenGL_GLUQuadric.h"


JNIEXPORT jint JNICALL Java_OpenGL_GLUQuadric_gluNewQuadric
  (JNIEnv *env, jobject obj)
{
  return (int) gluNewQuadric();
}

JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_gluDeleteQuadric
  (JNIEnv *env, jobject obj, jint quadric)
{
  gluDeleteQuadric((void*) quadric);
}
