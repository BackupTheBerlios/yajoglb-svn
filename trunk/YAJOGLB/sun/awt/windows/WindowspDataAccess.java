/*
 * $Id$
 *
 * Taken (and then modified) from jogl-0.7
 *
 */

package sun.awt.windows;

import sun.awt.DrawingSurface;
import sun.awt.DrawingSurfaceInfo;
import sun.awt.windows.*;
import sun.awt.Win32DrawingSurface;
import OpenGL.OpenGLpDataAccess;
import OpenGL.OpenGLCanvas;
import java.awt.Graphics;
import java.awt.Canvas;
import java.awt.peer.*;

/**
 * This class is used to access the raw window pointer and device
 * context from a canvas object.  It will, of course, only function
 * under windows. 
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.3
 */
public class WindowspDataAccess implements OpenGLpDataAccess {

  /** Invoked by our OpenGLCanvas when it attaches to us. */
  public void attach(OpenGLCanvas canvas) {
    ;
  }
  
  /** Returns the device context for canvas. */
  public int getHDC(Canvas canvas) {
    DrawingSurfaceInfo drawingSurfaceInfo;
    Win32DrawingSurface win32DrawingSurface;
    int hdc = 0;
    
    drawingSurfaceInfo = ((DrawingSurface)(canvas.getPeer())).getDrawingSurfaceInfo();
    
    if (null != drawingSurfaceInfo) {
      drawingSurfaceInfo.lock();
      win32DrawingSurface = (Win32DrawingSurface)drawingSurfaceInfo.getSurface();
      hdc = win32DrawingSurface.getHDC();

      drawingSurfaceInfo.unlock();
    }

    return hdc;
  }


  /* X11 accessors that return 0 here. */
  public int getColormapID(Canvas g) {
    return 0;
  }

  public int getDrawable(Canvas g) {
    return 0;
  }
}
