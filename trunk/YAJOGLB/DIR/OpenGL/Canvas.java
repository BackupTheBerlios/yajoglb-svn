/*
 * OpenGLCanvas class
 *
 * $Id: Canvas.java,v 1.1 1998/09/10 00:57:30 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

import java.awt.*;

/** This provides an embedded object that OpenGL can render into. */
public class OpenGLCanvas extends Canvas {
  
  /* Make sure that we load in our native library. */
  static {
    System.load("OpenGL4java");
  }

  /** This holds the capabilities we will request of our display. */
  private OpenGLCapabilities capabilities;

  /** True if we have called our native setup code. */
  private boolean canvasHasBeenSetup = false;

  public OpenGLCanvas() {
    super();
    setCapabilities(defaultCapabilities());
  }

  private native boolean setupOpenGLCanvas(int HDC, int HWnd);

  /** The default OpenGLCapabilities object that we return at startup
      for our display. */
  private OpenGLCapabilities defaultCapabilities() {
    return OpenGLCapabilities.defaultCapabilities();
  }

  /** Sets the capabilities that this widget will use when it is opened
     up.  This has no effect once the widget has been displayed on
     screen. */
  protected void setCapabilities(OpenGLCapabilities newCapabilities) {
    capabilities = newCapabilities;
  }

  /** Returns the capabilities object that was used when we started
      our display. */
  protected OpenGLCapabilities capabilities() {
    return capabilities;
  }

  /** Returns the handle to the device context for this canvas.  Windows
      specific. */
  protected int getHDC() {
    OpenGLpDataAccess dataAccess;

    dataAccess = 
      (OpenGLpDataAccess) new sun.awt.windows.WindowspDataAccess();
    return dataAccess.getHDC(this);
  }    



  /** Returns the handle to the window for this canvas.  Windows
      specific. */
  protected int getHWnd() {
    OpenGLpDataAccess dataAccess;

    dataAccess = 
      (OpenGLpDataAccess) new sun.awt.windows.WindowspDataAccess();
    return dataAccess.getHWnd(this);
  }


  /** This handles the actual setup for our OpenGL canvas. */
  private void init() {
    OpenGLpDataAccess dataAccess;

    dataAccess = 
      (OpenGLpDataAccess) new sun.awt.windows.WindowspDataAccess();
    
    if (false == setupOpenGLCanvas(dataAccess.getHDC(this),
				   dataAccess.getHWnd(this))) {
      throw new OpenGLCanvasSetupFailedException("Unable to setup the canvas");
    }
  }

  /** An empty method that subclasses can invoke to handle OpenGL setup. */
  public void glInit() {
    ;
  }

  /** The method that subclasses should override for rendering. */
  public void paint() {
    ;
  }

  /** This is overriden to handle our canvas setup, and calling
      glInit() and paint(). This should not be overriden by
      subclasses! */
  public void paint(Graphics g) {
    super.paint(g);
    if (false == canvasHasBeenSetup) {
      init();
      glInit();
      canvasHasBeenSetup = true;
    }
    paint();
  }

  /** This contains the native call needed to actually swap our display
      buffer. */
  private native void nativeSwapBuffers(int HDC);

  /** This swaps in the double buffer that we've been using.  If you
      don't call this after you draw, nothing will be displayed on the
      screen. */
  public void swapBuffers() {
    nativeSwapBuffers(getHDC());
  }
  
}
