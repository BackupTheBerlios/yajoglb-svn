/*
  The DC <-> Canvas dictionary for Win32.
 
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
 * win32DCDictionary.c
 *
 * $Id$
 *
 * This implements the win32 functions that aquire the DC from an OpenGLCanvas object. 
 *
 */

#include "jawt_md.h"
#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include "SystemError.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"
#include "win32DCDictionary.h"



void freeCanvasInfo(JNIEnv *env, CanvasInfo info)
{
	JAWT awt;
	jboolean result;
	awt.version = JAWT_VERSION_1_3;
	result = JAWT_GetAWT(env, &awt);
	if (result == JNI_FALSE) {
		handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get JAWT_GetAWT.");
	}

	if (info.hDC) {
		info.ds->FreeDrawingSurfaceInfo(info.dsi);
		info.ds->Unlock(info.ds);
		awt.FreeDrawingSurface(info.ds);
	}
}



CanvasInfo getCanvasInfo(JNIEnv *env, jobject canvas)
{
	CanvasInfo info;
	JAWT awt;
	JAWT_Win32DrawingSurfaceInfo* dsi_win;
	jboolean result;
	jint lock;

	info.hDC = 0;
	awt.version = JAWT_VERSION_1_3;
	result = JAWT_GetAWT(env, &awt);
	if (result == JNI_FALSE) {
	  handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get JAWT_GetAWT.");
	  return info;
	}
		
	info.ds = awt.GetDrawingSurface(env, canvas);
	if (info.ds == NULL) {
	  handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get JAWT drawing surface.");
	  info.ds->Unlock(info.ds);
	  return info;
	}
	lock = info.ds->Lock(info.ds);
	if (lock & JAWT_LOCK_ERROR) {
	  handleError(env, OPENGL_CANVAS_EXCEPTION, 
		      "Unable to lock JAWT surface.");
	  info.ds->Unlock(info.ds);
	  return info;
	}
		
	info.dsi = info.ds->GetDrawingSurfaceInfo(info.ds);
	if (info.dsi == NULL) {
	  handleError(env, OPENGL_CANVAS_EXCEPTION, 
		      "Unable to get drawing surface info.");
	  info.ds->Unlock(info.ds);
	  return info;
	}
		
	dsi_win = (JAWT_Win32DrawingSurfaceInfo*)info.dsi->platformInfo;
	if (dsi_win == NULL) {
	  handleError(env, OPENGL_CANVAS_EXCEPTION, 
		      "Unable to get win32 drawing surface info.");
	  info.ds->Unlock(info.ds);
	  return info;
	}
	info.hDC = dsi_win->hdc;

	return info;
}
