/*
 * CallbackObject.h 
 *
 * $Id$
 *
 * This provides an interface to the CallbackObject class so that
 * native methods can obtain the active CallbackObject for a 
 * particular class.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

#include <jni.h>

jobject getActiveCallbackObjectForClass(JNIEnv *env, jclass callbackClass);
