/*
 * OpenGL_GLUQuadric.c
 *
 * $Id: OpenGL_GLUQuadric.c,v 1.4 1999/01/26 23:55:44 razeh Exp $
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
#include "JNIInterface.h"
#include "CallbackObject.h"
#include "EnvDictionary.h"



////////////////////////////////////////////////////////////////////////
// Drawing functions.
////////////////////////////////////////////////////////////////////////



/* Set the drawing style for the quadric. */
JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_quadricDrawStyle
  (JNIEnv *env, jobject obj, jint quadric, jint drawStyle)
{
  gluQuadricDrawStyle((void*)quadric, drawStyle);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_quadricOrientation
  (JNIEnv *env, jobject obj, jint quadric, jint orientation)
{
  gluQuadricOrientation((void*) quadric, orientation);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_quadricNormals
  (JNIEnv *env, jobject obj, jint quadric, jint normals)
{
  gluQuadricNormals((void*)quadric, normals);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_quadricTexture
  (JNIEnv *env, jobject obj, jint quadric, jboolean texture)
{
  gluQuadricTexture((void*) quadric, texture);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_cylinder
  (JNIEnv *env, jobject obj, jint quadric, 
   jdouble baseRadius, jdouble topRadius, jdouble height, 
   jint slices, jint stacks)
{
  gluCylinder((void*)quadric, baseRadius, topRadius, height, slices, stacks);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_sphere
  (JNIEnv *env, jobject obj, jint quadric, jdouble radius, 
   jint slices, jint stacks)
{
  gluSphere((void*)quadric, radius, slices, stacks);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_disk
  (JNIEnv *env, jobject obj, jint quadric, jdouble innerRadius, 
   jdouble outerRadius, jint slices, jint loops)
{
  gluDisk((void*) quadric, innerRadius, outerRadius, slices, loops);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_partialDisk
  (JNIEnv *env, jobject obj, jint quadric, 
   jdouble innerRadius, jdouble outerRadius, 
   jint slices, jint loops, jdouble startAngle, jdouble sweepAngle)
{
  gluPartialDisk((void*)quadric, innerRadius, outerRadius, slices, loops, 
		 startAngle, sweepAngle);
}



////////////////////////////////////////////////////////////////////////
// Environment mapping.
////////////////////////////////////////////////////////////////////////



/* This returns the current tesselator that callbacks should use. */
static jobject getActiveQuadric(JNIEnv *env)
{
	jclass      quadricClass            = NULL;
	jobject     activeQuadric           = NULL;
	int         error                   = 0;

	// Get the tesselator class
	if (!error) {
		quadricClass = getClass(env, "OpenGL/GLUQuadric", 
			"Unable to get the OpenGL/GLUQuadric class.");
		error = (NULL == quadricClass);
	}

	activeQuadric = getActiveCallbackObjectForClass(env, quadricClass);
	
	return activeQuadric;
}


////////////////////////////////////////////////////////////////////////
// Callback functions.
////////////////////////////////////////////////////////////////////////

/* This handles the quadric error callback by trying to invoke the
current quadric's error(int) method. */
static void CALLBACK error(GLenum errorNumber)
{
	JNIEnv *env = environmentPointerForCurrentThread();

	if ((NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject    activeQuadric = getActiveQuadric(env);
		jmethodID  methodID      = NULL;

		methodID = getMethodIDForObject(env, activeQuadric, "error", "(I)V", "Unable to locate the error method.");
		if (NULL != methodID) {
			(*env)->CallVoidMethod(env, activeQuadric, methodID, errorNumber);
		}
	}
}



////////////////////////////////////////////////////////////////////////
// Creation and destruction functions.
////////////////////////////////////////////////////////////////////////



/* Creates a new quadric. */
JNIEXPORT jint JNICALL Java_OpenGL_GLUQuadric_newQuadric
  (JNIEnv *env, jobject obj)
{
	GLUquadric *newQuadric = gluNewQuadric();

	if (NULL != newQuadric) {
		gluQuadricCallback(newQuadric, GLU_ERROR, error);
	}
	return (int)newQuadric;
}



/* Deletes a quadric. */
JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_deleteQuadric
  (JNIEnv *env, jobject obj, jint quadric)
{
  gluDeleteQuadric((GLUquadric*) quadric);
}
