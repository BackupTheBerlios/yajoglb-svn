/*
 * $Id: WindowspDataAccess.java,v 1.3 1999/02/13 18:55:59 razeh Exp $
 *
 * Taken (and then modified) from jogl-0.7
 *
 */

package sun.awt.windows;

import sun.awt.windows.*;
import sun.awt.Win32DrawingSurface;
import OpenGL.OpenGLpDataAccess;
import java.awt.Graphics;
import java.awt.Canvas;
import java.awt.peer.*;

/**
 * This class is used to access the raw window pointer and device
 * context from a canvas object.  It will, of course, only function
 * under windows. 
*/
public class WindowspDataAccess implements OpenGLpDataAccess {
  public int getHWnd(Canvas canvas) {
    int Hwnd;
    WCanvasPeer peer = (WCanvasPeer) canvas.getPeer();
    WDrawingSurfaceInfo surface =
      (WDrawingSurfaceInfo) peer.getDrawingSurfaceInfo();
    /* If we don't lock the surface we will be unable to aquire the
       window handle. */
    surface.lock();
    Hwnd = surface.getHWnd();
    surface.unlock();
    return Hwnd;
  }

  public int getHDC(Canvas canvas) {
    WCanvasPeer peer = (WCanvasPeer) canvas.getPeer();
    WDrawingSurfaceInfo surface =
      (WDrawingSurfaceInfo) peer.getDrawingSurfaceInfo();
    /* If we don't lock the surface we will be unable to aquire the
       device context. */
    surface.lock();
    int HDC= surface.getHDC();
    surface.unlock();
    return HDC;
  }


  /* X11 accessors */
  public int getColormapID(Canvas g) {
    return 0;
  }

  public int getDrawable(Canvas g) {
    return 0;
  }

  public int getDisplay(Canvas g) {
    return 0;
  }

}
