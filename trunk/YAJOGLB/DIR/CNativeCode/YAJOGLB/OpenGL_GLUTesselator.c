/*
 * OpenGL_OpenGLTesselator.c
 *
 * $Id: OpenGL_GLUTesselator.c,v 1.1 1998/11/04 00:31:56 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements some of the native methods that are needed to support tesselators.
 */

#include <windows.h>
#include <GL/glu.h>

#include "cygnusFixes.h"
#include "OpenGL_GLUTesselator.h"

/* Returns a new tesselator. */
JNIEXPORT jint JNICALL Java_OpenGL_GLUTesselator_gluNewTess
  (JNIEnv *env, jobject obj)
{
	return (int) gluNewTess();
}

/*  Deletes a tesselator.  */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_gluDeleteTess
  (JNIEnv *env, jobject obj, jint tess)
{
	gluDeleteTess((void*) tess);
}

JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_gluTessBeginContour
  (JNIEnv *env, jobject obj, jint tess)
{
	gluTessBeginContour((void*) tess);
}

JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_gluTessBeginPolygon
  (JNIEnv *env, jobject obj, jint tess, jobject data)
{
	gluTessBeginPolygon((void*) tess, NULL);
}

JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_gluTessEndContour
  (JNIEnv *env, jobject obj, jint tess)
{
	gluTessEndContour((void*) tess);
}

JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_gluTessEndPolygon
  (JNIEnv *env, jobject obj, jint tess)
{
	gluTessEndPolygon((void*) tess);
}

JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_gluTessNormal
  (JNIEnv *env, jobject obj, jint tess, 
   jdouble valueX, jdouble valueY, jdouble valueZ)
{
	gluTessNormal((void*) tess, valueX, valueY, valueZ); 
}

/* Not done yet */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_gluTessVertex
  (JNIEnv *env, jobject obj, jint tess, jdoubleArray location, jobject data)
{

}


JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_gluTessProperty
  (JNIEnv *env, jobject obj, jint tess, jint which, jdouble data)
{
	gluTessProperty((void*) tess, which, data);
}


JNIEXPORT jdouble JNICALL Java_OpenGL_GLUTesselator_gluGetTessProperty
  (JNIEnv *env, jobject obj, jint tess, jint property)
{
	GLdouble dataOut;

	gluGetTessProperty((void*) tess, property, &dataOut);

	return dataOut;
}

