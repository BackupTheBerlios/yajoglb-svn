/*
 * OpenGL_GLUQuadric.c
 *
 * $Id: OpenGL_GLUQuadric.c,v 1.3 1998/11/04 00:31:44 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements the native methods that allocate and free gluQuadrics
 * for the OpenGL.GLUQuadric class, along with the drawing functions for quadrics.
 */


#include <windows.h>
#include <GL/glu.h>

#include "cygnusFixes.h"
#include "OpenGL_GLUQuadric.h"

/* Creates a new quadric. */
JNIEXPORT jint JNICALL Java_OpenGL_GLUQuadric_gluNewQuadric
  (JNIEnv *env, jobject obj)
{
  return (int) gluNewQuadric();
}


/* Deletes a quadric. */
JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_gluDeleteQuadric
  (JNIEnv *env, jobject obj, jint quadric)
{
  gluDeleteQuadric((void*) quadric);
}




JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_gluQuadricDrawStyle
  (JNIEnv *env, jobject obj, jint quadric, jint drawStyle)
{
  gluQuadricDrawStyle((void*)quadric, drawStyle);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_gluQuadricOrientation
  (JNIEnv *env, jobject obj, jint quadric, jint orientation)
{
  gluQuadricOrientation((void*) quadric, orientation);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_gluQuadricNormals
  (JNIEnv *env, jobject obj, jint quadric, jint normals)
{
  gluQuadricNormals((void*)quadric, normals);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_gluQuadricTexture
  (JNIEnv *env, jobject obj, jint quadric, jboolean texture)
{
  gluQuadricTexture((void*) quadric, texture);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_gluCylinder
  (JNIEnv *env, jobject obj, jint quadric, 
   jdouble baseRadius, jdouble topRadius, jdouble height, 
   jint slices, jint stacks)
{
  gluCylinder((void*)quadric, baseRadius, topRadius, height, slices, stacks);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_gluSphere
  (JNIEnv *env, jobject obj, jint quadric, jdouble radius, 
   jint slices, jint stacks)
{
  gluSphere((void*)quadric, radius, slices, stacks);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_gluDisk
  (JNIEnv *env, jobject obj, jint quadric, jdouble innerRadius, 
   jdouble outerRadius, jint slices, jint loops)
{
  gluDisk((void*) quadric, innerRadius, outerRadius, slices, loops);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_gluPartialDisk
  (JNIEnv *env, jobject obj, jint quadric, 
   jdouble innerRadius, jdouble outerRadius, 
   jint slices, jint loops, jdouble startAngle, jdouble sweepAngle)
{
  gluPartialDisk((void*)quadric, innerRadius, outerRadius, slices, loops, 
		 startAngle, sweepAngle);
}


