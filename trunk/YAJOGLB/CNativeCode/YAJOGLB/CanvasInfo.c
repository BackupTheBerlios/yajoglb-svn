/*
  Provides support for getting information from JAWT.
 
  Copyright 2001, Robert Allan Zeh (razeh@yahoo.com)
  43 Gale
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

#include <memory.h>
#include "CanvasInfo.h"
#include "ErrorHandling.h"

/*
 * Returns a locked info structure for the supplied canvas.  If we are
 * unable to aquire the information an exception will be thrown and
 * display and drawable will be NULL.  If the information was aquire
 * then the canvas will locked and can be unlocked by calling
 * freeCanvasInfo.
 */
CanvasInfo getCanvasInfo(JNIEnv *env, jobject canvas)
{
  CanvasInfo info;
  jboolean result;
  jint lock;
  
  memset(&info, sizeof info, 0);
  info.awt.version = JAWT_VERSION_1_4;
  result = JAWT_GetAWT(env, &info.awt);
  if (result == JNI_FALSE) {
    handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get JAWT_GetAWT.\n");
    return info;
  }
  
  info.ds = info.awt.GetDrawingSurface(env, canvas);
  if (info.ds == NULL) {
    handleError(env, OPENGL_CANVAS_EXCEPTION, 
		"Unable to get JAWT drawing surface.");
    return info;
  }
  
  lock = info.ds->Lock(info.ds);
  if (lock & JAWT_LOCK_ERROR) {
    handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to lock JAWT surface.");
    return info;
  }
  
  info.dsi = info.ds->GetDrawingSurfaceInfo(info.ds);
  if (info.dsi == NULL) {
    handleError(env, OPENGL_CANVAS_EXCEPTION, 
		"Unable to get drawing surface info.");
    info.ds->Unlock(info.ds);
    if ((*env)->ExceptionOccurred(env)) {
      (*env)->ExceptionDescribe(env);
    }
    return info;
  }
  
  return info;
}



/* Unlocks and frees a structure for the supplied info object.
*/
void freeCanvasInfo(JNIEnv *env, CanvasInfo info)
{
  if (info.dsi) {
    info.ds->FreeDrawingSurfaceInfo(info.dsi);
    if ((*env)->ExceptionOccurred(env)) {
      (*env)->ExceptionDescribe(env);
    }
  }

  if (info.ds) {
    info.ds->Unlock(info.ds);
    if ((*env)->ExceptionOccurred(env)) {
      (*env)->ExceptionDescribe(env);
    }
    info.awt.FreeDrawingSurface(info.ds);
    if ((*env)->ExceptionOccurred(env)) {
      (*env)->ExceptionDescribe(env);
    }
  }
}
