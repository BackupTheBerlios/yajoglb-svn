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

/*
 * Class:     OpenGL_Canvas
 * Method:    lockCanvas
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_OpenGL_Canvas_lockCanvas
  (JNIEnv *env, jobject canvas)
{
#ifdef USE_JAWT
  JAWT awt;
  jboolean result;
  jint lock;

  awt.version = JAWT_VERSION_1_3;
  result = JAWT_GetAWT(env, &awt);
  if (result != JNI_FALSE) {
    JAWT_DrawingSurface *ds = awt.GetDrawingSurface(env, canvas);
    lock = ds->Lock(ds);
    if (lock & JAWT_LOCK_ERROR) {
      handleError(env, OPENGL_CANVAS_EXCEPTION,
		  "Unable to lock JAWT drawing surface.");
    } 
  } else {
    handleError(env, OPENGL_CANVAS_EXCEPTION,
		"Unable to get JAWT drawing surface.");
  }
#endif
}



/*
 * Class:     OpenGL_Canvas
 * Method:    unlockCanvas
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_OpenGL_Canvas_unlockCanvas
  (JNIEnv *env, jobject canvas)
{
#ifdef USE_JAWT
  JAWT awt;
  jboolean result;


  awt.version = JAWT_VERSION_1_3;
  result = JAWT_GetAWT(env, &awt);
  if (result != JNI_FALSE) {
    JAWT_DrawingSurface *ds = awt.GetDrawingSurface(env, canvas);
    ds->Unlock(ds);
  } else {
    handleError(env, OPENGL_CANVAS_EXCEPTION, 
		"Unable to get JAWT drawing surface.");
  }
#endif
}

