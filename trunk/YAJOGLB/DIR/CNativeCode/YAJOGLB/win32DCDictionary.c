/*
 * win32DCDictionary.c
 *
 * $Id: win32DCDictionary.c,v 1.3 1999/02/13 19:27:40 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements the win32 functions that aquire the DC from an OpenGLCanvas object. 
 *
 */


#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include "SystemError.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"
#include "win32DCDictionary.h"

/* This aquires the DC from an OpenGLCanvas object. */
HDC getDCForCanvas(JNIEnv *env, jobject canvas)
{
	jmethodID getDCMethodID = NULL;
	HDC hDC = 0;
	jclass canvasClass = (*env)->GetObjectClass(env, canvas);
	
	getDCMethodID = getMethodID(env, canvasClass, "getHDC", "()I",
		"Unable to get getHDC() method.");
	if (getDCMethodID) {
		hDC = (HDC)(*env)->CallIntMethod(env, canvas, getDCMethodID);
	}
	return hDC;
}
	r