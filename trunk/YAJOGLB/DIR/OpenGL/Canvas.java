/*
  Provides a canvas to render OpenGL into.
 
  Copyright 2001, Robert Allan Zeh (razeh@yahoo.com)
  7346 Lake Street #3W
  River Forest, IL 60305
 
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA

*/

/*
 * Canvas class
 *
 * $Id: Canvas.java,v 1.7 2001/07/06 23:42:57 razeh Exp $
 *
 */

package OpenGL;

import java.awt.*;
import java.lang.Class;

/** This provides an embedded object that OpenGL can render into.  It
 * is similar to a normal Canvas object, but it can be setup with
 * Capabilities that describe how OpenGL should render into the
 * canvas.  For example, the precision of the depth buffer is
 * specified via the Capabilities.  If no capabilities are specified,
 * a default capabilities object will be used.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.4 */

abstract public class Canvas extends java.awt.Canvas {
  
  /** Make sure that we load in our native library. */
  static {
    NativePackageLoader.loadNativeLibrary();
  }

  /** This holds the capabilities we will request of our display. */
  private Capabilities capabilities;

  /** True if we have called our native setup code. */
  private boolean canvasHasBeenSetup = false;

  public Canvas() {
    super();

    /*
    try {
      Class dataAccessClass = Class.forName(dataAccessClass());
      dataAccess = (OpenGLpDataAccess)dataAccessClass.newInstance();
    } catch (java.lang.InstantiationException exception) {
      throw new NativeException("Unable to create a data access instance: " +
				      exception);
    } catch (java.lang.ClassNotFoundException exception) {
      throw new NativeException("Unable to create a data access instance: " +
				      exception);
    } catch (java.lang.IllegalAccessException exception) {
      throw new NativeException("Unable to create a data access instance: " +
				      exception);
    }
    */
    setCapabilities(defaultCapabilities());
  }

  private native boolean setupCanvas();

  /** The default Capabilities object that we return at startup
      for our display. */
  private Capabilities defaultCapabilities() {
    return Capabilities.defaultCapabilities();
  }

  /** Sets the capabilities that this widget will use when we are
     opened up.  This has no effect once the canvas has been displayed
     on screen. */
  protected void setCapabilities(Capabilities newCapabilities) {
    capabilities = newCapabilities;
  }

  /** Returns the capabilities object that was used when we started
      our display. */
  protected Capabilities capabilities() {
    return capabilities;
  }

  /** This handles the actual setup for our OpenGL canvas. */
  private void init() {
    if (false == setupCanvas()) {
      throw new CanvasSetupFailedException("Unable to setup the canvas.");
    }
  }

  /** An empty method that subclasses can invoke to handle OpenGL setup. */
  public void glInit() {
    ;
  }

  /** The method that subclasses should override for rendering.  It is 
   invoked by <code>paint(Graphics g)</code>. */
  abstract public void paint();

  /** This is overriden to handle our canvas setup, and calling
      glInit() and paint(). This is final to prevent any subclasses
      from mucking things up! <P> We do not call our super method,
      because doing so leaves our display set to the foreground color
      after redisplays under X.  */
  final public void paint(Graphics g) {
      // If we have not been setup, set ourself up.
      if (false == canvasHasBeenSetup) {
	  init();
	  glInit();
	  // Make sure the setup only happens once.
	  canvasHasBeenSetup = true;
      }
      paint();
  }

  protected native void lockCanvas();
  protected native void unlockCanvas();
  
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

  /** Returns the data access object used to return our drawable and
      hDC. */
  OpenGLpDataAccess getDataAccess() {
    return dataAccess;
  }

  /** Returns the Win32 hDC. */
  int getHDC() {
    return dataAccess.getHDC(this);
  }
}
