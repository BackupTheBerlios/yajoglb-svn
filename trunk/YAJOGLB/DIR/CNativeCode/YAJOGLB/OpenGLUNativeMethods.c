/*
 * OpenGLUNativeMethods.c
 *
 * This implements the native method portions of the GLU library.
 * Quadrics are handled by the java CHeapItem class, which stores each
 * quadric as an integer.  When we receive a quadric for these native
 * methods we simply cast the integer into a void pointer.
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com) 
*/



/* With the Cygnus tools you need to include the GL stuff first. */
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "cygnusFixes.h"
#include "OpenGL_OpenGLWidget.h"

/* This file contains the actual native methods for the GLU library.
   It really only consists of a light linkage between the Java native
   method names and the GLU function names. 

   We expect to be able to cast an jint into a GLUquadric.
*/

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluQuadricDrawStyle
  (JNIEnv *env, jobject obj, jint quadric, jint drawStyle)
{
  gluQuadricDrawStyle((void*)quadric, drawStyle);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluQuadricOrientation
  (JNIEnv *env, jobject obj, jint quadric, jint orientation)
{
  gluQuadricOrientation((void*) quadric, orientation);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluQuadricNormals
  (JNIEnv *env, jobject obj, jint quadric, jint normals)
{
  gluQuadricNormals((void*)quadric, normals);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluQuadricTexture
  (JNIEnv *env, jobject obj, jobject quadric, jboolean texture)
{
  gluQuadricTexture((void*) quadric, texture);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluCylinder
  (JNIEnv *env, jobject obj, jint quadric, 
   jdouble baseRadius, jdouble topRadius, jdouble height, 
   jint slices, jint stacks)
{
  gluCylinder((void*)quadric, baseRadius, topRadius, height, slices, stacks);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluSphere
  (JNIEnv *env, jobject obj, jint quadric, jdouble radius, 
   jint slices, jint stacks)
{
  gluSphere((void*)quadric, radius, slices, stacks);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluDisk
  (JNIEnv *env, jobject obj, jint quadric, jdouble innerRadius, 
   jdouble outerRadius, jint slices, jint loops)
{
  gluDisk((void*) quadric, innerRadius, outerRadius, slices, loops);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluPartialDisk
  (JNIEnv *env, jobject obj, jint quadric, 
   jdouble innerRadius, jdouble outerRadius, 
   jint slices, jint loops, jdouble startAngle, jdouble sweepAngle)
{
  gluPartialDisk((void*)quadric, innerRadius, outerRadius, slices, loops, 
		 startAngle, sweepAngle);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluLoadSamplingMatrices
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
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluNurbsProperty
  (JNIEnv *env, jobject obj, jint nurbs, jint property, jfloat value)
{
  gluNurbsProperty((void*)nurbs, property, value);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluBeginCurve
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluBeginCurve((void*)nurb);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluEndCurve
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluEndCurve((void*)nurb);
}
/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluNurbsCurve
 * Signature: (I[FI[FII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluNurbsCurve
  (JNIEnv *env, jobject obj, jint nurb, 
   jfloatArray jknot, jint stride, 
   jfloatArray jctlarray, jint order, 
   jint type)
{
  jfloat *knot, *ctlarray;

  knot = (*env)->GetFloatArrayElements(env, jknot, 0);
  if (knot == NULL)
    return;
  
  ctlarray = (*env)->GetFloatArrayElements(env, jctlarray, 0);
  if (ctlarray == NULL) {
    (*env)->ReleaseFloatArrayElements(env, jknot, knot, 0);
    return;
  }

  /* THIS NEEDS MORE WORK */

  (*env)->ReleaseFloatArrayElements(env, jknot, knot, 0);

}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluBeginSurface
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluBeginSurface
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluBeginSurface((void*) nurb);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluEndSurface
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluEndSurface
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluEndSurface((void*) nurb);
}
  
/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluNurbsSurface
 * Signature: (I[F[FII[FIII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluNurbsSurface
  (JNIEnv *env, jobject obj, jint, jfloatArray, jfloatArray, jint, jint, jfloatArray, jint, jint, jint);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluBeginTrim
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluBeginTrim
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluBeginTrim((void*) nurb);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluEndTrim
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluEndTrim
  (JNIEnv *env, jobject obj, jint nurb)
{
  gluEndTrim((void*) nurb);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluPwlCurve
 * Signature: (I[FII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluPwlCurve
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

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluBeginPolygon
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluBeginPolygon
  (JNIEnv *env, jobject obj, jint tess)
{
  gluBeginPolygon((void*) tess);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluEndPolygon
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluEndPolygon
  (JNIEnv *env, jobject obj, jint tess)
{
  gluEndPolygon((void*) tess);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    gluNextContour
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_gluNextContour
  (JNIEnv *env, jobject obj, jint, jint);



JNIEXPORT jstring JNICALL Java_OpenGL_OpenGLWidget_gluGetString
  (JNIEnv *env, jobject obj, jint name)
{
  /* Note: For what ever reason, invoking this function will currently
     cause a core dump.  I suspect that because of some gnuwin32
     compiler/JNI interaction we are unable to return objects at
     all. */
  const char *string;
  string = gluGetString(name);
  return (*env)->NewStringUTF(env, string);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    project
 * Signature: (DDD[D[D[I[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_project
  (JNIEnv *env, jobject obj, 
   jdouble objX, jdouble objY, jdouble objZ, 
   jdoubleArray jmodel, jdoubleArray jproj, jintArray jview, 
   jdoubleArray jwinCoordinates)
{
  GLdouble winX,    winY,  winZ;
  GLdouble *model, *proj, *winCoordinates;
  GLint    *view, returnCode;

  model = (*env)->GetDoubleArrayElements(env, jmodel, 0);
  if (model == NULL)
    return;

  proj = (*env)->GetDoubleArrayElements(env, jproj, 0);
  if (proj == NULL) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
    return;
  }

  view = (*env)->GetIntArrayElements(env, jview, 0);
  if (view == NULL) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
    (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
    return;
  }

  winCoordinates = (*env)->GetDoubleArrayElements(env, jwinCoordinates, 0);
  if (winCoordinates == NULL) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
    (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
    (*env)->ReleaseIntArrayElements(env, jview, view, 0);
    return;
  }

  returnCode = gluProject(objX, objY, objZ,
			  model, proj, view,
			  &winX, &winY, &winZ);

  winCoordinates[0] = winX;
  winCoordinates[1] = winY;
  winCoordinates[2] = winZ;
  
  (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
  (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
  (*env)->ReleaseIntArrayElements(env, jview, view, 0);
  (*env)->ReleaseDoubleArrayElements(env, jwinCoordinates, winCoordinates, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    unProject
 * Signature: (DDD[D[D[I[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_unProject
  (JNIEnv *env, jobject obj, 
   jdouble winX, jdouble winY, jdouble winZ, 
   jdoubleArray jmodel, jdoubleArray jproj, 
   jintArray jview, jdoubleArray jobjCoordinates)
{
  GLdouble objX,    objY,  objZ;
  GLdouble *model, *proj, *objCoordinates;
  GLint    *view, returnCode;

  model = (*env)->GetDoubleArrayElements(env, jmodel, 0);
  if (model == NULL)
    return;

  proj = (*env)->GetDoubleArrayElements(env, jproj, 0);
  if (proj == NULL) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
    return;
  }

  view = (*env)->GetIntArrayElements(env, jview, 0);
  if (view == NULL) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
    (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
    return;
  }

  objCoordinates = (*env)->GetDoubleArrayElements(env, jobjCoordinates, 0);
  if (objCoordinates == NULL) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
    (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
    (*env)->ReleaseIntArrayElements(env, jview, view, 0);
    return;
  }

  returnCode = gluUnProject(winX, winY, winZ,
			    model, proj, view,
			    &objX, &objY, &objZ);

  objCoordinates[0] = winX;
  objCoordinates[1] = winY;
  objCoordinates[2] = winZ;
  
  (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
  (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
  (*env)->ReleaseIntArrayElements(env, jview, view, 0);
  (*env)->ReleaseDoubleArrayElements(env, jobjCoordinates, objCoordinates, 0);
}

