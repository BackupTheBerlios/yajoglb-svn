/*
 * OpenGLCapabilities
 *
 * $Id: Capabilities.java,v 1.1 1997/11/16 02:49:19 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/** OpenGLCapabilities
 *
 * This defines the screen display capabilities that we are going to
 * request when we open up our window.  Changing it after we have
 * created our window has no effect.
 *
 */

public class OpenGLCapabilities {
  /** The number of bits per pixel we have for color information. */
  private int colorDepth;
  /** The number of bits per pixel we have for the alpha buffer. */
  private int alphaDepth;
  /** The number of bits per pixel we have for the accumulation buffer. */
  private int accumulationDepth;
  /** The number of bits per pixel we have for the depth buffer. */
  private int depthBuffer;
  /** The color model we will be using --- this must be RGBA or ColorIndex. */
  private int colorType;
  /** TRUE if we want to use double buffering and FALSE if we do not. */
  private boolean isDoubleBufferEnabled;
  /** The number of bits per pixel for the stencil buffer. */
  private int stencilBuffer;

  /** We will specify our colors as RGBA quadruples. */
  static final int RGBA       = 0;
  /** We will specify color indicies. */
  static final int ColorIndex = 1;

  /** Set the number of bits per pixel we use for our color depth. */
  public void setColorDepth(int newColorDepth) {
    colorDepth = newColorDepth;
  }

  /** Returns the number of bits per pixel we set for our color depth. */
  public int colorDepth() {
    return colorDepth;
  }

  /** Sets the number of bits per pixel we want for our alpha
      buffer. */
  public void setAlphaDepth(int newAlphaDepth) {
    alphaDepth = newAlphaDepth;
  }
  
  /** Returns the number of bits per pixel for the alpha buffer. */
  public int alphaDepth() {
    return alphaDepth;
  }

  /** Sets the number of bits per pixel we want for the accumulation
      buffer. */
  public void setAccumulationDepth(int newAccumulationDepth) {
    accumulationDepth = newAccumulationDepth;
  }

  /** Returns the number of pits per pixel we want for the
      accumulation buffer. */
  public int accumulationDepth() {
    return accumulationDepth;
  }

  /** Sets the number of bits per pixel we want for the depth buffer. */
  public void setDepthBuffer(int newDepthBuffer) {
    depthBuffer = newDepthBuffer;
  }

  /** Returns the number of bits per pixel we wanted for the depth buffer. */
  public int depthBuffer() {
    return depthBuffer;
  }

  /** Sets the number of bits per pixel for the stencil buffer. */
  public void setStencilBuffer(int newStencilBuffer) {
    stencilBuffer = newStencilBuffer;
  }

  /** Returns the number of pits per pixel for the stencil buffer. */
  public int stencilBuffer() {
    return stencilBuffer;
  }

  /** Sets the color type we want to use.  If the newColorType is not
      a valid one (RGBA or ColorIndex) an IllegalArgumentException is
      thrown. */
  public void setColorType(int newColorType) {
    switch (newColorType) {
    case RGBA:
    case ColorIndex:
      colorType = newColorType;      
      break;
    default:
      throw new 
	IllegalArgumentException("An invalid color type was given to OpenGLCapabilities.setColorType()");
    }
  }
  
  /** Returns the color type we asked for. */
  public int colorType() {
    return colorType;
  }

  /** Sets double buffering.  YES means we want double buffer and no
      means that we do not care. */
  public void setDoubleBufferEnabled(boolean newDoubleBuffer) {
    isDoubleBufferEnabled = newDoubleBuffer;
  }

  /** Returns TRUE if we requested double buffering and FALSE if we
      did not care. */
  public boolean isDoubleBufferedEnabled() {
    return isDoubleBufferEnabled;
  }

  /** A simple constructor that will set all of our fields to the
      supplied values. */
  public OpenGLCapabilities(int initialColorDepth,
			    int initialAlphaDepth,
			    int initialAccumulationDepth,
			    int initialDepthBuffer,
			    int initialStencilBuffer,
			    int initialColorType,
			    boolean initialIsDoubleBufferEnabled)
  {
    setColorDepth(initialColorDepth);
    setAlphaDepth(initialAlphaDepth);
    setAccumulationDepth(initialAccumulationDepth);
    setDepthBuffer(initialDepthBuffer);
    setStencilBuffer(initialStencilBuffer);
    setColorType(initialColorType);
    setDoubleBufferEnabled(initialIsDoubleBufferEnabled);
  }

  /** A handy default capability to use that has 16 bits for color,
   16 bits for the depth buffer, double buffering, and RGBA color. */
  static OpenGLCapabilities defaultCapabilities() {
    return new OpenGLCapabilities(16, 0, 0, 16, 0, RGBA, true);
  }
}
