package sun.awt.windows;

import sun.awt.windows.*;
import sun.awt.Win32DrawingSurface;
import OpenGL.OpenGLpDataAccess;
import java.awt.Graphics;
import java.awt.Canvas;
import java.awt.peer.*;

public class WindowspDataAccess implements OpenGLpDataAccess
{
  public int getInfo( Graphics g )
    {
      return ((WGraphics)g).pData;
    }

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
}
