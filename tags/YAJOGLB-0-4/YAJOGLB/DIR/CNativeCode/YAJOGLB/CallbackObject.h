/*
 * CallbackObject.h 
 *
 * $Id: CallbackObject.h,v 1.2 2002/07/21 16:53:14 razeh Exp $
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
