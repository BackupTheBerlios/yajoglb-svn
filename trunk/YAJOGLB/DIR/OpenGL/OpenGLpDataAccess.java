/*
 * OpenGLpDataAccess
 * 
 * $Id: OpenGLpDataAccess.java,v 1.3 1999/02/13 19:30:08 razeh Exp $
 * 
 */

package OpenGL;

public interface OpenGLpDataAccess {

  /** X11 accessors */
  public int getDisplay(java.awt.Canvas canvas);
  public int getDrawable(java.awt.Canvas canvas);
  public int getColormapID(java.awt.Canvas canvas);

  /** Win32 accessors */
  public int getHWnd(java.awt.Canvas canvas);
  public int getHDC(java.awt.Canvas canvas);

}
