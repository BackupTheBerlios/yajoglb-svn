/*
 * OpenGL_GLUQuadric.c
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements the native methods that allocate and free gluNurbs
 * for the OpenGL.GLUNurbs class.
 */

#include <windows.h>
#include <GL/glu.h>

#include "cygnusFixes.h"
#include "OpenGL_GLUNurbs.h"

/*
 * Class:     OpenGL_GLUNurbs
 * Method:    gluNewNurbsRenderer
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_OpenGL_GLUNurbs_gluNewNurbsRenderer
  (JNIEnv *env, jobject obj)
{
  //return (int) gluNewNurbsRenderer();
  return 0;
}

/*
 * Class:     OpenGL_GLUNurbs
 * Method:    gluDeleteNurbsRenderer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluDeleteNurbsRenderer
  (JNIEnv *env, jobject obj, jint nurbs)
{
  gluDeleteNurbsRenderer((void*) nurbs); 
}

