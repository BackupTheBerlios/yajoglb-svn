/*
 * win32DCDictionary.c
 *
 * $Id: win32DCDictionary.c,v 1.2 1998/11/04 00:38:51 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements the win32 functions that aquire the DC from an OpenGLCanvas object. 
 *
 */

#include "cygnusFixes.h"
#include "SystemError.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"
#include "win32DCDictionary.h"

/* This aquires the DC from an OpenGLCanvas object. */
HDC getDCForCanvas(JNIEnv *env, jobject canvas)
{
	jmethodID getDCMethodID;
	HDC hDC = 0;
	jclass canvasClass =
		(*env)->GetObjectClass(env, canvas);
	
	getDCMethodID = getMethodID(env, canvasClass, "getHDC", "()I",
		"Unable to get getHDC()I method");
	if (getDCMethodID) {
		hDC = (*env)->CallObjectMethod(env, canvas, getDCMethodID);
	}
	return hDC;
}
	r