/*
 Provides support for display mapping under MacOS X.
 
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
 * linuxDPYDictionary.c
 *
 * $Id: linuxDPYDictionary.c,v 1.5 2002/11/23 14:31:54 razeh Exp $
 *
 * This implements the linux functions that aquire the display related
 * information from an OpenGLCanvas.  
 */

#include "SystemIncludes.h"
#include "JNIInterface.h"
#include "ErrorHandling.h"
#include "macosx_CanvasInfo.h"

/*
 * Free the JAWT information aquired inside of getCanvasInfo, and unlock
 * the canvas as well.
 */
void freeCanvasInfo(JNIEnv *env, CanvasInfo info)
{
	JAWT awt;
	jboolean result;
	
	awt.version = JAWT_VERSION_1_3;
	result = JAWT_GetAWT(env, &awt);
	if (result == JNI_FALSE) {
		handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get JAWT_GetAWT.\n");
		return;
	}

	if (info.view) {
		info.ds->FreeDrawingSurfaceInfo(info.dsi);
		info.ds->Unlock(info.ds);
		awt.FreeDrawingSurface(info.ds);
	}
}



/*
 * Returns an info structure for the supplied canvas.  If we are unable to
 * aquire the information an exception will be thrown and display and drawable
 * will be NULL.  If the information was aquire then the canvas will locked and 
 * can be unlocked by calling freeCanvasInfo.
 */
CanvasInfo getCanvasInfo(JNIEnv *env, jobject canvas)
{
	CanvasInfo info;
	{
		JAWT awt;
		JAWT_MacOSXDrawingSurfaceInfo *dsi_mox = 0; // cocoaViewRef
		jboolean result;
		jint lock;
		
		awt.version = JAWT_VERSION_1_3;
		result = JAWT_GetAWT(env, &awt);
		if (result == JNI_FALSE) {
			handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get JAWT_GetAWT.\n");
			return info;
		}
		
		info.ds = awt.GetDrawingSurface(env, canvas);
		if (info.ds == NULL) {
			handleError(env, OPENGL_CANVAS_EXCEPTION, "Unable to get JAWT drawing surface.");
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
			return info;
		}
		
		dsi_mox = (JAWT_MacOSXDrawingSurfaceInfo*)info.dsi->platformInfo;
		if (dsi_mox == NULL) {
			handleError(env, OPENGL_CANVAS_EXCEPTION, 
						"Unable to get X11 drawing surface info.");
			info.ds->Unlock(info.ds);
			return info;
		}
		info.view = dsi_mox->cocoaViewRef;
		// info.display = dsi_mox->display;
		// info.drawable = dsi_mox->drawable;
	}
	
	return info;
}

