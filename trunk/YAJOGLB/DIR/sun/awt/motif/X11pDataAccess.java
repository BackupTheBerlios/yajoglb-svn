/*
 * $Id: X11pDataAccess.java,v 1.2 1999/04/29 01:25:34 razeh Exp $
 *
 * Taken (and then modified) from jogl-0.7
 *
 */

/* Class that package spoofs sun.awt.motif to get the
   pData out of X11Graphics */

package sun.awt.motif;

import sun.awt.*;
import OpenGL.OpenGLpDataAccess;
import OpenGL.OpenGLCanvas;
import java.awt.Canvas;
import java.awt.Graphics;

/**
 * This class is used to get to the raw X11 pointers used by Java for 
 * peer window support. 
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.3
 */
public class X11pDataAccess implements OpenGLpDataAccess {
  /** The Display that we setup for the OpenGLCanvas we belong to. 
   @return the display for our OpenGLCanvas. */
  private int privateDisplay;
  
  /** This returns the X11 drawing surface for a given graphics object. 
   @return the X11 drawing surface for canvas. */
  private X11DrawingSurface getDrawingSurface (java.awt.Canvas canvas) {
      MCanvasPeer cp = (MCanvasPeer) canvas.getPeer();
      X11DrawingSurface xds = (X11DrawingSurface) cp.getDrawingSurfaceInfo();

      return xds;
  }

  /** Returns the Display we setup for our canvas. 
      @return the Display previously set for our canvas. */
  public int getDisplay() {
    return privateDisplay;
  }

  /** Sets the Display we setup for our canvas. 
      @param display our new display that will be returned by getDisplay. */
  public void setDisplay(int display) {
    privateDisplay = display;
  }

  /** Returns the drawable for our canvas.
      @param canvas the canvas whose color map we want
      @return the drawable for canvas. */
  public int getDrawable(Canvas canvas) {
      return getDrawingSurface(canvas).getDrawable();
  }

  /** Returns the color map ID for canvas. 
      @param canvas the canvas whose color map we want
      @return the color map ID for canvas. */
  public int getColormapID(Canvas canvas) {
      return getDrawingSurface(canvas).getColormapID();
  }
  
  /** This accessors is really for win32, and simply returns 0.
     @param canvas ignored
     @return always 0. */
  public int getHWnd(java.awt.Canvas canvas) {
    return 0;
  }

  /* This accessor is really here for win32, and simply returns 0. 
     @param canvas ignored
     @return always 0. */
  public int getHDC(java.awt.Canvas canavs) {
    return 0;
  }



  /** Invoked by our OpenGLCanvas when it attaches to us. */
  public void attach(OpenGLCanvas canvas) {
    
  }


}






