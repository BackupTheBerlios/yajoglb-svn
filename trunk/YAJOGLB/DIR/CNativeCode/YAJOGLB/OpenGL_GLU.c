/*
  Implements the GLU basic functions.
 
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
 * OpenGL_GLU.c
 *
 * $Id: OpenGL_GLU.c,v 1.5 2001/07/06 23:40:05 razeh Exp $
 *
 * This implements the generic GLU methods.
 *
 */


/* With the Cygnus tools you need to include the GL stuff first. */
#include "SystemIncludes.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "cygnusFixes.h"
#include "OpenGL_GLU.h"
#include "JNIInterface.h"
#include "ErrorHandling.h"

/* This file contains the actual native methods for the GLU library.
   It really only consists of a light linkage between the Java native
   method names and the GLU function names. 

   We expect to be able to cast an jint into a GLUquadric, and a jint
   into a GLUnurbs.
*/


////////////////////////////////////////////////////////////////////////
// Transformation matrix methods.
////////////////////////////////////////////////////////////////////////



JNIEXPORT void JNICALL Java_OpenGL_GLU_gluLookAt
  (JNIEnv *env, jobject obj, 
   jdouble eye_x,    jdouble eye_y,    jdouble eye_z,
   jdouble center_x, jdouble center_y, jdouble center_z,
   jdouble up_x,     jdouble up_y,     jdouble up_z)
{
  gluLookAt(eye_x,    eye_y,    eye_z,
	    center_x, center_y, center_z,
	    up_x,     up_y,     up_z);
}



JNIEXPORT void JNICALL Java_OpenGL_GLU_gluOrtho2D
  (JNIEnv *env, jobject obj, jdouble left, jdouble right, 
   jdouble bottom, jdouble top)
{
  gluOrtho2D(left, right, bottom, top);
}



JNIEXPORT void JNICALL Java_OpenGL_GLU_gluPerspective
  (JNIEnv *env, jobject obj, jdouble fovy, jdouble aspect, 
   jdouble z_near, jdouble z_far)
{
  gluPerspective(fovy, aspect, z_near, z_far);
}



JNIEXPORT void JNICALL Java_OpenGL_GLU_gluPickMatrix
  (JNIEnv *env, jobject obj, jdouble x, jdouble y, 
   jdouble width, jdouble height, jintArray viewport)
{
  jint *viewportInts;
  viewportInts = (*env)->GetIntArrayElements(env, viewport, 0);
  if (viewportInts == NULL) {
	  handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
		  "Unable to map the pick matrix.");
	  return;
  }

  gluPickMatrix(x, y, width, height, (GLint*)viewportInts);
  (*env)->ReleaseIntArrayElements(env, viewport, viewportInts, 0);
}



JNIEXPORT jstring JNICALL Java_OpenGL_GLU_gluGetString
  (JNIEnv *env, jobject obj, jint name)
{
  const char *string;
  string = gluGetString(name);
  if (string != NULL)
     return (*env)->NewStringUTF(env, string);
  else 
    return NULL;
}



JNIEXPORT void JNICALL Java_OpenGL_GLU_gluProject
  (JNIEnv *env, jobject obj, 
   jdouble objX, jdouble objY, jdouble objZ, 
   jdoubleArray jmodel, jdoubleArray jproj, jintArray jview, 
   jdoubleArray jwinCoordinates)
{
  GLdouble winX,    winY,  winZ;
  GLdouble *model = NULL, *proj = NULL, *winCoordinates = NULL;
  GLint    returnCode;
  jint     *view  = NULL;
  model = (*env)->GetDoubleArrayElements(env, jmodel, 0);
  if (NULL == model) {
	  handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
		  "Unable to map the model.");
    return;
  }

  proj = (*env)->GetDoubleArrayElements(env, jproj, 0);
  if (NULL == proj) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
 	handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
		  "Unable to map the projection.");
   return;
  }

  view = (*env)->GetIntArrayElements(env, jview, 0);
  if (NULL == view) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
    (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
 	handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
		  "Unable to map the view.");
    return;
  }

  winCoordinates = (*env)->GetDoubleArrayElements(env, jwinCoordinates, 0);
  if (NULL == winCoordinates) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
    (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
    (*env)->ReleaseIntArrayElements(env, jview, view, 0);
 	handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
		  "Unable to map the window coordinates.");
    return;
  }

  returnCode = gluProject(objX, objY, objZ,
			  model, proj, (GLint*)view,
			  &winX, &winY, &winZ);

  winCoordinates[0] = winX;
  winCoordinates[1] = winY;
  winCoordinates[2] = winZ;
  
  (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
  (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
  (*env)->ReleaseIntArrayElements(env, jview, view, 0);
  (*env)->ReleaseDoubleArrayElements(env, jwinCoordinates, winCoordinates, 0);
}



JNIEXPORT void JNICALL Java_OpenGL_GLU_gluUnProject
  (JNIEnv *env, jobject obj, 
   jdouble winX, jdouble winY, jdouble winZ, 
   jdoubleArray jmodel, jdoubleArray jproj, 
   jintArray jview, jdoubleArray jobjCoordinates)
{
  GLdouble objX,    objY,  objZ;
  GLdouble *model = NULL, *proj = NULL, *objCoordinates = NULL;
  GLint    returnCode;
  jint     *view  = NULL;
  model = (*env)->GetDoubleArrayElements(env, jmodel, 0);
  if (model == NULL) {
  	handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
		  "Unable to map the model.");
    return;
  }

  proj = (*env)->GetDoubleArrayElements(env, jproj, 0);
  if (proj == NULL) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
  	handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
		  "Unable to map the projection.");
    return;
  }

  view = (*env)->GetIntArrayElements(env, jview, 0);
  if (view == NULL) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
    (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
  	handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
		  "Unable to map the view.");
    return;
  }

  objCoordinates = (*env)->GetDoubleArrayElements(env, jobjCoordinates, 0);
  if (objCoordinates == NULL) {
    (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
    (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
    (*env)->ReleaseIntArrayElements(env, jview, view, 0);
  	handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
		  "Unable to map the coordinates.");
    return;
  }

  returnCode = gluUnProject(winX, winY, winZ,
			    model, proj, (GLint*)view,
			    &objX, &objY, &objZ);

  objCoordinates[0] = winX;
  objCoordinates[1] = winY;
  objCoordinates[2] = winZ;
  
  (*env)->ReleaseDoubleArrayElements(env, jmodel, model, 0);
  (*env)->ReleaseDoubleArrayElements(env, jproj,  proj, 0);
  (*env)->ReleaseIntArrayElements(env, jview, view, 0);
  (*env)->ReleaseDoubleArrayElements(env, jobjCoordinates, objCoordinates, 0);
}



////////////////////////////////////////////////////////////////////////
// Mipmapping and image scaling.
////////////////////////////////////////////////////////////////////////



JNIEXPORT jint JNICALL Java_OpenGL_GLU_gluScaleImage
  (JNIEnv *env, jobject obj, 
   jint format, jint widthin, jint heightin, 
   jint typein, jobject jdatain, 
   jint widthout, jint heightout, jint typeout, 
   jobject jdataout)
{
  int result;
  void *datain = NULL, *dataout = NULL;
  jboolean isCopy;
  
  datain  = getArrayElements(env, jdatain, &isCopy).arrayElements;
  /* An exception should have been thrown, so this should work out ok. */
  if (datain == NULL)
    return NATIVE_PROBLEM;

  dataout = getArrayElements(env, jdataout, &isCopy).arrayElements;
  datain  = getArrayElements(env, jdatain, &isCopy).arrayElements;
  /* An exception should have been thrown, so this should work out ok. */
  if (dataout == NULL)
    return NATIVE_PROBLEM;
  
  result = gluScaleImage(format, 
			 widthin, heightin, typein, datain,
			 widthout, heightout, typeout, dataout);
  
  if (releaseArrayElements(env, jdatain, datain, JNI_ABORT) != 0) 
    /* Something went wrong and an exception was thrown, so just exit. */
    return NATIVE_PROBLEM;

  releaseArrayElements(env, jdataout, dataout, 0);
  
  return result;
}



JNIEXPORT jint JNICALL Java_OpenGL_GLU_gluBuild1DMipmaps__IIIII_3B
  (JNIEnv *env, jobject obj, 
   jint target, jint components, jint width, jint format, jint type, 
   jbyteArray jdata)
{
  GLbyte *data;
  GLint result;
  data = (*env)->GetByteArrayElements(env, jdata, 0);
  if (data == NULL)
    return -1;

  result 
    = gluBuild1DMipmaps(target, components, width, format, type, data);

  (*env)->ReleaseByteArrayElements(env, jdata, data, 0);
  
  return result;
}



JNIEXPORT jint JNICALL Java_OpenGL_GLU_gluBuild1DMipmaps__IIIII_3S
  (JNIEnv *env, jobject obj, 
   jint target, jint components, jint width, jint format, jint type, 
   jshortArray jdata)
{
  GLshort *data;
  GLint result;
  data = (*env)->GetShortArrayElements(env, jdata, 0);
  if (data == NULL)
    return -1;

  result 
    = gluBuild1DMipmaps(target, components, width, format, type, data);

  (*env)->ReleaseShortArrayElements(env, jdata, data, 0);
  
  return result;
}



JNIEXPORT jint JNICALL Java_OpenGL_GLU_gluBuild1DMipmaps__IIIII_3I
  (JNIEnv *env, jobject obj, 
   jint target, jint components, jint width, jint format, jint type, 
   jintArray jdata)
{
  jint *data;
  GLint result;
  data = (*env)->GetIntArrayElements(env, jdata, 0);
  if (data == NULL)
    return -1;

  result 
    = gluBuild1DMipmaps(target, components, width, format, type, (GLint*)data);

  (*env)->ReleaseIntArrayElements(env, jdata, data, 0);
  
  return result;
}



JNIEXPORT jint JNICALL Java_OpenGL_GLU_gluBuild1DMipmaps__IIIII_3F
  (JNIEnv *env, jobject obj, 
   jint target, jint components, jint width, jint format, jint type, 
   jfloatArray jdata)
{
  GLfloat *data;
  GLint result;
  data = (*env)->GetFloatArrayElements(env, jdata, 0);
  if (data == NULL)
    return -1;

  result 
    = gluBuild1DMipmaps(target, components, width, format, type, data);

  (*env)->ReleaseFloatArrayElements(env, jdata, data, 0);
  
  return result;
}



JNIEXPORT jint JNICALL Java_OpenGL_GLU_gluBuild2DMipmaps__IIIIII_3B
  (JNIEnv *env, jobject obj, 
   jint target, jint components, 
   jint width, jint height, jint format, jint type, jbyteArray jdata)
{
  GLbyte *data;
  GLint result;
  data = (*env)->GetByteArrayElements(env, jdata, 0);
  if (data == NULL)
    return -1;

  result 
    = gluBuild2DMipmaps(target, components, width, height, format, type, data);

  (*env)->ReleaseByteArrayElements(env, jdata, data, 0);
  
  return result;
}



JNIEXPORT jint JNICALL Java_OpenGL_GLU_gluBuild2DMipmaps__IIIIII_3S
  (JNIEnv *env, jobject obj, 
   jint target, jint components, 
   jint width, jint height, jint format, jint type, jshortArray jdata)
{
  GLshort *data;
  GLint result;
  data = (*env)->GetShortArrayElements(env, jdata, 0);
  if (data == NULL)
    return -1;

  result 
    = gluBuild2DMipmaps(target, components, width, height, format, type, data);

  (*env)->ReleaseShortArrayElements(env, jdata, data, 0);
  
  return result;
}



JNIEXPORT jint JNICALL Java_OpenGL_GLU_gluBuild2DMipmaps__IIIIII_3I
  (JNIEnv *env, jobject obj, 
   jint target, jint components, 
   jint width, jint height, jint format, jint type, jintArray jdata)
{
  jint *data;
  GLint result;
  data = (*env)->GetIntArrayElements(env, jdata, 0);
  if (data == NULL)
    return -1;

  result 
    = gluBuild2DMipmaps(target, components, width, height, format, type, (GLint*)data);

  (*env)->ReleaseIntArrayElements(env, jdata, data, 0);
  
  return result;
}



JNIEXPORT jint JNICALL Java_OpenGL_GLU_gluBuild2DMipmaps__IIIIII_3F
  (JNIEnv *env, jobject obj, 
   jint target, jint components, 
   jint width, jint height, jint format, jint type, jfloatArray jdata)
{
  GLfloat *data;
  jint     result;

  data = (*env)->GetFloatArrayElements(env, jdata, 0);
  if (data == NULL)
    return -1;

  result 
    = gluBuild2DMipmaps(target, components, width, height, format, type, data);

  (*env)->ReleaseFloatArrayElements(env, jdata, data, 0);
  
  return result;
}



JNIEXPORT jstring JNICALL Java_OpenGL_GLU_gluErrorString
  (JNIEnv *env, jobject obj, jint errorCode)
{
  return (*env)->NewStringUTF(env, gluErrorString(errorCode));
}
