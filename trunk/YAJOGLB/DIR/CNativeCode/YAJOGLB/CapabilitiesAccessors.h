/*
 * CapabilitiesAccessors.h
 * 
 * $Id: CapabilitiesAccessors.h,v 1.2 2001/08/11 02:14:22 razeh Exp $
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@yahoo.com)
 */

#include <jni.h>

jint colorDepth(JNIEnv *env, jobject capabilities);
jint alphaDepth(JNIEnv *env, jobject capabilities);
jint depthBuffer(JNIEnv *env, jobject capabilities);
jint stencilBuffer(JNIEnv *env, jobject capabilities);
jint colorType(JNIEnv* env, jobject capabilities);
jint isDoubleBufferEnabled(JNIEnv *env, jobject capabilities);
