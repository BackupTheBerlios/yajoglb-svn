/*
  Common canvas methods.
 
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



#ifdef USE_JAWT
#include <jawt_md.h>
#endif
#include "Memory.h"
#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include "OpenGL_Canvas.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"

static void nativeLockingMethod
(JNIEnv *env, jobject canvas, const char *methodName,
 const char *errorMessage)
{
  JAWT awt;
  JAWT_DrawingSurface* ds;
  JAWT_DrawingSurfaceInfo* dsi;
  jboolean result;
  jint lock;
  
  // Get the AWT
  awt.version = JAWT_VERSION_1_3;
  result = JAWT_GetAWT(env, &awt);
  if (result == JNI_FALSE) {
    handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get JAWT.");
    return;
  }

  // Get the drawing surface
  ds = awt.GetDrawingSurface(env, canvas);
  if (ds == NULL) {
    handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get drawing surface.");
    return;
  }

  // Lock the drawing surface
  lock = ds->Lock(ds);
  if (lock & JAWT_LOCK_ERROR) {
    handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to lock canvas.");
    awt.FreeDrawingSurface(ds);
    return;
  }

  // Get the drawing surface info
  dsi = ds->GetDrawingSurfaceInfo(ds);
  
  {
    jclass canvasClass = (*env)->GetObjectClass(env, canvas);
    jmethodID methodID = getMethodID(env, canvasClass, methodName, "()V",
				     errorMessage);
    if (methodID) {
      (*env)->CallVoidMethod(env, canvas, methodID);
    }
  }

  // Free the drawing surface info
  ds->FreeDrawingSurfaceInfo(dsi);

  // Unlock the drawing surface
  ds->Unlock(ds);

  // Free the drawing surface
  awt.FreeDrawingSurface(ds);
}



/*
 * Class:     OpenGL_Canvas
 * Method:    nativePaint
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_OpenGL_Canvas_nativePaint
(JNIEnv *env, jobject canvas)

{
  nativeLockingMethod(env, canvas, "paint", "Unable to get paint method.");
}



/*
 * Class:     OpenGL_Canvas
 * Method:    nativeGlInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_OpenGL_Canvas_nativeGlInit
(JNIEnv *env, jobject canvas)

{
  nativeLockingMethod(env, canvas, "glInit", "Unable to get glInit method.");
}




/*
 * Class:     OpenGL_Canvas
 * Method:    lockedMethod
 * Signature: (Ljava/lang/reflect/Method;Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_OpenGL_Canvas_lockedMethod
(JNIEnv *env, jobject canvas, jobject method, jobject object, 
 jobjectArray args)
{
  JAWT awt;
  JAWT_DrawingSurface* ds;
  JAWT_DrawingSurfaceInfo* dsi;
  jboolean result;
  jint lock;
  jobject returnObject = 0;

  // Get the AWT
  awt.version = JAWT_VERSION_1_3;
  result = JAWT_GetAWT(env, &awt);
  if (result == JNI_FALSE) {
    handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get JAWT.");
    return returnObject;
  }

  // Get the drawing surface
  ds = awt.GetDrawingSurface(env, canvas);
  if (ds == NULL) {
    handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get drawing surface.");
    return returnObject;
  }

  // Lock the drawing surface
  lock = ds->Lock(ds);
  if (lock & JAWT_LOCK_ERROR) {
    handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to lock canvas.");
    awt.FreeDrawingSurface(ds);
    return returnObject;
  }

  // Get the drawing surface info
  dsi = ds->GetDrawingSurfaceInfo(ds);
  if (dsi == NULL) {
    handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get drawing surface information.");
    ds->Unlock(ds);
    awt.FreeDrawingSurface(ds);
    return returnObject;
  }

  {
    jmethodID methodID = (*env)->FromReflectedMethod(env, method);

    if (!methodID) {
      handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get methodID.");
      return returnObject;
    }

    if (args != NULL) {
      // If we have any arguments we need to convert them into a
      // jvalues.
      const jsize argsLength = (*env)->GetArrayLength(env, args);      
      jvalue *argsAsValues = (jvalue*)alloca(sizeof(jvalue) * argsLength);
      int i = 0;

      if (argsAsValues == NULL) {
	handleOutOfMemoryError(env, "Ran out of memory while trying to invoke a locked method.");
	return returnObject;
      }
      for(i = 0; i < argsLength; i++) {
	argsAsValues[i].l = (*env)->GetObjectArrayElement(env, args, i);
      }
      returnObject = (*env)->CallObjectMethodA(env, object, methodID, 
					       argsAsValues);
    } else {
      returnObject = (*env)->CallObjectMethod(env, object, methodID, NULL);
    }
  }

  // Free the drawing surface info
  ds->FreeDrawingSurfaceInfo(dsi);

  // Unlock the drawing surface
  ds->Unlock(ds);

  // Free the drawing surface
  awt.FreeDrawingSurface(ds);

  return returnObject;
}
