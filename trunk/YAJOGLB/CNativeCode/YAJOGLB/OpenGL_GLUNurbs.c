/*
  Implements GLU nurbs.
 
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
 * $Id$
 *
 * This implements the native methods that allocate and free gluNurbs
 * for the OpenGL.GLUNurbs class, along with the drawing functions
 * for nurbs.
 */


#include "SystemIncludes.h"

#include "cygnusFixes.h"
#include "OpenGL_GLUNurbs.h"
#include "JNIInterface.h"
#include "ErrorHandling.h"
#include "OpenGL_GLUNurbs.h"
#include "CallbackObject.h"
#include "EnvDictionary.h"



////////////////////////////////////////////////////////////////////////
// Environment mapping.
////////////////////////////////////////////////////////////////////////



/* This returns the current tesselator that callbacks should use. */
static jobject getActiveNurbs(JNIEnv *env)
{
	jclass      nurbsClass              = NULL;
	jobject     activeNurbs             = NULL;
	int         error                   = 0;

	// Get the nurbs class
	if (!error) {
		nurbsClass = getClass(env, "OpenGL/GLUNurbs", 
			"Unable to get the OpenGL/GLUNubs class.");
		error = (NULL == nurbsClass);
	}

	activeNurbs = getActiveCallbackObjectForClass(env, nurbsClass);
	
	return activeNurbs;
}



////////////////////////////////////////////////////////////////////////
// Callback functions.
////////////////////////////////////////////////////////////////////////



/* This is the callback for GLU_NURBS_BEGIN. */
static void CALLBACK begin(GLenum type)
{
	JNIEnv *env = environmentPointerForCurrentThread();

	if ((NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject    activeNurbs   = getActiveNurbs(env);
		jmethodID  methodID      = NULL;

		methodID = getMethodIDForObject(env, activeNurbs, "begin", "(I)V", "Unable to locate the begin method.");
		if (NULL != methodID) {
			(*env)->CallVoidMethod(env, activeNurbs, methodID, type);
		}
	}
}



/* This handles the callback for GLU_NURBS_VERTEX. */
static void CALLBACK vertex(GLfloat *vertex)
{
	JNIEnv *env = environmentPointerForCurrentThread();

	if ((NULL != vertex) && (NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject    activeNurbs   = getActiveNurbs(env);
		jmethodID  methodID      = NULL;
		GLfloat    x, y, z;

		x = vertex[0]; y = vertex[1]; z = vertex[2];
		methodID = getMethodIDForObject(env, activeNurbs, "vertex", "(FFF)V", "Unable to locate the vertex method.");
		if (NULL != methodID) {
			(*env)->CallVoidMethod(env, activeNurbs, methodID, x, y, z);
		}
	}
}



/* This handles the callback for GLU_NURBS_NORMAL. */
static void CALLBACK normal(GLfloat *normal)
{
	JNIEnv *env = environmentPointerForCurrentThread();

	if ((NULL != normal) && (NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject    activeNurbs   = getActiveNurbs(env);
		jmethodID  methodID      = NULL;
		GLfloat    x, y, z;

		x = normal[0]; y = normal[1]; z = normal[2];
		methodID = getMethodIDForObject(env, activeNurbs, "normal", "(FFF)V", "Unable to locate the normal method.");
		if (NULL != methodID) {
			(*env)->CallVoidMethod(env, activeNurbs, methodID, x, y, z);
		}
	}
}



/* This handles the callback for GLU_NURBS_COLOR. */
static void CALLBACK color(GLfloat *color)
{
	JNIEnv *env = environmentPointerForCurrentThread();

	if ((NULL != color) && (NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject    activeNurbs   = getActiveNurbs(env);
		jmethodID  methodID      = NULL;
		GLfloat    r, g, b, a;

		r = color[0]; g = color[1]; b = color[2]; a = color[3];
		methodID = getMethodIDForObject(env, activeNurbs, "color", "(FFFF)V", "Unable to locate the color method.");
		if (NULL != methodID) {
			(*env)->CallVoidMethod(env, activeNurbs, methodID, r, g, b, a);
		}
	}
}



/* This handles the callback for GLU_NURBS_TEXTURE_COORD. */
static void CALLBACK texCoord(GLfloat *texCoord)
{
	unsigned int texCoordLength = 0;
	JNIEnv      *env = environmentPointerForCurrentThread();

	// First we have to figure out how long the texCoord array is.
	if (glIsEnabled(GL_MAP1_TEXTURE_COORD_1) || glIsEnabled(GL_MAP2_TEXTURE_COORD_1)) {
		texCoordLength = 1;
	}

	if (glIsEnabled(GL_MAP1_TEXTURE_COORD_2) || glIsEnabled(GL_MAP2_TEXTURE_COORD_2)) {
		texCoordLength = 2;
	}

	if (glIsEnabled(GL_MAP1_TEXTURE_COORD_3) || glIsEnabled(GL_MAP2_TEXTURE_COORD_3)) {
		texCoordLength = 3;
	}

	if (glIsEnabled(GL_MAP1_TEXTURE_COORD_4) || glIsEnabled(GL_MAP2_TEXTURE_COORD_4)) {
		texCoordLength = 4;
	}

	if (0 == texCoordLength) {
		handleError(env, OPENGL_NATIVE_EXCEPTION, "Unable to determine the texture coordinate length in the texCoord callback.");
	}

	if ((NULL != env) && (0 != texCoordLength) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject     activeNurbs   = getActiveNurbs(env);
		jmethodID   methodID      = NULL;
		jfloatArray jTexCoord     = (*env)->NewFloatArray(env, texCoordLength);

		// Create a Java array to hold texCoord.
		if (NULL != jTexCoord) {
			(*env)->SetFloatArrayRegion(env, jTexCoord, 0, texCoordLength, texCoord);
		} else {
			handleError(env, OPENGL_NATIVE_EXCEPTION, "Unable to allocate an array for the texCoord callback.");
			return;
		}

		methodID = getMethodIDForObject(env, activeNurbs, "texCoord", "([F)V", "Unable to locate the texCoord method.");
		if (NULL != methodID) {
			(*env)->CallVoidMethod(env, activeNurbs, methodID, jTexCoord);
		}
	}
}



/* This handles the callback for GLU_END. */
static void CALLBACK end(void)
{
	JNIEnv *env = environmentPointerForCurrentThread();

	if ((NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject    activeNurbs   = getActiveNurbs(env);
		jmethodID  methodID      = NULL;

		methodID = getMethodIDForObject(env, activeNurbs, "end", "()V", "Unable to locate the end method.");
		if (NULL != methodID) {
			(*env)->CallVoidMethod(env, activeNurbs, methodID);
		}
	}
}



/* This handles the error callback. */
static void CALLBACK error(GLenum errorNumber)
{
	JNIEnv *env = environmentPointerForCurrentThread();

	if ((NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject    activeNurbs   = getActiveNurbs(env);
		jmethodID  methodID      = NULL;

		methodID = getMethodIDForObject(env, activeNurbs, "error", "(I)V", "Unable to locate the error method.");
		if (NULL != methodID) {
			(*env)->CallVoidMethod(env, activeNurbs, methodID, errorNumber);
		}
	}
}


////////////////////////////////////////////////////////////////////////
// Creation and destruction functions.
////////////////////////////////////////////////////////////////////////

JNIEXPORT jlong JNICALL Java_OpenGL_GLUNurbs_newNurbsRenderer
  (JNIEnv *env, jobject obj)
{
  GLUnurbs *newNurbs = gluNewNurbsRenderer();

  if (NULL != newNurbs) {
    /* Assume that if GLU_NURBS_BEGIN_EXT is defined the rest are too. */
#ifdef GLU_NURBS_BEGIN_EXT
	  gluNurbsCallback(newNurbs, GLU_NURBS_BEGIN_EXT, begin);
	  gluNurbsCallback(newNurbs, GLU_NURBS_VERTEX_EXT, vertex);
	  gluNurbsCallback(newNurbs, GLU_NURBS_NORMAL_EXT, normal);
	  gluNurbsCallback(newNurbs, GLU_NURBS_COLOR_EXT, color);
	  gluNurbsCallback(newNurbs, GLU_NURBS_TEX_COORD_EXT, texCoord);
	  gluNurbsCallback(newNurbs, GLU_NURBS_END_EXT, end);
#endif
	  gluNurbsCallback(newNurbs, GLU_ERROR, error);
  }
  return FROM_POINTER(newNurbs);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_deleteNurbsRenderer
  (JNIEnv *env, jobject obj, jlong nurb)
{
  gluDeleteNurbsRenderer(TO_POINTER(nurb)); 
}




////////////////////////////////////////////////////////////////////////
// Drawing functions.
////////////////////////////////////////////////////////////////////////



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_loadSamplingMatrices
  (JNIEnv *env, jobject obj, jlong nurb, jfloatArray jmodelMatrix, 
   jfloatArray jprojMatrix, jintArray jviewport)
{
  jfloat *modelMatrix, *projMatrix;
  jint   *viewport;

  modelMatrix = (*env)->GetFloatArrayElements(env, jmodelMatrix, 0);
  if (modelMatrix == NULL)
    return;

  projMatrix = (*env)->GetFloatArrayElements(env, jprojMatrix, 0);
  if (projMatrix == NULL) {
    (*env)->ReleaseFloatArrayElements(env, jmodelMatrix, modelMatrix, 0);
  }

  viewport = (*env)->GetIntArrayElements(env, jviewport, 0);
  if (viewport == NULL) {
    (*env)->ReleaseFloatArrayElements(env, jmodelMatrix, modelMatrix, 0);
    (*env)->ReleaseFloatArrayElements(env, jprojMatrix, projMatrix, 0);
  }

  gluLoadSamplingMatrices(TO_POINTER(nurb), modelMatrix, projMatrix, (GLint*)viewport);

  (*env)->ReleaseIntArrayElements(env, jviewport, viewport, 0);
  (*env)->ReleaseFloatArrayElements(env, jmodelMatrix, modelMatrix, 0);
  (*env)->ReleaseFloatArrayElements(env, jprojMatrix, projMatrix, 0);

}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_nurbsProperty
  (JNIEnv *env, jobject obj, jlong nurb, jint property, jfloat value)
{
  gluNurbsProperty(TO_POINTER(nurb), property, value);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_beginCurve
  (JNIEnv *env, jobject obj, jlong nurb)
{
  gluBeginCurve(TO_POINTER(nurb));
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_endCurve
  (JNIEnv *env, jobject obj, jlong nurb)
{
  gluEndCurve(TO_POINTER(nurb));
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_nurbsCurve
  (JNIEnv *env, jobject obj, jlong nurb, 
   jfloatArray jknot, jint stride, 
   jfloatArray jctlarray, jint order, 
   jint type)
{
  jfloat *knot = NULL, *ctlarray = NULL;
  int knotCount;
  
  knot = (*env)->GetFloatArrayElements(env, jknot, 0);
  if (knot == NULL)
    return;
  knotCount = (*env)->GetArrayLength(env, jknot);
  
  ctlarray = (*env)->GetFloatArrayElements(env, jctlarray, 0);
  if (ctlarray == NULL) {
    (*env)->ReleaseFloatArrayElements(env, jknot, knot, 0);
    return;
  }

  gluNurbsCurve(TO_POINTER(nurb), knotCount,
	           knot, stride, ctlarray, order, type);
 
  (*env)->ReleaseFloatArrayElements(env, jknot, knot, 0);
  (*env)->ReleaseFloatArrayElements(env, jctlarray, ctlarray, 0);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_beginSurface
  (JNIEnv *env, jobject obj, jlong nurb)
{
  gluBeginSurface(TO_POINTER(nurb));
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_endSurface
  (JNIEnv *env, jobject obj, jlong nurb)
{
  gluEndSurface(TO_POINTER(nurb));
}


  
JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_nurbsSurface
  (JNIEnv *env, jobject obj, 
   jlong nurb, jfloatArray jsKnots, jfloatArray jtKnots, 
   jint sStride, jint tStride, jfloatArray jcontrol, 
   jint sOrder, jint tOrder, jint type)
{
  jint sKnotCount, tKnotCount;
  jfloat *sKnots = NULL, *tKnots = NULL, *control = NULL;

  sKnotCount = (*env)->GetArrayLength(env, jsKnots);
  tKnotCount = (*env)->GetArrayLength(env, jtKnots);

  sKnots = (*env)->GetFloatArrayElements(env, jsKnots, 0);
  if (sKnots == NULL)
    return;

  tKnots = (*env)->GetFloatArrayElements(env, jtKnots, 0);
  if (tKnots == NULL) {
    (*env)->ReleaseFloatArrayElements(env, jsKnots, sKnots, 0);
  }
  
  control = (*env)->GetFloatArrayElements(env, jcontrol, 0);
  if (control == NULL) {
    (*env)->ReleaseFloatArrayElements(env, jsKnots, sKnots, 0);
    (*env)->ReleaseFloatArrayElements(env, jtKnots, tKnots, 0);
  }

  gluNurbsSurface(TO_POINTER(nurb), sKnotCount, sKnots, tKnotCount,
		  tKnots, sStride, tStride, control, sOrder, tOrder, type);

  
  (*env)->ReleaseFloatArrayElements(env, jsKnots, sKnots, 0);
  (*env)->ReleaseFloatArrayElements(env, jtKnots, tKnots, 0);
  (*env)->ReleaseFloatArrayElements(env, jcontrol, control, 0);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_getNurbsProperty
  (JNIEnv *env, jobject obj, jlong nurb, jint property, jfloatArray jvalue)
{
  jfloat *value;

  value = (*env)->GetFloatArrayElements(env, jvalue, 0);
  if (value == NULL)
    return;
  
  gluGetNurbsProperty(TO_POINTER(nurb), property, value);

  (*env)->ReleaseFloatArrayElements(env, jvalue, value, 0);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_beginTrim
  (JNIEnv *env, jobject obj, jlong nurb)
{
  gluBeginTrim(TO_POINTER(nurb));
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_endTrim
  (JNIEnv *env, jobject obj, jlong nurb)
{
  gluEndTrim(TO_POINTER(nurb));
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_pwlCurve
  (JNIEnv *env, jobject obj, jlong nurb, 
   jfloatArray jdata, jint stride, jint type)
{
  jfloat *data;
  jint count;

  data = (*env)->GetFloatArrayElements(env, jdata, 0);
  if (data == NULL)
    return;

  count = (*env)->GetArrayLength(env, jdata);

  gluPwlCurve(TO_POINTER(nurb), count, data, stride, type);

  (*env)->ReleaseFloatArrayElements(env, jdata, data, 0);
}


