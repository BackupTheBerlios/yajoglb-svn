/*
  Provides support for callback objects.
 
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
 * CallbackObject.v
 *
 * $Id: CallbackObject.c,v 1.2 2001/07/06 23:39:39 razeh Exp $
 *
 * This provides an interface to the CallbackObject class so that
 * native methods can obtain the active CallbackObject for a 
 * particular class.
 *
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
