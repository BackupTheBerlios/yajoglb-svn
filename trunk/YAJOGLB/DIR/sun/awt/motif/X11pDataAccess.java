/*
 * $Id: X11pDataAccess.java,v 1.1 1999/02/13 18:52:14 razeh Exp $
 *
 * Taken (and then modified) from jogl-0.7
 *
 */

/* Class that package spoofs sun.awt.motif to get the
   pData out of X11Graphics */

package sun.awt.motif;

import sun.awt.*;
import OpenGL.OpenGLpDataAccess;
import java.awt.Canvas;
import java.awt.Graphics;

/**
 * This class is used to get to the raw X11 pointers used by Java for 
 * peer window support. 
 */
public class X11pDataAccess implements OpenGLpDataAccess {
  /** This returns the X11 drawing surface for a given graphics object. */
  private X11DrawingSurface getDrawingSurface (java.awt.Canvas canvas) {
      MCanvasPeer cp = (MCanvasPeer) canvas.getPeer();
      X11DrawingSurface xds = (X11DrawingSurface) cp.getDrawingSurfaceInfo();

      return xds;
  }

  public int getDisplay(Canvas canvas) {
      return getDrawingSurface(canvas).getDisplay();
  }

  public int getDrawable(Canvas canvas) {
      return getDrawingSurface(canvas).getDrawable();
  }

  public int getColormapID(Canvas canvas) {
      return getDrawingSurface(canvas).getColormapID();
  }
  
  /* This accessors are really for win32. */
  public int getHWnd(java.awt.Canvas canvas) {
    return 0;
  }

  public int getHDC(java.awt.Canvas canavs) {
    return 0;
  }
}
