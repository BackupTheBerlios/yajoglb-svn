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
#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include "OpenGL_Canvas.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"


/*
 * Class:     OpenGL_Canvas
 * Method:    nativePaint
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_OpenGL_Canvas_nativePaint
  (JNIEnv *env, jobject canvas)

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
	 jmethodID methodID = getMethodID(env, canvasClass, "paint", "()V",
		 "Unable to get paint method.");
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

