/*
 * CapabilitiesAccessors.h
 * 
 * $Id$
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
