/*
 * OpenGLpDataAccess
 * 
 * $Id: OpenGLpDataAccess.java,v 1.4 1999/04/29 01:17:39 razeh Exp $
 * 
 */

package OpenGL;

/**
 * Provides a public interface for getting at the native details of an 
 * OpenGLCanvas.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.3
 */

public interface OpenGLpDataAccess {
  /** Lets the private object know that an OpenGL canvas has been attached
      to it. */
  public void attach(OpenGLCanvas canvas);

  /** X11 accessors */
  public int getDrawable(java.awt.Canvas canvas);
  public int getColormapID(java.awt.Canvas canvas);

  /** Win32 accessors */
  public int getHWnd(java.awt.Canvas canvas);
  public int getHDC(java.awt.Canvas canvas);

}
