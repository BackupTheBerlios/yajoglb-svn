/*
 * OpenGLpDataAccess
 * 
 * $Id: OpenGLpDataAccess.java,v 1.1 1998/09/10 01:06:04 razeh Exp $
 * 
 */

package OpenGL;

public interface OpenGLpDataAccess {
  /* Gets the secret window information! */
  public int getInfo(java.awt.Graphics g);
  public int getHWnd(java.awt.Canvas canvas);
  public int getHDC(java.awt.Canvas canvas);
}
