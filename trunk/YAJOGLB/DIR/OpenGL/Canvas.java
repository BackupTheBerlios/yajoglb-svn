/*
 * OpenGLCanvas class
 *
 * $Id: Canvas.java,v 1.5 1999/02/13 19:30:08 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

import java.awt.*;
import java.lang.Class;

/** This provides an embedded object that OpenGL can render into.  It
 * is similar to a normal Canvas object, but it can be setup with
 * OpenGLCapabilities that describe how OpenGL should render into the
 * canvas.  For example, the precision of the depth buffer is
 * specified via the OpenGLCapabilities.  If no capabilities are
 * specified, a default capabilities object will be used.  */
public class OpenGLCanvas extends Canvas {
  
  /* Make sure that we load in our native library. */
  static {
    System.load("YAJOGLB");
  }

  /** This holds the capabilities we will request of our display. */
  private OpenGLCapabilities capabilities;

  /** True if we have called our native setup code. */
  private boolean canvasHasBeenSetup = false;

  public OpenGLCanvas() {
    super();

    try {
      Class dataAccessClass = Class.forName(dataAccessClass());
      dataAccess = (OpenGLpDataAccess)dataAccessClass.newInstance();
    } catch (java.lang.InstantiationException exception) {
      throw new OpenGLNativeException("Unable to create a data access instance: " +
				      exception);
    } catch (java.lang.ClassNotFoundException exception) {
      throw new OpenGLNativeException("Unable to create a data access instance: " +
				      exception);
    } catch (java.lang.IllegalAccessException exception) {
      throw new OpenGLNativeException("Unable to create a data access instance: " +
				      exception);
    }

    setCapabilities(defaultCapabilities());
  }

  private native boolean setupOpenGLCanvas();

  /** The default OpenGLCapabilities object that we return at startup
      for our display. */
  private OpenGLCapabilities defaultCapabilities() {
    return OpenGLCapabilities.defaultCapabilities();
  }

  /** Sets the capabilities that this widget will use when we are
     opened up.  This has no effect once the canvas has been displayed
     on screen. */
  protected void setCapabilities(OpenGLCapabilities newCapabilities) {
    capabilities = newCapabilities;
  }

  /** Returns the capabilities object that was used when we started
      our display. */
  protected OpenGLCapabilities capabilities() {
    return capabilities;
  }

  /** This handles the actual setup for our OpenGL canvas. */
  private void init() {
    if (false == setupOpenGLCanvas()) {
      throw new OpenGLCanvasSetupFailedException("Unable to setup the canvas.");
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
      glInit() and paint(). This is final to prevent any subclasses
      from mucking things up! */
  final public void paint(Graphics g) {
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
  private native void nativeSwapBuffers();

  /** This swaps in the double buffer that we've been using.  If
      double buffering is enabled and you don't call this after you
      draw, nothing will be displayed on the screen. */
  public void swapBuffers() {
    nativeSwapBuffers();
  }
  
  /** Returns the class to use for data access. */
  static private native String dataAccessClass();

  private OpenGLpDataAccess dataAccess;

  /** Returns the X11 display pointer. */
  int getDisplay() {
    return dataAccess.getDisplay(this);
  }
  
  /** Returns the X11 drawable pointer. */
  int getDrawable() {
    return dataAccess.getDrawable(this);
  }

  /** Returns the Win32 hDC. */
  int getHDC() {
    return dataAccess.getHDC(this);
  }

}





