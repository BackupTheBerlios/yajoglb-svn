/*
 * OpenGLNativeMethods.c
 *
 * $Id: OpenGLNativeMethods.c,v 1.2 1998/11/01 21:42:58 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com) 
 */


/* With the Cygnus tools you need to include the GL stuff first. */
#include <windows.h>
#include <GL/gl.h>

#include "cygnusFixes.h"
#include "ErrorHandling.h"
#include "OpenGL_OpenGLWidget.h"
#include "memory.h"
#include "JNIInterface.h"

/* This file contains the actual native methods for OpenGL.  It really
   only consists of name linkage between the mangled Java native
   method names and the OpenGL function names.  When the OpenGL API
   expects to receive an array we have to pin it down, but other than
   that we pretty much just pass in the arguments that we are
   given. */



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    clearIndex
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_clearIndex
  (JNIEnv *env, jobject obj, jfloat c)
{
  glClearIndex(c);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_clearColor
  (JNIEnv *env, jobject obj, jfloat red, jfloat green, jfloat blue, 
   jfloat alpha) {
    glClearColor(red, green, blue, alpha);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_clear
  (JNIEnv *env, jobject obj, jint mask) {
    glClear(mask);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_indexMask
  (JNIEnv *env, jobject obj, jint mask) {
    glIndexMask(mask);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_colorMask
  (JNIEnv *env, jobject obj, jboolean red, jboolean green, jboolean blue,
   jboolean alpha) {
    GLboolean glRed  = GL_TRUE, glGreen = GL_TRUE, 
              glBlue = GL_TRUE, glAlpha  = GL_TRUE;
    if (red == JNI_FALSE)
      glRed = GL_FALSE;
    if (green == JNI_FALSE)
      glGreen = GL_FALSE;
    if (blue == JNI_FALSE)
      glBlue = GL_FALSE;
    if (alpha == JNI_FALSE)
      glAlpha = GL_FALSE;
    glColorMask(glRed, glGreen, glBlue, glAlpha);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_alphaFunc
  (JNIEnv *env, jobject obj, jint func, jfloat value) {
    glAlphaFunc(func, value);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_blendFunc
  (JNIEnv *env, jobject obj, jint sfactor, jint dfactor) {
    glBlendFunc(sfactor, dfactor);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_logicOp
  (JNIEnv *env, jobject obj, jint opcode) {
    glLogicOp(opcode);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_cullFace
  (JNIEnv *env, jobject obj, jint mode) {
    glCullFace(mode);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_frontFace
  (JNIEnv *env, jobject obj, jint mode) {
    glFrontFace(mode);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pointSize
  (JNIEnv *env, jobject obj, jfloat size) {
    glPointSize(size);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_lineWidth
  (JNIEnv *env, jobject obj, jfloat width) {
    glLineWidth(width);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_lineStipple
  (JNIEnv *env, jobject obj, jint factor, jshort pattern) {
    glLineStipple(factor, pattern);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_polygonMode
  (JNIEnv *env, jobject obj, jint face, jint mode) {
    glPolygonMode(face, mode);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_polygonOffset
(JNIEnv *env, jobject obj, jfloat factor, jfloat units) {
  glPolygonOffset(factor, units);
} 



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_polygonStipple
  (JNIEnv *env, jobject obj, jbyteArray mask)
{
  GLbyte *maskBytes;

  maskBytes = (*env)->GetByteArrayElements(env, mask, 0);
  if (maskBytes == NULL)
    return;
  glPolygonStipple(maskBytes);
  (*env)->ReleaseByteArrayElements(env, mask, maskBytes, JNI_ABORT);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getPolygonStipple
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getPolygonStipple
  (JNIEnv *env, jobject obj, jbyteArray mask)
{
  GLbyte *maskBytes;

  maskBytes = (*env)->GetByteArrayElements(env, mask, 0);
  if (maskBytes == NULL)
    return;
  glGetPolygonStipple(maskBytes);
  (*env)->ReleaseByteArrayElements(env, mask, maskBytes, 0);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_edgeFlag
  (JNIEnv *env, jobject obj, jboolean flag)
{
  glEdgeFlag(flag);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_scissor
  (JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height)
{
  glScissor(x, y, width, height);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    clipPlane
 * Signature: (I[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_clipPlane
  (JNIEnv *env, jobject obj, jint plane, jdoubleArray equation)
{
  GLdouble *equationDoubles;
  
  equationDoubles = (*env)->GetDoubleArrayElements(env, equation, 0);
  if (equationDoubles == NULL)
    return;
  glClipPlane(plane, equationDoubles);
  (*env)->ReleaseDoubleArrayElements(env, equation, equationDoubles, 
				     JNI_ABORT);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getClipPlane
 * Signature: (I[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getClipPlane
  (JNIEnv *env, jobject obj, jint plane, jdoubleArray equation)
{
  GLdouble *equationDoubles;
  
  equationDoubles = (*env)->GetDoubleArrayElements(env, equation, 0);
  if (equationDoubles == NULL)
    return;
  glGetClipPlane(plane, equationDoubles);
  (*env)->ReleaseDoubleArrayElements(env, equation, equationDoubles, 0);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    drawBuffer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_drawBuffer
  (JNIEnv *env, jobject obj, jint mode)
{
  glDrawBuffer(mode);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    readBuffer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_readBuffer
  (JNIEnv *env, jobject obj, jint mode)
{
  glReadBuffer(mode);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_enable
  (JNIEnv *env, jobject obj, jint capability)
{
  glEnable(capability);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_disable
  (JNIEnv *env, jobject obj, jint capability)
{
  glDisable(capability);
}



JNIEXPORT jboolean JNICALL Java_OpenGL_OpenGLWidget_isEnabled
  (JNIEnv *env, jobject obj, jint capability)
{
  return glIsEnabled(capability) == JNI_TRUE;
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_get__I_3Z
  (JNIEnv *env, jobject obj, jint pname, jbooleanArray jparams)
{
  jboolean *params;
  params = (*env)->GetBooleanArrayElements(env, jparams, 0);
  if (params == NULL)
    return;
  glGetBooleanv(pname, params);
  (*env)->ReleaseBooleanArrayElements(env, jparams, params,0);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_get__I_3D
  (JNIEnv *env, jobject obj, jint pname, jdoubleArray jparams)
{
  jdouble *params;
  params = (*env)->GetDoubleArrayElements(env, jparams, 0);
  if (params == NULL)
    return;
  glGetDoublev(pname, params);
  (*env)->ReleaseDoubleArrayElements(env, jparams, params,0);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_get__I_3F
  (JNIEnv *env, jobject obj, jint pname, jfloatArray jparams)
{
  GLfloat *params;
  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;
  glGetFloatv(pname, params);
  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_get__I_3I
  (JNIEnv *env, jobject obj, jint pname, jintArray jparams)
{
  GLint *params;
  params = (*env)->GetIntArrayElements(env, jparams, 0);
  if (params == NULL)
    return;
  glGetIntegerv(pname, params);
  (*env)->ReleaseIntArrayElements(env, jparams, params,0);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pushAttrib
  (JNIEnv *env, jobject obj, jint mask)
{
  glPushAttrib(mask);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_popAttrib
  (JNIEnv *env, jobject obj)
{
  glPopAttrib();
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pushClientAttrib
  (JNIEnv *env, jobject obj, jint mask)
{
  glPushClientAttrib(mask);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_popClientAttrib
  (JNIEnv *env, jobject obj)
{
  glPopClientAttrib();
}



JNIEXPORT jint JNICALL Java_OpenGL_OpenGLWidget_renderMode
  (JNIEnv *env, jobject obj, jint mode)
{
  return glRenderMode(mode);
}



JNIEXPORT jint JNICALL Java_OpenGL_OpenGLWidget_getError
  (JNIEnv *env, jobject obj)
{
  return glGetError();
}



JNIEXPORT jstring JNICALL Java_OpenGL_OpenGLWidget_getString
  (JNIEnv *env, jobject obj, jint name)
{
  const char *string;
  string = glGetString(name);
  if (string != NULL)
    return (*env)->NewStringUTF(env, string);
  else 
    return NULL;
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    finish
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_finish
  (JNIEnv *env, jobject obj)
{
  glFinish();
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    flush
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_flush
  (JNIEnv *env, jobject obj)
{
  glFlush();
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    hint
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_hint
  (JNIEnv *env, jobject obj, jint target, jint mode)
{
  glHint(target, mode);
}



/*
 * Depth Buffer
 */

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_clearDepth
  (JNIEnv *env, jobject obj, jdouble depth)
{
  glClearDepth(depth);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_depthFunc
  (JNIEnv *env, jobject obj, jint func) 
{
  glDepthFunc(func);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_depthMask
  (JNIEnv *env, jobject obj, jboolean flag)
{
  glDepthMask(flag);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_depthRange
  (JNIEnv *env, jobject obj, jdouble near_val, jdouble far_val)
{
  glDepthRange(near_val, far_val);
}



  /*
   * Accumulation buffer
   */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_clearAccum
  (JNIEnv *env, jobject obj, jfloat red, jfloat green, jfloat blue, 
   jfloat alpha)
{
  glClearAccum(red, green, blue, alpha);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_accum
  (JNIEnv *env, jobject obj, jint op, jfloat value)
{
  glAccum(op, value);
}



/*
 * Transformation
 */

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_matrixMode
  (JNIEnv *env, jobject obj, jint mode)
{
  glMatrixMode(mode);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_ortho
  (JNIEnv *env, jobject obj, 
   jdouble left, jdouble right, 
   jdouble bottom, jdouble top, 
   jdouble near_val, jdouble far_val)
{
  glOrtho(left, right,
	  bottom, top, 
	  near_val, far_val);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_frustum
  (JNIEnv *env, jobject obj, 
   jdouble left, jdouble right, 
   jdouble bottom, jdouble top, 
   jdouble near_val, jdouble far_val)
{
  glFrustum(left, right,
	    bottom, top, 
	    near_val, far_val);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_viewport
  (JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height)
{
  glViewport(x, y, width, height);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pushMatrix
  (JNIEnv *env, jobject object)
{
  glPushMatrix();
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_popMatrix
  (JNIEnv *env, jobject obj)
{
  glPopMatrix();
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_loadIdentity
  (JNIEnv *env, jobject obj)
{
  glLoadIdentity();
}


JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_loadMatrixd
  (JNIEnv *env, jobject obj, jdoubleArray jm)
{
  jdouble *m;

  m = (*env)->GetDoubleArrayElements(env, jm, 0);
  if (m == NULL)
    return;
  glLoadMatrixd(m);
  (*env)->ReleaseDoubleArrayElements(env, jm, m, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    loadMatrixf
 * Signature: ([F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_loadMatrixf
  (JNIEnv *env, jobject obj, jfloatArray jm)
{
  jfloat *m;

  m = (*env)->GetFloatArrayElements(env, jm, 0);
  if (m == NULL)
    return;
  glLoadMatrixf(m);
  (*env)->ReleaseFloatArrayElements(env, jm, m, 0);
}


JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_multMatrixd
  (JNIEnv *env, jobject object, jdoubleArray darr)
{
  jdouble *doubles;

  doubles = (*env)->GetDoubleArrayElements(env, darr, 0);
  if (doubles == NULL)
    return;
  glMultMatrixd(doubles);
  (*env)->ReleaseDoubleArrayElements(env, darr, doubles, 0);
}


JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_multMatrixf
  (JNIEnv *env, jobject object, jfloatArray farr)
{
  float *floats;
  floats = (*env)->GetFloatArrayElements(env, farr, 0);
  if (floats == NULL)
    return;
  glMultMatrixf(floats);
  (*env)->ReleaseFloatArrayElements(env, farr, floats, 0);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rotated
  (JNIEnv *env, jobject obj, jdouble angle, jdouble x, jdouble y, jdouble z)
{
  glRotated(angle, x, y, z);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rotatef
  (JNIEnv *env, jobject obj, jfloat angle, jfloat x, jfloat y, jfloat z)
{
  glRotatef(angle, x, y, z);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_scaled
  (JNIEnv *env, jobject obj, jdouble x, jdouble y, jdouble z)
{
  glScaled(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_scalef
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z)
{
  glScalef(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_translated
  (JNIEnv *env, jobject obj, jdouble x, jdouble y, jdouble z)
{
  glTranslated(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_translatef
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z)
{
  glTranslatef(x, y, z);
}



/*
 * Display Lists
 */

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    isList
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_OpenGL_OpenGLWidget_isList
  (JNIEnv *env, jobject obj, jint list)
{
  return glIsList(list);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    deleteLists
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_deleteLists
  (JNIEnv *env, jobject obj, jint list, jint range)
{
  glDeleteLists(list, range);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    genLists
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_OpenGL_OpenGLWidget_genLists
  (JNIEnv *env, jobject obj, jint range)
{
  return glGenLists(range);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_newList
  (JNIEnv *env, jobject obj, jint list, jint mode)
{
  glNewList(list, mode);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_endList
  (JNIEnv *env, jobject obj)
{
  glEndList();
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_callList
  (JNIEnv *env, jobject obj, jint list)
{
  glCallList(list);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    callLists
 * Signature: (II[B)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_callLists__II_3B
  (JNIEnv *env, jobject obj, jint n, jint type, jbyteArray jarray)
{
  GLbyte *array;
  
  array = (*env)->GetByteArrayElements(env, jarray, 0);
  if (array == NULL)
    return;

  glCallLists(n, type, array);

  (*env)->ReleaseByteArrayElements(env, jarray, array, 0);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    callLists
 * Signature: (II[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_callLists__II_3S
  (JNIEnv *env, jobject obj, jint n, jint type, jshortArray jarray)
{
  GLshort *array;
  
  array = (*env)->GetShortArrayElements(env, jarray, 0);
  if (array == NULL)
    return;

  glCallLists(n, type, array);

  (*env)->ReleaseShortArrayElements(env, jarray, array, 0);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    callLists
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_callLists__II_3F
  (JNIEnv *env, jobject obj, jint n, jint type, jfloatArray jarray)
{
  GLfloat *array;
  
  array = (*env)->GetFloatArrayElements(env, jarray, 0);
  if (array == NULL)
    return;

  glCallLists(n, type, array);

  (*env)->ReleaseFloatArrayElements(env, jarray, array, 0);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_listBase
  (JNIEnv *env, jobject obj, jint base)
{
  glListBase(base);
}



/*
 * Drawing Functions
 */

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_begin
  (JNIEnv *env, jobject obj, jint mode)
{
  glBegin(mode);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_end
  (JNIEnv *env, jobject obj)
{
  glEnd();
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex2d
  (JNIEnv *env, jobject obj, jdouble x , jdouble y)
{
  glVertex2d(x, y);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex2f
  (JNIEnv *env, jobject obj, jfloat x, jfloat y)
{
  glVertex2f(x, y);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex2i
  (JNIEnv *env, jobject obj, jint x, jint y)
{
  glVertex2i(x, y);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex2s
  (JNIEnv *env, jobject obj, jshort x, jshort y)
{
  glVertex2s(x, y);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex3d
  (JNIEnv *env, jobject obj, jdouble x, jdouble y, jdouble z)
{
  glVertex3d(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex3f
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z)
{
  glVertex3f(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex3i
  (JNIEnv *env, jobject obj, jint x, jint y, jint z)
{
  glVertex3i(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex3s
  (JNIEnv *env, jobject obj, jshort x, jshort y, jshort z)
{
  glVertex3s(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex4d
  (JNIEnv *env, jobject obj, jdouble x, jdouble y, jdouble z, jdouble w)
{
  glVertex4d(x, y, z, w);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex4f
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z, jfloat w)
{
  glVertex4f(x, y, z, w);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex4i
  (JNIEnv *env, jobject obj, jint x, jint y, jint z, jint w)
{
  glVertex4i(x, y, z, w);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertex4s
  (JNIEnv *env, jobject obj, jshort x, jshort y, jshort z, jshort w)
{
  glVertex4s(x, y, z, w);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_normal3b
  (JNIEnv *env, jobject obj, jbyte x, jbyte y, jbyte z)
{
  glNormal3b(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_normal3d
  (JNIEnv *env, jobject obj, jdouble x, jdouble y, jdouble z)
{
  glNormal3d(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_normal3f
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z)
{
  glNormal3f(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_normal3i
  (JNIEnv *env, jobject obj, jint x, jint y, jint z)
{
  glNormal3i(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_normal3s
  (JNIEnv *env, jobject obj, jshort x, jshort y, jshort z)
{
  glNormal3s(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_indexd
  (JNIEnv *env, jobject obj, jdouble c)
{
  glIndexd(c);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_indexf
  (JNIEnv *env, jobject obj, jfloat c)
{
  glIndexf(c);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_indexi
  (JNIEnv *env, jobject obj, jint c)
{
  glIndexi(c);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_indexs
  (JNIEnv *env, jobject obj, jshort c)
{
  glIndexs(c);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_color3b
  (JNIEnv *env, jobject obj, jbyte red, jbyte green, jbyte blue)
{
  glColor3b(red, green, blue);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_color3d
  (JNIEnv *env, jobject obj, jdouble red, jdouble green, jdouble blue)
{
  glColor3d(red, green, blue);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_color3f
  (JNIEnv *env, jobject obj, jfloat red, jfloat green, jfloat blue)
{
  glColor3f(red, green, blue);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_color3i
  (JNIEnv *env, jobject obj, jint red, jint green, jint blue)
{
  glColor3i(red, green, blue);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_color3s
  (JNIEnv *env, jobject obj, jshort red, jshort green, jshort blue)
{
  glColor3s(red, green, blue);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_color4b
  (JNIEnv *env, jobject obj, jbyte red, jbyte green, jbyte blue, jbyte alpha)
{
  glColor4b(red, green, blue, alpha);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_color4d
  (JNIEnv *env, jobject obj, jdouble red, jdouble green, jdouble blue, 
   jdouble alpha)
{
  glColor4d(red, green, blue, alpha);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_color4f
  (JNIEnv *env, jobject obj, jfloat red, jfloat green, jfloat blue, 
   jfloat alpha)
{
  glColor4f(red, green, blue, alpha);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_color4i
  (JNIEnv *env, jobject obj, jint red, jint green, jint blue, jint alpha)
{
  glColor4i(red, green, blue, alpha);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_color4s
  (JNIEnv *env, jobject obj, jshort red, jshort green, jshort blue, 
   jshort alpha)
{
  glColor4s(red, green, blue, alpha);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord1d
  (JNIEnv *env, jobject obj, jdouble s)
{
  glTexCoord1d(s);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord1f
  (JNIEnv *env, jobject obj, jfloat s)
{
  glTexCoord1f(s);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord1i
  (JNIEnv *env, jobject obj, jint s)
{
  glTexCoord1i(s);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord1s
  (JNIEnv *env, jobject obj, jshort s)
{
  glTexCoord1s(s);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texCoord2d
 * Signature: (DD)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord2d
  (JNIEnv *env, jobject obj, jdouble s, jdouble t)
{
  glTexCoord2d(s, t);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord2f
  (JNIEnv *env, jobject obj, jfloat s, jfloat t)
{
  glTexCoord2d(s, t);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord2i
  (JNIEnv *env, jobject obj, jint s, jint t)
{
  glTexCoord2d(s, t);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord2s
  (JNIEnv *env, jobject obj, jshort s, jshort t)
{
  glTexCoord2d(s, t);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord3d
  (JNIEnv *env, jobject obj, jdouble s, jdouble t, jdouble r)
{
  glTexCoord3d(s, t, r);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord3f
  (JNIEnv *env, jobject obj, jfloat s, jfloat t, jfloat r)
{
  glTexCoord3f(s, t, r);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord3i
  (JNIEnv *env, jobject obj, jint s, jint t, jint r)
{
  glTexCoord3i(s, t, r);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord3s
  (JNIEnv *env, jobject obj, jshort s, jshort t, jshort r)
{
  glTexCoord3s(s, t, r);
}




JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord4d
  (JNIEnv *env, jobject obj, jdouble s, jdouble t, jdouble r, jdouble q)
{
  glTexCoord4d(s, t, r, q);
}




JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord4f
  (JNIEnv *env, jobject obj, jfloat s, jfloat t, jfloat r, jfloat q)
{
  glTexCoord4f(s, t, r, q);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord4i
  (JNIEnv *env, jobject obj, jint s, jint t, jint r, jint q)
{
  glTexCoord4i(s, t, r, q);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoord4s
  (JNIEnv *env, jobject obj, jshort s, jshort t, jshort r, jshort q)
{
  glTexCoord4s(s, t, r, q);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos2d
  (JNIEnv *env, jobject obj, jdouble x, jdouble y)
{
  glRasterPos2d(x, y);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos2f
  (JNIEnv *env, jobject obj, jfloat x, jfloat y)
{
  glRasterPos2f(x, y);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos2i
  (JNIEnv *env, jobject obj, jint x, jint y)
{
  glRasterPos2i(x, y);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos2s
  (JNIEnv *env, jobject obj, jshort x, jshort y)
{
  glRasterPos2s(x, y);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos3d
  (JNIEnv *env, jobject obj, jdouble x, jdouble y, jdouble z)
{
  glRasterPos3d(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos3f
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z)
{
  glRasterPos3d(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos3i
  (JNIEnv *env, jobject obj, jint x, jint y, jint z)
{
  glRasterPos3i(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos3s
  (JNIEnv *env, jobject obj, jshort x, jshort y, jshort z)
{
  glRasterPos3s(x, y, z);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos4d
  (JNIEnv *env, jobject obj, jdouble x, jdouble y, jdouble z, jdouble w)
{
  glRasterPos4d(x, y, z, w);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos4f
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z, jfloat w)
{
  glRasterPos4f(x, y, z, w);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos4i
  (JNIEnv *env, jobject obj, jint x, jint y, jint z, jint w)
{
  glRasterPos4i(x, y, z, w);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rasterPos4s
  (JNIEnv *env, jobject obj, jshort x, jshort y, jshort z, jshort w)
{
  glRasterPos4s(x, y, z, w);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rectd
  (JNIEnv *env, jobject obj, jdouble x1, jdouble y1, jdouble x2, jdouble y2)
{
  glRectd(x1, y1, x2, y2);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rectf
  (JNIEnv *env, jobject obj, jfloat x1, jfloat y1, jfloat x2, jfloat y2)
{
  glRectf(x1, y1, x2, y2);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_recti
  (JNIEnv *env, jobject obj, jint x1, jint y1, jint x2, jint y2)
{
  glRecti(x1, y1, x2, y2);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_rects
  (JNIEnv *env, jobject obj, jshort x1, jshort y1, jshort x2, jshort y2)
{
  glRects(x1, y1, x2, y2);
}

/*
 * Vertex Arrays 
 */

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    vertexPointer
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertexPointer__II_3F
  (JNIEnv *env, jobject obj, jint size, jint stride, jfloatArray jarray)
{
  jfloat *array;
  array = (*env)->GetFloatArrayElements(env, jarray, 0);
  if (array == NULL)
    return;
  glVertexPointer(size, GL_FLOAT, stride,array);
  (*env)->ReleaseFloatArrayElements(env, jarray, array, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    vertexPointer
 * Signature: (II[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertexPointer__II_3D
  (JNIEnv *, jobject, jint, jint, jdoubleArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    vertexPointer
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertexPointer__II_3I
  (JNIEnv *, jobject, jint, jint, jintArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    vertexPointer
 * Signature: (II[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertexPointer__II_3S
  (JNIEnv *, jobject, jint, jint, jshortArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    normalPointer
 * Signature: (I[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_normalPointer__I_3F
  (JNIEnv *, jobject, jint, jfloatArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    normalPointer
 * Signature: (I[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_normalPointer__I_3D
  (JNIEnv *, jobject, jint, jdoubleArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    normalPointer
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_normalPointer__I_3I
  (JNIEnv *, jobject, jint, jintArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    normalPointer
 * Signature: (I[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_normalPointer__I_3S
  (JNIEnv *, jobject, jint, jshortArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    colorPointer
 * Signature: (III[B)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_colorPointer__III_3B
  (JNIEnv *, jobject, jint, jint, jint, jbyteArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    colorPointer
 * Signature: (III[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_colorPointer__III_3S
  (JNIEnv *, jobject, jint, jint, jint, jshortArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    colorPointer
 * Signature: (III[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_colorPointer__III_3I
  (JNIEnv *, jobject, jint, jint, jint, jintArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    colorPointer
 * Signature: (III[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_colorPointer__III_3F
  (JNIEnv *, jobject, jint, jint, jint, jfloatArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    colorPointer
 * Signature: (III[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_colorPointer__III_3D
  (JNIEnv *, jobject, jint, jint, jint, jdoubleArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    indexPointer
 * Signature: (I[B)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_indexPointer__I_3B
  (JNIEnv *, jobject, jint, jbyteArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    indexPointer
 * Signature: (I[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_indexPointer__I_3S
  (JNIEnv *, jobject, jint, jshortArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    indexPointer
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_indexPointer__I_3I
  (JNIEnv *, jobject, jint, jintArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    indexPointer
 * Signature: (I[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_indexPointer__I_3F
  (JNIEnv *, jobject, jint, jfloatArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    indexPointer
 * Signature: (I[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_indexPointer__I_3D
  (JNIEnv *, jobject, jint, jdoubleArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texCoordPointer
 * Signature: (II[B)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoordPointer__II_3B
  (JNIEnv *, jobject, jint, jint, jbyteArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texCoordPointer
 * Signature: (II[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoordPointer__II_3S
  (JNIEnv *, jobject, jint, jint, jshortArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texCoordPointer
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoordPointer__II_3I
  (JNIEnv *, jobject, jint, jint, jintArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texCoordPointer
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoordPointer__II_3F
  (JNIEnv *, jobject, jint, jint, jfloatArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texCoordPointer
 * Signature: (II[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texCoordPointer__II_3D
  (JNIEnv *, jobject, jint, jint, jdoubleArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    edgeFlagPointer
 * Signature: (I[Z)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_edgeFlagPointer
  (JNIEnv *, jobject, jint, jbooleanArray);
/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    vertexPointer
 * Signature: (III[Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_vertexPointer
  (JNIEnv *env, jobject obj, jint size, jint type, jint stride, 
   jobjectArray ptr)
{
  ;
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    edgeFlagPointer
 * Signature: (I[Z)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_edgeFlagPointer
  (JNIEnv *env, jobject obj, jint stride, jbooleanArray ptr)
{

}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getPointerv
 * Signature: (I[[Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getPointerv
  (JNIEnv *env, jobject obj, jint pname, jobjectArray params)
{

}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    arrayElement
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_arrayElement
  (JNIEnv *env, jobject obj, jint i)
{
  glArrayElement(i);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_drawArrays
  (JNIEnv *env, jobject obj, jint mode, jint first, jint count)
{
  glDrawArrays(mode, first, count);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_drawElements
  (JNIEnv *env, jobject obj, jint mode, jint count, jint type, 
   jobjectArray indices)
{

}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    interleavedArrays
 * Signature: (II[Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_interleavedArrays
  (JNIEnv *env, jobject obj, jint format, jint stride, jobjectArray pointer)
{

}


/*
 * Lighting 
 */

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_shadeModel
  (JNIEnv *env, jobject obj, jint mode)
{
  glShadeModel(mode);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_lightf
  (JNIEnv *env, jobject obj, jint light, jint pname, jfloat param)
{
  glLightf(light, pname, param);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    lighti
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_lighti
  (JNIEnv *env, jobject obj, jint light, jint pname, jint param)
{
  glLighti(light, pname, param);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    lightfv
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_lightfv
  (JNIEnv *env, jobject obj, jint light, jint pname, jfloatArray jparams)
{
  jfloat *params;
  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glLightfv(light, pname, params);
  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    lightiv
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_lightiv
  (JNIEnv *env, jobject obj, jint light, jint param, jintArray jparams)
{
  jint *params;
  params = (*env)->GetIntArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glLightiv(light, param, params);
  (*env)->ReleaseIntArrayElements(env, jparams, params, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getLightfv
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getLightfv
  (JNIEnv *env, jobject obj, jint light, jint pname, jfloatArray jparams)
{
  jfloat *params;
  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glGetLightfv(light, pname, params);
  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getLightiv
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getLightiv
  (JNIEnv *env, jobject obj, jint light, jint pname, jintArray jparams)
{
  jint *params;
  params = (*env)->GetIntArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glGetLightiv(light, pname, params);
  (*env)->ReleaseIntArrayElements(env, jparams, params, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    lightModelf
 * Signature: (IF)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_lightModelf
  (JNIEnv *env, jobject obj, jint pname, jfloat param)
{
  glLightModelf(pname, param);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    lightModeli
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_lightModeli
  (JNIEnv *env, jobject obj, jint pname, jint param)
{
  glLightModeli(pname, param);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    lightModelfv
 * Signature: (I[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_lightModelfv
  (JNIEnv *env, jobject obj, jint pname, jfloatArray jparams)
{
  jfloat *params;
  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;
  glLightModelfv(pname, params);
  (*env)->ReleaseFloatArrayElements(env, jparams, params,0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    lightModeliv
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_lightModeliv
  (JNIEnv *env, jobject obj, jint pname, jintArray jparams)
{
  jint *params;
  params = (*env)->GetIntArrayElements(env, jparams, 0);
  if (params == NULL)
    return;
  glLightModeliv(pname, params);
  (*env)->ReleaseIntArrayElements(env, jparams, params,0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    materialf
 * Signature: (IIF)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_materialf
  (JNIEnv *env, jobject obj, jint face, jint pname, jfloat param)
{
  glMaterialf(face, pname, param);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_materiali
  (JNIEnv *env, jobject obj, jint face, jint pname, jint param)
{
  glMateriali(face, pname, param);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_materialiv
  (JNIEnv *env, jobject obj, jint face, jint pname, jintArray jparams)
{
  jint *params;
  params = (*env)->GetIntArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glMaterialiv(face, pname, params);
  (*env)->ReleaseIntArrayElements(env, jparams, params, 0);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_materialfv
  (JNIEnv *env, jobject obj, jint face, jint pname, jfloatArray jparams)
{
  jfloat *params;
  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glMaterialfv(face, pname, params);
  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getMaterialfv
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getMaterialfv
  (JNIEnv *env, jobject obj, jint face, jint pname, jfloatArray jparams)
{
  jfloat *params;

  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glGetMaterialfv(face, pname, params);

  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getMaterialiv
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getMaterialiv
  (JNIEnv *env, jobject obj, jint face, jint pname, jintArray jparams)
{
  jint *params;

  params = (*env)->GetIntArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glGetMaterialiv(face, pname, params);

  (*env)->ReleaseIntArrayElements(env, jparams, params, 0);
}


/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    colorMaterial
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_colorMaterial
  (JNIEnv *env, jobject obj, jint face, jint mode)
{
  glColorMaterial(face, mode);
}

/*
 * Raster functions
 */

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    pixelZoom
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pixelZoom
  (JNIEnv *env, jobject obj, jfloat xfactor, jfloat yfactor)
{
  glPixelZoom(xfactor, yfactor);
}
     

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    pixelStoref
 * Signature: (IF)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pixelStoref
  (JNIEnv *env, jobject obj, jint pname, jfloat param)
{
  glPixelStoref(pname, param);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    pixelStorei
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pixelStorei
  (JNIEnv *env, jobject obj, jint pname, jint param)
{
  glPixelStorei(pname, param);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pixelTransferf
  (JNIEnv *env, jobject obj, jint pname, jfloat param)
{
  glPixelTransferf(pname, param);
}


JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pixelTransferi
  (JNIEnv *env, jobject obj, jint pname, jint param)
{
  glPixelTransferi(pname, param);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    pixelMapfv
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pixelMapfv
  (JNIEnv *env, jobject obj, jint map, jint mapsize, jfloatArray jarray)
{
  GLfloat *array;
  array = (*env)->GetFloatArrayElements(env, jarray, 0);
  if (array == NULL)
    return;
  glPixelMapfv(map, mapsize, array);
  (*env)->ReleaseFloatArrayElements(env, jarray, array, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    pixelMapuiv
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pixelMapuiv
  (JNIEnv *env, jobject obj, jint map, jint mapsize, jintArray jvalues)
{
  GLint *values;
  values = (*env)->GetIntArrayElements(env, jvalues, 0);
  if (values == NULL)
    return;
  glPixelMapuiv(map, mapsize, values);
  (*env)->ReleaseIntArrayElements(env, jvalues, values, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    pixelMapusv
 * Signature: (II[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pixelMapusv
  (JNIEnv *env, jobject obj, jint map, jint mapsize, jshortArray jvalues)
{
  GLshort *values;
  values = (*env)->GetShortArrayElements(env, jvalues, 0);
  if (values == NULL)
    return;
  glPixelMapusv(map, mapsize, values);
  (*env)->ReleaseShortArrayElements(env, jvalues, values, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getPixelMapfv
 * Signature: (I[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getPixelMapfv
  (JNIEnv *env, jobject obj, jint map, jfloatArray jvalues)

{
  GLfloat *values;
  values = (*env)->GetFloatArrayElements(env, jvalues, 0);
  if (values == NULL)
    return;
  glGetPixelMapfv(map, values);
  (*env)->ReleaseFloatArrayElements(env, jvalues, values, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getPixelMapuiv
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getPixelMapuiv
  (JNIEnv *env, jobject obj, jint map, jintArray jvalues)
{
  GLint *values;
  values = (*env)->GetIntArrayElements(env, jvalues, 0);
  if (values == NULL)
    return;
  glGetPixelMapuiv(map, values);
  (*env)->ReleaseIntArrayElements(env, jvalues, values, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getPixelMapusv
 * Signature: (I[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getPixelMapusv
  (JNIEnv *env, jobject obj, jint map, jshortArray jvalues)
{
  GLshort *values;
  values = (*env)->GetShortArrayElements(env, jvalues, 0);
  if (values == NULL)
    return;
  glGetPixelMapusv(map, values);
  (*env)->ReleaseShortArrayElements(env, jvalues, values, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    bitmap
 * Signature: (IIFFFF[B)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_bitmap
  (JNIEnv *env, jobject obj, 
   jint width, jint height, 
   jfloat xorig, jfloat yorig, 
   jfloat xmove, jfloat ymove, jbyteArray jbitmap)
{
  GLbyte *bitmap;

  bitmap = (*env)->GetByteArrayElements(env, jbitmap, 0);
  if (bitmap == NULL)
    return;
  glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap);

  (*env)->ReleaseByteArrayElements(env, jbitmap, bitmap, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    readPixels
 * Signature: (IIIIII)Ljava/lang/Object;
 */

JNIEXPORT jobject JNICALL Java_OpenGL_OpenGLWidget_readPixels
  (JNIEnv *env, jobject obj, 
   jint x, jint y, jint width, jint height, jint format, jint type)
{
  void   *buffer;
  int     pixelCountMultiplier = 4; /* Default to the maximum possible. */
  int     pixelStorageSizeMultiplier;
  int     bufferElementCount;
  jobject result = NULL;
  
  /* Determine how many return values we will get for each pixel. */
  switch (format) 
    {
    case GL_COLOR_INDEX:
    case GL_STENCIL_INDEX:
    case GL_DEPTH_COMPONENT:
    case GL_RED:
    case GL_GREEN:
    case GL_BLUE:
    case GL_ALPHA:
    case GL_LUMINANCE:
      pixelCountMultiplier = 1;
      break;
    case GL_RGB:
      pixelCountMultiplier = 3;
      break;
    case GL_RGBA:
      pixelCountMultiplier = 4;
      break;
    case GL_LUMINANCE_ALPHA:
      pixelCountMultiplier = 2;
      break;
    default:
      handleError(env, "OpenGL/OpenGLNativeException",
		  "Unexpected format passed to readPixels");
      return NULL;
    }

  /* Determine how much storage each return value will require. */
  switch(type) 
    {
    case GL_BYTE:
      pixelStorageSizeMultiplier = 1;
      break;
    case GL_SHORT:
      pixelStorageSizeMultiplier = 2;
      break;
    case GL_INT:
    case GL_FLOAT:
      pixelStorageSizeMultiplier = 4;
      break;
    default:
      handleError(env, "OpenGL/OpenGLNativeException",
		  "Unexpected type passed to readPixels");
      return NULL;
    }
    
  bufferElementCount = width * height * pixelCountMultiplier;
  buffer = privateMalloc(bufferElementCount * pixelStorageSizeMultiplier);
  if (buffer == NULL) {
    handleError(env, "OpenGL/OpenGLNativeMemoryExhaustedException",
		"Unable to allocate temporary buffer in readPixels");
    return NULL;
  }
  
  glReadPixels(x, y, width, height, format, type, buffer);

  switch(type) 
    {
    case GL_BYTE:
      result = (*env)->NewByteArray(env, bufferElementCount);
      if (result == NULL) {
	handleError(env, "OpenGL/OpenGLNativeException",
		    "Unable to allocate byte array in readPixels");
	return NULL;
      }
      (*env)->SetByteArrayRegion(env, result, 0, bufferElementCount, buffer);
      break;
    case GL_SHORT:
      result = (*env)->NewShortArray(env, bufferElementCount);
      if (result == NULL) {
	handleError(env, "OpenGL/OpenGLNativeException",
		    "Unable to allocate short array in readPixels");
	return NULL;
      }
      (*env)->SetShortArrayRegion(env, result, 0, bufferElementCount, buffer);
      break;
  case GL_INT:
    result = (*env)->NewIntArray(env, bufferElementCount);
    if (result == NULL) {
      handleError(env, "OpenGL/OpenGLNativeException",
		  "Unable to allocate int array in readPixels");
      return NULL;
    }
    (*env)->SetIntArrayRegion(env, result, 0, bufferElementCount, buffer);
    break;
    case GL_FLOAT:
      result = (*env)->NewFloatArray(env, bufferElementCount);
      if (result == NULL) {
	handleError(env, "OpenGL/OpenGLNativeException",
		    "Unable to allocate float array in readPixels");
	return NULL;
      }
      (*env)->SetFloatArrayRegion(env, result, 0, bufferElementCount, buffer);
      
      if ((*env)->GetArrayLength(env, result) != bufferElementCount)
      break;
    }
  privateFree(buffer);
  
  return result;
}


/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    drawPixels
 * Signature: (IIII[B)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_drawPixels__IIII_3B
  (JNIEnv *env, jobject obj, 
   jint width, jint height, 
   jint format, jint type, 
   jbyteArray jpixels)
{
  GLbyte *pixels;
  
  pixels = (*env)->GetByteArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glDrawPixels(width, height, format, type, pixels);

  (*env)->ReleaseByteArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    drawPixels
 * Signature: (IIII[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_drawPixels__IIII_3S
  (JNIEnv *env, jobject obj,
   jint width, jint height, 
   jint format, jint type, 
   jshortArray jpixels)
{
  GLshort *pixels;
  
  pixels = (*env)->GetShortArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glDrawPixels(width, height, format, type, pixels);

  (*env)->ReleaseShortArrayElements(env, jpixels, pixels, 0);

}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    drawPixels
 * Signature: (IIII[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_drawPixels__IIII_3I
  (JNIEnv *env, jobject obj,
   jint width, jint height, 
   jint format, jint type, 
   jintArray jpixels)
{
  GLint *pixels;
  
  pixels = (*env)->GetIntArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glDrawPixels(width, height, format, type, pixels);

  (*env)->ReleaseIntArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    drawPixels
 * Signature: (IIII[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_drawPixels__IIII_3F
  (JNIEnv *env, jobject obj,
   jint width, jint height, 
   jint format, jint type, 
   jfloatArray jpixels)
{
  GLfloat *pixels;
  
  pixels = (*env)->GetFloatArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glDrawPixels(width, height, format, type, pixels);

  (*env)->ReleaseFloatArrayElements(env, jpixels, pixels, 0);

}


/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    copyPixels
 * Signature: (IIIII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_copyPixels
  (JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height, 
   jint type)
{
  glCopyPixels(x, y, width, height, type);
}


/*
 * Stenciling
 */
/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    stencilFunc
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_stencilFunc
  (JNIEnv *env, jobject obj, jint func, jint ref, jint mask)
{
  glStencilFunc(func, ref, mask);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    stencilMask
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_stencilMask
  (JNIEnv *env, jobject obj, jint mask)
{
  glStencilMask(mask);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    stencilOp
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_stencilOp
  (JNIEnv *env, jobject obj, jint fail, jint zfail, jint zpass)
{
  glStencilOp(fail, zfail, zpass);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    clearStencil
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_clearStencil
  (JNIEnv *env, jobject obj, jint s)
{
  glClearStencil(s);
}

/*
 * Texture mapping
 */
/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texGend
 * Signature: (IID)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texGend
  (JNIEnv *env, jobject obj, jint coord, jint pname, jdouble param)
{
  glTexGend(coord, pname, param);
}
/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texGenf
 * Signature: (IIF)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texGenf
  (JNIEnv *env, jobject obj, jint coord, jint pname, jfloat param)
{
  glTexGenf(coord, pname, param);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texGeni
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texGeni
  (JNIEnv *env, jobject obj, jint coord, jint pname, jint param)
{
  glTexGeni(coord, pname, param);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texGendv
 * Signature: (II[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texGendv
  (JNIEnv *env, jobject obj, jint coord, jint pname, jdoubleArray jparams)
{
  GLdouble *params;

  params = (*env)->GetDoubleArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glTexGendv(coord, pname, params);

  (*env)->ReleaseDoubleArrayElements(env, jparams, params, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texGenfv
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texGenfv
  (JNIEnv *env, jobject obj, jint coord, jint pname, jfloatArray jparams)
{
  GLfloat *params;

  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glTexGenfv(coord, pname, params);

  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);
}
/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texGeniv
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texGeniv
  (JNIEnv *env, jobject obj, jint coord, jint pname, jintArray jparams)
{
  GLint *params;

  params = (*env)->GetIntArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glTexGeniv(coord, pname, params);

  (*env)->ReleaseIntArrayElements(env, jparams, params, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexGendv
 * Signature: (II[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexGendv
  (JNIEnv *env, jobject obj, 
   jint coord, jint pname, jdoubleArray jparams)
{
  GLdouble *params;

  params = (*env)->GetDoubleArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glGetTexGendv(coord, pname, params);

  (*env)->ReleaseDoubleArrayElements(env, jparams, params, 0);

}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexGenfv
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexGenfv
  (JNIEnv *env, jobject obj, jint, jint, jfloatArray);

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexGeniv
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexGeniv
  (JNIEnv *env, jobject obj, jint, jint, jintArray);

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texEnvf
  (JNIEnv *env, jobject obj, jint target, jint pname, jfloat param)
{
  glTexEnvf(target, pname, param);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texEnvi
  (JNIEnv *env, jobject obj, jint target, jint pname, jint param)
{
  glTexEnvi(target, pname, param);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texEnvfv
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texEnvfv
  (JNIEnv *env, jobject obj, jint target, jint pname, jfloatArray jparams)
{
  jfloat *params = NULL;
  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;
  glTexEnvfv(target, pname, params);
  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texEnviv
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texEnviv
  (JNIEnv *env, jobject obj, jint target, jint pname, jintArray jparams)
{
	jint *params = NULL;

	params = (*env)->GetIntArrayElements(env, jparams, 0);
	if (params == NULL)
		return;
	glTexEnviv(target, pname, params);
	(*env)->ReleaseIntArrayElements(env, jparams, params, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexEnvfv
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexEnvfv
  (JNIEnv *env, jobject obj, jint target, jint pname, jfloatArray jparams)
{
  jfloat *params = NULL;
  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;
  glGetTexEnvfv(target, pname, params);
  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);
}
/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexEnviv
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexEnviv
  (JNIEnv *env, jobject obj, jint target, jint pname, jintArray jparams)
{
  int *params;
  params = (*env)->GetIntArrayElements(env, jparams, 0);
  if (params == NULL)
    return;
  glGetTexEnviv(target, pname, params);
  (*env)->ReleaseIntArrayElements(env, jparams, params, 0);

}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texParameterf
  (JNIEnv *env, jobject obj, jint target, jint pname, jfloat param)
{
  glTexParameterf(target, pname, param);
}

JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texParameteri
  (JNIEnv *env, jobject obj, jint target, jint pname, jint param)
{
  glTexParameteri(target, pname, param);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texParameterfv
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texParameterfv
  (JNIEnv *env, jobject obj, jint target, jint pname, jfloatArray jparams)
{
  jfloat *params;

  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;
  
  glTexParameterfv(target, pname, params);

  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);

}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texParameteriv
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texParameteriv
  (JNIEnv *env, jobject obj, jint target, jint pname, jintArray jparams)
{
  jint *params;
  
  params = (*env)->GetIntArrayElements(env, jparams, 0);
  
  if (params == NULL)
    return;
  
  glTexParameteriv(target, pname, params);

  (*env)->ReleaseIntArrayElements(env, jparams, params, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexParameterfv
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexParameterfv
  (JNIEnv *env, jobject obj, jint target, jint pname, jfloatArray jparams)
{
  GLfloat *params;

  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glGetTexParameterfv(target, pname, params);
  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);
}


/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexParameteriv
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexParameteriv
  (JNIEnv *env, jobject obj, jint target, jint pname, jintArray jparams)
{
  GLint *params;

  params = (*env)->GetIntArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glGetTexParameteriv(target, pname, params);
  (*env)->ReleaseIntArrayElements(env, jparams, params, 0);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexLevelParameterfv
 * Signature: (III[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexLevelParameterfv
  (JNIEnv *env, jobject obj, jint target, jint level, jint pname, 
   jfloatArray jparams)
{
  GLfloat *params;

  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glGetTexLevelParameterfv(target, level, pname, params);
  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexLevelParameteriv
 * Signature: (III[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexLevelParameteriv
  (JNIEnv *env, jobject obj, jint target, jint level, jint pname, 
   jintArray jparams)
{
  GLint *params;

  params = (*env)->GetIntArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glGetTexLevelParameteriv(target, level, pname, params);
  (*env)->ReleaseIntArrayElements(env, jparams, params, 0);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texImage1D
 * Signature: (IIIIIII[B)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texImage1D__IIIIIII_3B
  (JNIEnv *env, jobject obj, 
   jint target, jint level, jint components, 
   jint width, jint border, jint format, jint type, 
   jbyteArray jpixels)
{
  GLbyte *pixels;

  pixels = (*env)->GetByteArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;
  
  glTexImage1D(target, level, components, width, border, format, type, pixels);
  (*env)->ReleaseByteArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texImage1D
 * Signature: (IIIIIII[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texImage1D__IIIIIII_3S
  (JNIEnv *env, jobject obj, 
   jint target, jint level, jint components, 
   jint width, jint border, jint format, jint type, 
   jshortArray jpixels)
{
  GLshort *pixels;

  pixels = (*env)->GetShortArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;
  
  glTexImage1D(target, level, components, width, border, format, type, pixels);
  (*env)->ReleaseShortArrayElements(env, jpixels, pixels, 0);
}


/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texImage1D
 * Signature: (IIIIIII[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texImage1D__IIIIIII_3I
  (JNIEnv *env, jobject obj, 
   jint target, jint level, jint components, 
   jint width, jint border, jint format, jint type, 
   jintArray jpixels)
{
  GLint *pixels;

  pixels = (*env)->GetIntArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;
  
  glTexImage1D(target, level, components, width, border, format, type, pixels);
  (*env)->ReleaseIntArrayElements(env, jpixels, pixels, 0);
}


/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texImage1D
 * Signature: (IIIIIII[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texImage1D__IIIIIII_3F
  (JNIEnv *env, jobject obj, 
   jint target, jint level, jint components, 
   jint width, jint border, jint format, jint type, 
   jfloatArray jpixels)
{
  GLfloat *pixels;

  pixels = (*env)->GetFloatArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;
  
  glTexImage1D(target, level, components, width, border, format, type, pixels);
  (*env)->ReleaseFloatArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texImage2D
 * Signature: (IIIIIIII[B)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texImage2D__IIIIIIII_3B
  (JNIEnv *env, jobject obj, 
   jint target, jint level, jint components, 
   jint width, jint height, jint border, 
   jint format, jint type, jbyteArray jpixels)
{
  GLbyte *pixels;

  pixels = (*env)->GetByteArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;
  
  glTexImage2D(target, level, components, width, height,
	       border, format, type, pixels);
  (*env)->ReleaseByteArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texImage2D
 * Signature: (IIIIIIII[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texImage2D__IIIIIIII_3S
  (JNIEnv *env, jobject obj, 
   jint target, jint level, jint components, 
   jint width, jint height, jint border, 
   jint format, jint type, jshortArray jpixels)
{
  GLshort *pixels;

  pixels = (*env)->GetShortArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;
  
  glTexImage2D(target, level, components, width, height,
	       border, format, type, pixels);
  (*env)->ReleaseShortArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texImage2D
 * Signature: (IIIIIIII[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texImage2D__IIIIIIII_3I
  (JNIEnv *env, jobject obj, 
   jint target, jint level, jint components, 
   jint width, jint height, jint border, 
   jint format, jint type, jintArray jpixels)
{
  GLint *pixels;

  pixels = (*env)->GetIntArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;
  
  glTexImage2D(target, level, components, width, height,
	       border, format, type, pixels);
  (*env)->ReleaseIntArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texImage2D
 * Signature: (IIIIIIII[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texImage2D__IIIIIIII_3F
  (JNIEnv *env, jobject obj, 
   jint target, jint level, jint components, 
   jint width, jint height, jint border, 
   jint format, jint type, jfloatArray jpixels)
{
  GLfloat *pixels;

  pixels = (*env)->GetFloatArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;
  
  glTexImage2D(target, level, components, width, height,
	       border, format, type, pixels);
  (*env)->ReleaseFloatArrayElements(env, jpixels, pixels, 0);
}


/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexImage
 * Signature: (IIII[B)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexImage__IIII_3B
  (JNIEnv *env, jobject obj, jint target, jint level, 
   jint format, jint type, jbyteArray jpixels)
{
  GLbyte *pixels;

  pixels = (*env)->GetByteArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glGetTexImage(target, level, format, type, pixels);
  (*env)->ReleaseByteArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexImage
 * Signature: (IIII[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexImage__IIII_3S
  (JNIEnv *env, jobject obj, jint target, jint level, 
   jint format, jint type, jbyteArray jpixels)
{
  GLshort *pixels;

  pixels = (*env)->GetShortArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glGetTexImage(target, level, format, type, pixels);
  (*env)->ReleaseShortArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexImage
 * Signature: (IIII[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexImage__IIII_3I
  (JNIEnv *env, jobject obj, jint target, jint level, 
   jint format, jint type, jintArray jpixels)
{
  GLint *pixels;

  pixels = (*env)->GetIntArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glGetTexImage(target, level, format, type, pixels);
  (*env)->ReleaseIntArrayElements(env, jpixels, pixels, 0);
}


/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getTexImage
 * Signature: (IIII[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getTexImage__IIII_3F
  (JNIEnv *env, jobject obj, jint target, jint level, 
   jint format, jint type, jfloatArray jpixels)
{
  GLfloat *pixels;

  pixels = (*env)->GetFloatArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glGetTexImage(target, level, format, type, pixels);
  (*env)->ReleaseFloatArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    genTextures
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_genTextures
  (JNIEnv *env, jobject obj, jintArray jtextures)
{
  int *textures;
  int  n = (*env)->GetArrayLength(env, jtextures);
  textures = (*env)->GetIntArrayElements(env, jtextures, 0);
  if (textures == NULL)
    return;
  glGenTextures(n, textures);
  (*env)->ReleaseIntArrayElements(env, jtextures, textures, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    deleteTextures
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_deleteTextures
  (JNIEnv *env, jobject obj, jintArray jtextures)
{
  int *textures;
  int n = (*env)->GetArrayLength(env, jtextures);
  textures = (*env)->GetIntArrayElements(env, jtextures, 0);
  if (textures == NULL)
    return;
  glDeleteTextures(n, textures);
  (*env)->ReleaseIntArrayElements(env, jtextures, textures, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    bindTexture
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_bindTexture
  (JNIEnv *env, jobject obj, jint target, jint textures)
{
  glBindTexture(target, textures);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    prioritizeTextures
 * Signature: (I[I[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_prioritizeTextures
  (JNIEnv *env, jobject obj, jintArray textures, 
   jfloatArray priorities)
{
  jfloat *jpriorities;
  jint   *jtextures;
  jint   texturesLength;

  jpriorities = (*env)->GetFloatArrayElements(env, priorities, 0);
  if (jpriorities == NULL)
    return;
  jtextures = (*env)->GetIntArrayElements(env, textures, 0);
  if (jtextures == NULL) {
    (*env)->ReleaseFloatArrayElements(env, priorities, jpriorities, 0);
    return;
  }
  texturesLength = (*env)->GetArrayLength(env, textures);
  glPrioritizeTextures(texturesLength, jtextures, jpriorities);
  (*env)->ReleaseIntArrayElements(env, textures, jtextures, 0);  
  (*env)->ReleaseFloatArrayElements(env, priorities, jpriorities, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    areTexturesResident
 * Signature: (I[I[Z)Z
 */
JNIEXPORT jboolean JNICALL Java_OpenGL_OpenGLWidget_areTexturesResident
  (JNIEnv *env, jobject obj, jintArray jtextures, jbooleanArray jresidences)
{
  int *textures;
  jboolean *residences;
  jboolean result;
  int texturesLength = (*env)->GetArrayLength(env, jtextures);
  textures = (*env)->GetIntArrayElements(env, jtextures, 0);
  if (textures == NULL)
    return FALSE;
  residences = (*env)->GetBooleanArrayElements(env, jresidences, 0);
  if (residences == NULL) {
    (*env)->ReleaseIntArrayElements(env, jtextures, textures, 0);
    return FALSE;
  }

  result = glAreTexturesResident(texturesLength, textures, residences);

  (*env)->ReleaseIntArrayElements(env, jtextures, textures, 0);
  (*env)->ReleaseBooleanArrayElements(env, jresidences, residences, 0);

  return result;
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    isTexture
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_OpenGL_OpenGLWidget_isTexture
  (JNIEnv *env, jobject obj, jint texture)
{
  /* This assumes that JNI_TRUE == 1, and JNI_FALSE == 0 */
  return glIsTexture(texture);
}

/* TexSubImage2D */

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texSubImage2D
 * Signature: (IIIIIIII[B)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texSubImage2D__IIIIIIII_3B
  (JNIEnv *env, jobject obj, 
   jint target, jint level, 
   jint xoffset, jint yoffset, 
   jint width, jint height, 
   jint format, jint type, 
   jbyteArray jpixels)
{
  GLbyte *pixels;

  pixels = (*env)->GetByteArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glTexSubImage2D(target, level, xoffset, yoffset, width, height,
		  format, type, pixels);
  (*env)->ReleaseByteArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texSubImage2D
 * Signature: (IIIIIIII[S)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texSubImage2D__IIIIIIII_3S
  (JNIEnv *env, jobject obj, 
   jint target, jint level, 
   jint xoffset, jint yoffset, 
   jint width, jint height, 
   jint format, jint type, 
   jshortArray jpixels)
{
  GLshort *pixels;

  pixels = (*env)->GetShortArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glTexSubImage2D(target, level, xoffset, yoffset, width, height,
		  format, type, pixels);
  (*env)->ReleaseShortArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texSubImage2D
 * Signature: (IIIIIIII[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texSubImage2D__IIIIIIII_3I
  (JNIEnv *env, jobject obj, 
   jint target, jint level, 
   jint xoffset, jint yoffset, 
   jint width, jint height, 
   jint format, jint type, 
   jintArray jpixels)
{
  GLint *pixels;

  pixels = (*env)->GetIntArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glTexSubImage2D(target, level, xoffset, yoffset, width, height,
		  format, type, pixels);
  (*env)->ReleaseIntArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    texSubImage2D
 * Signature: (IIIIIIII[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_texSubImage2D__IIIIIIII_3F
  (JNIEnv *env, jobject obj, 
   jint target, jint level, 
   jint xoffset, jint yoffset, 
   jint width, jint height, 
   jint format, jint type, 
   jfloatArray jpixels)
{
  GLfloat *pixels;

  pixels = (*env)->GetFloatArrayElements(env, jpixels, 0);
  if (pixels == NULL)
    return;

  glTexSubImage2D(target, level, xoffset, yoffset, width, height,
		  format, type, pixels);
  (*env)->ReleaseFloatArrayElements(env, jpixels, pixels, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    copyTexImage1D
 * Signature: (IIIIIII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_copyTexImage1D
  (JNIEnv *env, jobject obj, 
   jint target, jint level, 
   jint internalformat,
   jint x, jint y,
   jint width, jint border)

{
  glCopyTexImage1D(target, level, internalformat, x, y, width, border);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    copyTexImage2D
 * Signature: (IIIIIIII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_copyTexImage2D
  (JNIEnv *env, jobject obj, 
   jint target, jint level, 
   jint internalFormat, 
   jint x, jint y, 
   jint width, jint height, jint border)
{
  glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    copyTexSubImage1D
 * Signature: (IIIIII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_copyTexSubImage1D
  (JNIEnv *env, jobject obj, 
   jint target, jint level, 
   jint xoffset, jint x, jint y, 
   jint width)
{
  glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    copyTexSubImage2D
 * Signature: (IIIIIIII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_copyTexSubImage2D
  (JNIEnv *env, jobject obj, 
   jint target, jint level, 
   jint xoffset, jint yoffset, 
   jint x, jint y, 
   jint width, jint height)
{
  glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}


/*
 * Evaluators
 */

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    map1d
 * Signature: (IDDII[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_map1d
  (JNIEnv *env, jobject obj, jint target, 
   jdouble u1, jdouble u2, jint stride, jint order, jdoubleArray points)
{
  GLdouble *doublePoints;

  doublePoints = (*env)->GetDoubleArrayElements(env, points, 0);
  if (doublePoints == NULL)
    return;
  glMap1d(target, u1, u2, stride, order, doublePoints);
  (*env)->ReleaseDoubleArrayElements(env, points, doublePoints, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    map1f
 * Signature: (IFFII[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_map1f
  (JNIEnv *env, jobject obj, 
   jint target, jfloat u1, jfloat u2, jint stride, jint order, 
   jfloatArray jpoints)
{
  GLfloat *points;

  points = (*env)->GetFloatArrayElements(env, jpoints, 0);
  if (points == NULL)
    return;
  glMap1f(target, u1, u2, stride, order, points);
  (*env)->ReleaseFloatArrayElements(env, jpoints, points, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    map2d
 * Signature: (IDDIIDDII[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_map2d
  (JNIEnv *env, jobject obj, 
   jint target, 
   jdouble u1, jdouble u2, 
   jint ustride, jint uorder, 
   jdouble v1, jdouble v2, jint vstride, jint vorder, jdoubleArray jpoints)
{
  GLdouble *points;
  
  points = (*env)->GetDoubleArrayElements(env, jpoints, 0);
  if (points == NULL)
    return;
  
  glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
  (*env)->ReleaseDoubleArrayElements(env, jpoints, points, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    map2f
 * Signature: (IFFIIFFII[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_map2f
  (JNIEnv *env, jobject obj, 
   jint target, 
   jfloat u1, jfloat u2, jint ustride, jint uorder, 
   jfloat v1, jfloat v2, jint vstride, jint vorder, 
   jfloatArray jpoints)
{
  GLfloat *points;
  
  points = (*env)->GetFloatArrayElements(env, jpoints, 0);
  if (points == NULL)
    return;
  
  glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
  (*env)->ReleaseFloatArrayElements(env, jpoints, points, 0);
}


/* getMapdv */
/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getMapdv
 * Signature: (II[D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getMapdv
  (JNIEnv *env, jobject obj, 
   jint target, jint query, jdoubleArray jv)
{
  GLdouble *v;

  v = (*env)->GetDoubleArrayElements(env, jv, 0);
  if (v == NULL)
    return;
  
  glGetMapdv(target, query, v);
  (*env)->ReleaseDoubleArrayElements(env, jv, v, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getMapfv
 * Signature: (II[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getMapfv
  (JNIEnv *env, jobject obj, 
   jint target, jint query, jfloatArray jv)
{
  GLfloat *v;

  v = (*env)->GetFloatArrayElements(env, jv, 0);
  if (v == NULL)
    return;
  
  glGetMapfv(target, query, v);
  (*env)->ReleaseFloatArrayElements(env, jv, v, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    getMapiv
 * Signature: (II[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_getMapiv
  (JNIEnv *env, jobject obj, 
   jint target, jint query, jintArray jv)
{
  GLint *v;

  v = (*env)->GetIntArrayElements(env, jv, 0);
  if (v == NULL)
    return;
  
  glGetMapiv(target, query, v);
  (*env)->ReleaseIntArrayElements(env, jv, v, 0);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    evalCoord1d
 * Signature: (D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_evalCoord1d
  (JNIEnv *env, jobject obj, jdouble u)
{
  glEvalCoord1d(u);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    evalCoord1f
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_evalCoord1f
  (JNIEnv *env, jobject obj, jfloat u)
{
  glEvalCoord1f(u);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    evalCoord2d
 * Signature: (DD)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_evalCoord2d
  (JNIEnv *env, jobject obj, jdouble u, jdouble v)
{
  glEvalCoord2d(u, v);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    evalCoord2f
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_evalCoord2f
  (JNIEnv *env, jobject obj, 
   jfloat u, jfloat v)
{
  glEvalCoord2f(u, v);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    mapGrid1d
 * Signature: (IDD)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_mapGrid1d
  (JNIEnv *env, jobject obj, 
   jint un, jdouble u1, jdouble u2)
{
  glMapGrid1d(un, u1, u2);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    mapGrid1f
 * Signature: (IFF)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_mapGrid1f
  (JNIEnv *env, jobject obj, 
   jint un, jfloat u1, jfloat u2)
{
  glMapGrid1f(un, u1, u2);
}

/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    mapGrid2d
 * Signature: (IDDIDD)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_mapGrid2d
  (JNIEnv *env, jobject obj, 
   jint un, jdouble u1, jdouble u2, 
   jint vn, jdouble v1, jdouble v2)
{
  glMapGrid2d(un, u1, u2,
	      vn, v1, v2);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    mapGrid2f
 * Signature: (IFFIFF)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_mapGrid2f
  (JNIEnv *env, jobject obj, 
   jint un, jfloat u1, jfloat u2, 
   jint vn, jfloat v1, jfloat v2)
{
  glMapGrid2f(un, u1, u2, 
	      vn, v1, v2);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    evalPoint1
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_evalPoint1
  (JNIEnv *env, jobject obj, jint i)
{
  glEvalPoint1(i);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    evalPoint2
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_evalPoint2
  (JNIEnv *env, jobject obj, jint i, jint j)
{
  glEvalPoint2(i, j);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    evalMesh1
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_evalMesh1
  (JNIEnv *env, jobject obj, jint mode, jint i1, jint i2)
{
  glEvalMesh1(mode, i1, i2);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    evalMesh2
 * Signature: (IIIII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_evalMesh2
  (JNIEnv *env, jobject obj, jint mode, jint i1, jint i2, jint j1, jint j2)
{
  glEvalMesh2(mode, i1, i2, j1, j2);
}



/*
 * Fog
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_fogf
  (JNIEnv *env, jobject obj, jint name, jfloat param)
{
  glFogf(name, param);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_fogi
  (JNIEnv *env, jobject obj, jint name, jint param)
{
  glFogi(name, param);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_fogfv
  (JNIEnv *env, jobject obj, jint param, jfloatArray jparams)
{
  jfloat *params;
  params = (*env)->GetFloatArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glFogfv(param, params);
  (*env)->ReleaseFloatArrayElements(env, jparams, params, 0);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_fogiv
  (JNIEnv *env, jobject obj, jint param, jintArray jparams)
{
  jint *params;
  params = (*env)->GetIntArrayElements(env, jparams, 0);
  if (params == NULL)
    return;

  glFogiv(param, params);
  (*env)->ReleaseIntArrayElements(env, jparams, params, 0);
}



/*
 * Selection and Feedback
 */



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    feedbackBuffer
 * Signature: (I[F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_feedbackBuffer
  (JNIEnv *env, jobject obj, jint type, jfloatArray jbuffer)
{
  /* TODO: This won't work because the native array may be gone by the
     time OpenGL wants to use it. */
  GLfloat *buffer;
  int      size;

  size = (*env)->GetArrayLength(env, jbuffer);

  buffer = (*env)->GetFloatArrayElements(env, jbuffer, 0);
  if (buffer == NULL) 
    return;
  glFeedbackBuffer(size, type, buffer);
  (*env)->ReleaseFloatArrayElements(env, jbuffer, buffer, 0);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    passThrough
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_passThrough
  (JNIEnv *env, jobject obj, jfloat token)
{
  glPassThrough(token);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    selectBuffer
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_selectBuffer
  (JNIEnv *env, jobject obj, jintArray buffer)
{
  jint *params;
  jsize size;
  params = (*env)->GetIntArrayElements(env, buffer, 0);
  if (params == NULL)
    return;

  size = (*env)->GetArrayLength(env, buffer);

  glSelectBuffer(size, params);
  (*env)->ReleaseIntArrayElements(env, buffer, params, 0);
}



/* Class:     OpenGL_OpenGLWidget
 * Method:    initNames
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_initNames
  (JNIEnv *env, jobject obj)
{
  glInitNames();
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_loadName
  (JNIEnv *env, jobject obj, jint name)
{
  glLoadName(name);
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_pushName
  (JNIEnv *env, jobject obj, jint name)
{
  glPushName(name);
}



/*
 * Class:     OpenGL_OpenGLWidget
 * Method:    popName
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_OpenGL_OpenGLWidget_popName
  (JNIEnv *env, jobject obj)
{
  glPopName();
}



