/*
 * OpenGLPeerAccess
 *
 * $Id: OpenGLPeerAccess.java,v 1.1 1998/09/10 01:02:16 razeh Exp $
 *
 */

package OpenGL;

import java.awt.*;

interface OpenGLPeerAccess {
  public int getHWnd(java.awt.Canvas canvas);
  public int getHDC(java.awt.Canvas canvas);
}
