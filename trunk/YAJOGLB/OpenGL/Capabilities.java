/*
  Describes rendering information about a canvas.
 
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

package OpenGL;

/**
 *
 * Defines the screen display capabilities that our Canvas will
 * Request at startup.  Changing it after the window has been opened
 * has no effect.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.4 
 */

public class Capabilities {
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
  /** We will specify color indices. */
  static final int ColorIndex = 1;

  /** Set the number of bits per pixel we use for our color depth. 
    * @param newColorDepth the number of bits to use for our color information. */
  public void setColorDepth(int newColorDepth) {
    colorDepth = newColorDepth;
  }

  /** Returns the number of bits per pixel we set for our color depth. 
    @return The number of bits per pixel used for our color depth.*/
  public int getColorDepth() {
    return colorDepth;
  }

  /** Sets the number of bits per pixel we want for our alpha
      buffer. */
  public void setAlphaDepth(int newAlphaDepth) {
    alphaDepth = newAlphaDepth;
  }
  
  /** Returns the number of bits per pixel for the alpha buffer.
    * @return The number of bits per pixel for the alpha buffer. */
  public int getAlphaDepth() {
    return alphaDepth;
  }

  /** Sets the desired number of bits per pixel for the accumulation
      buffer. 
    * @param newAccumulationDepth the number of bits per pixel that the accumulation buffer will use. */
  public void setAccumulationDepth(int newAccumulationDepth) {
    accumulationDepth = newAccumulationDepth;
  }

  /** Returns the desired number of pits per pixel for the
      accumulation buffer. 
    * @return the bits per pixel for the accumulation buffer. */
  public int getAccumulationDepth() {
    return accumulationDepth;
  }

  /** Sets the number of bits per pixel we want for the depth buffer.
    * @param newDepthBuffer the number of bits per pixel for the depth
    * buffer. */
  public void setDepthBuffer(int newDepthBuffer) {
    depthBuffer = newDepthBuffer;
  }

  /** Returns the number of bits per pixel requested for the depth buffer.
    * @return the bits per pixel used by the depth buffer. */

  public int getDepthBuffer() {
    return depthBuffer;
  }

  /** Sets the number of bits per pixel for the stencil buffer. */
  public void setStencilBuffer(int newStencilBuffer) {
    stencilBuffer = newStencilBuffer;
  }

  /** Returns the number of pits per pixel for the stencil buffer. */
  public int getStencilBuffer() {
    return stencilBuffer;
  }

  /** Sets the desired color type.  If the newColorType is not
      a valid one (RGBA or ColorIndex) an IllegalArgumentException is
      thrown. 
    @param newColorType RGBA if colors are specified as RGBA
    quadruples and ColorIndex if colors should be looked up in an
    index table.
    @exception IllegalArgumentException thrown when newColorType is
    not RGBA or ColorIndex. */
  public void setColorType(int newColorType) {
    switch (newColorType) {
    case RGBA:
    case ColorIndex:
      colorType = newColorType;      
      break;
    default:
      throw new 
	IllegalArgumentException("An invalid color type was given to Capabilities.setColorType()");
    }
  }
  
  /** Returns the requested color type. 
    * @return ColorIndex if colors are indexed or RGBA if colors are RGBA quadruples. */
  public int getColorType() {
    return colorType;
  }

  /** Sets double buffering.
    * @param newDoubleBuffer <code>true</code> for double buffering and <code>false</code> for do not care. */
  public void setDoubleBufferEnabled(boolean newDoubleBuffer) {
    isDoubleBufferEnabled = newDoubleBuffer;
  }

  /** Our double buffer request.  
     @return <code>true</code> if double buffering was requested and <code>false</code> otherwise. */
  public boolean getDoubleBufferEnabled() {
    return isDoubleBufferEnabled;
  }

  /** A simple constructor that will set all of our fields to the
   * supplied values.
   @param initialColorDepth the number of bits for color information
   @param initialAlphaDepth the number of bits for our alpha channel
   @param initialAccumulationDepth the number of bits for our accumulation
   buffer
   @param initialDepthBuffer the number of bits for our depth buffer
   @param initialStencilBuffer the number of bits for our stencil buffer
   @param initialIsDoubleBufferEnabled <code>true</code> to enable double buffering, <code>false</code> otherwise.
   @param initialColorType our choice of color modes
   **/

  public Capabilities(int initialColorDepth,
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

  /** A handy default capability to use that has 16 bits for color, 16
   bits for the depth buffer, enabled double buffering, and RGBA
   color. 
   @return A Capabilities with 16 bits of color, a 16 bit depth buffer, double buffer and RGBA color. */
  static Capabilities defaultCapabilities() {
    return new Capabilities(16, 0, 0, 16, 0, RGBA, true);
  }

  /** Creates a string describing the Capabilities object.
      @return A string describing the Capabilities object.
  */
  public String toString() {
    String description;

    description  = "Color depth = " + getColorDepth();
    description += "\nAlpha depth = " + getAlphaDepth();
    description += "\nAccumulation buffer depth = " + getAccumulationDepth();
    description += "\nDepth buffer depth = " + getDepthBuffer();
    description += "\nStencil buffer depth = " + getStencilBuffer();
    description += "\nColor type = ";
    if (getColorType() == RGBA) {
      description += "RGBA";
    }
    if (getColorType() == ColorIndex) {
      description += "index";
    }
    description += "\nDouble buffering is ";
    if (getDoubleBufferEnabled()) {
      description += "Enabled";
    } else {
      description += "Disable";
    }

    return description;
  }
}
