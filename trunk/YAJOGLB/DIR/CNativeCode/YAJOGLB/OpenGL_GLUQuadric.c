/*
  Support for GLU quadrics.
 
  Copyright 2001, Robert Allan Zeh (razeh@yahoo.com)
  7346 Lake Street #3W
  River Forest, IL 60305
 
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA

*/

/*
 * OpenGL_GLUQuadric.c
 *
 * $Id: OpenGL_GLUQuadric.c,v 1.7 2004/02/07 00:50:40 razeh Exp $
 *
 * This implements the native methods that allocate and free gluQuadrics
 * for the OpenGL.GLUQuadric class, along with the drawing functions for quadrics.
 */


#include "SystemIncludes.h"
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
  (JNIEnv *env, jobject obj, jlong quadric, jint drawStyle)
{
  gluQuadricDrawStyle(TO_POINTER(quadric), drawStyle);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_quadricOrientation
  (JNIEnv *env, jobject obj, jlong quadric, jint orientation)
{
  gluQuadricOrientation(TO_POINTER(quadric), orientation);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_quadricNormals
  (JNIEnv *env, jobject obj, jlong quadric, jint normals)
{
  gluQuadricNormals(TO_POINTER(quadric), normals);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_quadricTexture
  (JNIEnv *env, jobject obj, jlong quadric, jboolean texture)
{
  gluQuadricTexture(TO_POINTER(quadric), texture);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_cylinder
  (JNIEnv *env, jobject obj, jlong quadric, 
   jdouble baseRadius, jdouble topRadius, jdouble height, 
   jint slices, jint stacks)
{
  gluCylinder(TO_POINTER(quadric), baseRadius, topRadius, height, slices, stacks);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_sphere
  (JNIEnv *env, jobject obj, jlong quadric, jdouble radius, 
   jint slices, jint stacks)
{
  gluSphere(TO_POINTER(quadric), radius, slices, stacks);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_disk
  (JNIEnv *env, jobject obj, jlong quadric, jdouble innerRadius, 
   jdouble outerRadius, jint slices, jint loops)
{
  gluDisk(TO_POINTER(quadric), innerRadius, outerRadius, slices, loops);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_partialDisk
  (JNIEnv *env, jobject obj, jlong quadric, 
   jdouble innerRadius, jdouble outerRadius, 
   jint slices, jint loops, jdouble startAngle, jdouble sweepAngle)
{
  gluPartialDisk(TO_POINTER(quadric), innerRadius, outerRadius, slices, loops, 
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
JNIEXPORT jlong JNICALL Java_OpenGL_GLUQuadric_newQuadric
  (JNIEnv *env, jobject obj)
{
	GLUquadric *newQuadric = gluNewQuadric();

	if (NULL != newQuadric) {
		/* The cast is required because the gluQuadricCallback
		 * lies about it's type; _GLUfuncptr is declared not to take
		 * any arguments, although gluQuadricCallback takes an
		 * integer.
		 */
		gluQuadricCallback(newQuadric, GLU_ERROR, 
				   (_GLUfuncptr)error);
	}
	return FROM_POINTER(newQuadric);
}



/* Deletes a quadric. */
JNIEXPORT void JNICALL Java_OpenGL_GLUQuadric_deleteQuadric
  (JNIEnv *env, jobject obj, jlong quadric)
{
  gluDeleteQuadric((GLUquadric*)(TO_POINTER(quadric)));
}
