/*
 * OpenGLpDataAccess
 * 
 * $Id: OpenGLpDataAccess.java,v 1.2 1998/11/09 01:07:51 razeh Exp $
 * 
 */

package OpenGL;

public interface OpenGLpDataAccess {
  /** Gets the WIN32 specific window information. */
  public int getInfo(java.awt.Graphics g);
  public int getHWnd(java.awt.Canvas canvas);
  public int getHDC(java.awt.Canvas canvas);
}
