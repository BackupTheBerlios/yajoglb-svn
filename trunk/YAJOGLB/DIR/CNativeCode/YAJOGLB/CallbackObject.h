/*
 * CallbackObject.h 
 *
 * $Id: CallbackObject.h,v 1.1 1999/01/26 23:57:50 razeh Exp $
 *
 * This provides an interface to the CallbackObject class so that
 * native methods can obtain the active CallbackObject for a 
 * particular class.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

#include <jni.h>

jobject getActiveCallbackObjectForClass(JNIEnv *env, jclass callbackClass);
