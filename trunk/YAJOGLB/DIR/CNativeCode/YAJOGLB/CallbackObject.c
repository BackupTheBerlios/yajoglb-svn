/*
 * CallbackObject.v
 *
 * $Id: CallbackObject.c,v 1.1 1999/01/26 23:55:44 razeh Exp $
 *
 * This provides an interface to the CallbackObject class so that
 * native methods can obtain the active CallbackObject for a 
 * particular class.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */


#include "cygnusFixes.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"
#include "EnvDictionary.h"
#include "CallbackObject.h"


/* Returns the currently active callback object for callbackClass.
*/

jobject getActiveCallbackObjectForClass(JNIEnv *env, jclass callbackClass)
{
	jobject     activeCallbackObject        = NULL;
	jmethodID   activeCallbackObjectMethod  = NULL;
	jclass      callbackObjectClass         = NULL;
	int         error                       = 0;

	// Get the callback object class.
	if (!error) {
		callbackObjectClass = getClass(env, "OpenGL/CallbackObject", 
			"Unable to get the OpenGL/CallbackObject class.");
		error = (NULL == callbackClass);
	}

	// Get the callback method.
	if (!error) {
		activeCallbackObjectMethod = 
			getStaticMethodID(env, callbackObjectClass,
						  	  "activeCallbackObjectForThread",
						      "(Ljava/lang/Class;)LOpenGL/CallbackObject;",
						      "Unable to obtain the active callback object method.");
		error = (NULL == activeCallbackObjectMethod);
	}

	// Get the active tesselator by asking the Callback object class for it.
	if (!error) {
		activeCallbackObject = 
			(*env)->CallStaticObjectMethod(env, callbackClass,  activeCallbackObjectMethod,
		                                   callbackClass);
	}
	
	return activeCallbackObject;
}
