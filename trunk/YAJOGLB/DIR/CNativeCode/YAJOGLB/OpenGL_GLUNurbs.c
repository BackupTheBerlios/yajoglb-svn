/*
 * OpenGL_GLUQuadric.c
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements the native methods that allocate and free gluNurbs
 * for the OpenGL.GLUNurbs class, along with the drawing functions
 * for nurbs.
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
  return (int) gluNewNurbsRenderer();
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


JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluLoadSamplingMatrices
  (JNIEnv *env, jobject obj, jint nurbs, jfloatArray jmodelMatrix, 
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

  gluLoadSamplingMatrices((void*)nurbs, modelMatrix, projMatrix, viewport);

  (*env)->ReleaseIntArrayElements(env, jviewport, viewport, 0);
  (*env)->ReleaseFloatArrayElements(env, jmodelMatrix, modelMatrix, 0);
  (*env)->ReleaseFloatArrayElements(env, jprojMatrix, projMatrix, 0);

}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluNurbsProperty
 * Signature: (IIF)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluNurbsProperty
  (JNIEnv *env, jobject obj, jint nurbs, jint property, jfloat value)
{
  gluNurbsProperty((void*)nurbs, property, value);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluBeginCurve
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluBeginCurve((void*)nurb);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluEndCurve
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluEndCurve((void*)nurb);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluNurbsCurve
 * Signature: (I[FI[FII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluNurbsCurve
  (JNIEnv *env, jobject obj, jint nurb, 
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

  gluNurbsCurve((void*)nurb, knotCount,
	           knot, stride, ctlarray, order, type);
 
  (*env)->ReleaseFloatArrayElements(env, jknot, knot, 0);
  (*env)->ReleaseFloatArrayElements(env, jctlarray, ctlarray, 0);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluBeginSurface
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluBeginSurface
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluBeginSurface((void*) nurb);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluEndSurface
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluEndSurface
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluEndSurface((void*) nurb);
}


  
/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluNurbsSurface
 * Signature: (I[F[FII[FIII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluNurbsSurface
  (JNIEnv *env, jobject obj, 
   jint nurb, jfloatArray jsKnots, jfloatArray jtKnots, 
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

  gluNurbsSurface((void*)nurb, sKnotCount, sKnots, tKnotCount,
		  tKnots, sStride, tStride, control, sOrder, tOrder, type);

  
  (*env)->ReleaseFloatArrayElements(env, jsKnots, sKnots, 0);
  (*env)->ReleaseFloatArrayElements(env, jtKnots, tKnots, 0);
  (*env)->ReleaseFloatArrayElements(env, jcontrol, control, 0);
}



JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluGetNurbsProperty
  (JNIEnv *env, jobject obj, jint nurb, jint property, jfloatArray jvalue)
{
  jfloat *value;

  value = (*env)->GetFloatArrayElements(env, jvalue, 0);
  if (value == NULL)
    return;
  
  gluGetNurbsProperty((void*) nurb, property, value);

  (*env)->ReleaseFloatArrayElements(env, jvalue, value, 0);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluBeginTrim
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluBeginTrim
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluBeginTrim((void*) nurb);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluEndTrim
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluEndTrim
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluEndTrim((void*) nurb);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluPwlCurve
 * Signature: (I[FII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUNurbs_gluPwlCurve
  (JNIEnv *env, jobject obj, jint nurb, 
   jfloatArray jdata, jint stride, jint type)
{
  jfloat *data;
  jint count;

  data = (*env)->GetFloatArrayElements(env, jdata, 0);
  if (data == NULL)
    return;

  count = (*env)->GetArrayLength(env, jdata);

  gluPwlCurve((void*) nurb, count, data, stride, type);

  (*env)->ReleaseFloatArrayElements(env, jdata, data, 0);
}


