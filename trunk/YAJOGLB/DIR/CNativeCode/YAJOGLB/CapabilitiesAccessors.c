/*
 * OpenGLCapabilitiesAccessors.h
 * 
 * $Id: CapabilitiesAccessors.c,v 1.1 1999/02/13 19:27:40 razeh Exp $
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@balr.com)
 */

/* This files contains some accessors for the OpenGL capabilities
   class.  Although this scheme is not quite as efficient as bundling
   up all of the calls into one place, it prevents needless
   duplication between the win32 and linux implementations. */

#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include "JNIInterface.h"
#include "OpenGLCapabilitiesAccessors.h"

/* Returns the number of bits to use for color.  A negative number is
   returned if something went wrong.*/
jint colorDepth(JNIEnv *env, jobject capabilities)
{
  jclass    capabilitiesClass = NULL;
  jmethodID methodID          = NULL;
  jint      colorDepth        = -1;

  capabilitiesClass = (*env)->GetObjectClass(env, capabilities);
  methodID = getMethodID(env, capabilitiesClass, "colorDepth", "()I",
			 "Unable to get colorDepth method.");
  if (methodID) {
    colorDepth = (*env)->CallIntMethod(env, capabilities, methodID);
  } else {
    return -1;
  }
  return colorDepth;
}



/* Returns the number of bits to be used for the alpha buffer.  A negative 
   number is returned if something went wrong. */
jint alphaDepth(JNIEnv *env, jobject capabilities)
{
  jclass    capabilitiesClass = NULL;
  jmethodID methodID          = NULL;
  jint      colorDepth        = -1;

  capabilitiesClass = (*env)->GetObjectClass(env, capabilities);
  methodID = getMethodID(env, capabilitiesClass, "alphaDepth", "()I",
			 "Unable to get alphaDepth method.");
  if (methodID) {
    colorDepth = (*env)->CallIntMethod(env, capabilities, methodID);
  } else {
    return -1;
  }

  return colorDepth;
}



/* Returns the number of bits to use for the depth buffer.  A negative number
   is returned if something went wrong. */
jint depthBuffer(JNIEnv *env, jobject capabilities)
{
  jclass    capabilitiesClass = NULL;
  jmethodID methodID          = NULL;
  jint      colorDepth        = -1;

  capabilitiesClass = (*env)->GetObjectClass(env, capabilities);
  methodID = getMethodID(env, capabilitiesClass, "depthBuffer", "()I",
			 "Unable to get depthBuffer method.");
  if (methodID) {
    colorDepth = (*env)->CallIntMethod(env, capabilities, methodID);
  } else {
    return -1;
  }

  return colorDepth;
}



/* Returns the number of bits to use for the stencil buffer.  A negative
   number is used if something went wrong. */
jint stencilBuffer(JNIEnv *env, jobject capabilities)
{
  jclass    capabilitiesClass = NULL;
  jmethodID methodID          = NULL;
  jint      stencilBuffer     = -1;

  capabilitiesClass = (*env)->GetObjectClass(env, capabilities);
  methodID = getMethodID(env, capabilitiesClass, "stencilBuffer", "()I",
			 "Unable to get stencilBuffer method.");
  if (methodID) {
    stencilBuffer = (*env)->CallIntMethod(env, capabilities, methodID);
  } else {
    return -1;
  }

  return stencilBuffer;
}




/* Returns the number of bits to use for the color type.  A negative
   number is used if something went wrong. */
jint colorType(JNIEnv *env, jobject capabilities)
{
  jclass    capabilitiesClass = NULL;
  jmethodID methodID          = NULL;
  jint      colorType         = -1;

  capabilitiesClass = (*env)->GetObjectClass(env, capabilities);
  methodID = getMethodID(env, capabilitiesClass, "colorType", "()I",
			 "Unable to get colorType method.");
  if (methodID) {
    colorType = (*env)->CallIntMethod(env, capabilities, methodID);
  } else {
    return -1;
  }

  return colorType;
}



/* Returns if the capabilities wants to use double buffering. */
jint isDoubleBufferEnabled(JNIEnv *env, jobject capabilities)
{
  jclass    capabilitiesClass = NULL;
  jmethodID methodID          = NULL;
  jboolean  isDoubleBufferEnabled;

  capabilitiesClass = (*env)->GetObjectClass(env, capabilities);
  methodID = getMethodID(env, capabilitiesClass, "isDoubleBufferedEnabled", 
			 "()Z", "Unable to get isDoubleBufferedEnabled.");
  if (methodID) {
    isDoubleBufferEnabled = (*env)->CallBooleanMethod(env, capabilities, methodID);
  } else {
    return -1;
  }

  return (jint)isDoubleBufferEnabled;
}

  
