/*
 * OpenGLCapabilitiesAccessors.h
 * 
 * $Id: CapabilitiesAccessors.h,v 1.1 1999/02/13 19:29:04 razeh Exp $
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@balr.com)
 */

#include <jni.h>

jint colorDepth(JNIEnv *env, jobject capabilities);
jint alphaDepth(JNIEnv *env, jobject capabilities);
jint depthBuffer(JNIEnv *env, jobject capabilities);
jint stencilBuffer(JNIEnv *env, jobject capabilities);
jint colorType(JNIEnv* env, jobject capabilities);
jint isDoubleBufferEnabled(JNIEnv *env, jobject capabilities);
