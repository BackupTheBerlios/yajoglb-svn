/*
  Accessors for the OpenGL capabilities class.
 
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
 * CapabilitiesAccessors.h
 * 
 * $Id: CapabilitiesAccessors.c,v 1.3 2001/11/10 20:32:54 razeh Exp $
 *
 */

/* This files contains some accessors for the OpenGL capabilities
   class.  Although this scheme is not quite as efficient as bundling
   up all of the calls into one place, it prevents needless
   duplication between the win32 and linux implementations. */

#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include "JNIInterface.h"
#include "CapabilitiesAccessors.h"

/* Returns the number of bits to use for color.  A negative number is
   returned if something went wrong.*/
jint colorDepth(JNIEnv *env, jobject capabilities)
{
  jclass    capabilitiesClass = NULL;
  jmethodID methodID          = NULL;
  jint      colorDepth        = -1;

  capabilitiesClass = (*env)->GetObjectClass(env, capabilities);
  methodID = getMethodID(env, capabilitiesClass, "getColorDepth", "()I",
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
  methodID = getMethodID(env, capabilitiesClass, "getAlphaDepth", "()I",
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
  methodID = getMethodID(env, capabilitiesClass, "getDepthBuffer", "()I",
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
  methodID = getMethodID(env, capabilitiesClass, "getStencilBuffer", "()I",
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
  methodID = getMethodID(env, capabilitiesClass, "getColorType", "()I",
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
  methodID = getMethodID(env, capabilitiesClass, "getDoubleBufferEnabled", 
			 "()Z", "Unable to get isDoubleBufferedEnabled.");
  if (methodID) {
    isDoubleBufferEnabled = (*env)->CallBooleanMethod(env, capabilities, methodID);
  } else {
    return -1;
  }

  return (jint)isDoubleBufferEnabled;
}

  
