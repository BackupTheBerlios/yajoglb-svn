/*
  Support for feedback buffers.

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
 * GLFeedbackBuffer
 *
 * $Id: GLFeedbackBuffer.java,v 1.6 2003/04/19 13:40:58 razeh Exp $
 *
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 */

package OpenGL;

/**
 * A GLFeedbackBuffer is used to hold a buffer of floats for the
 * OpenGL feedback buffer.
 *
 * It's possible that the native array allocated will be a copy, in
 * which case we have to take extra steps to make sure that the Java
 * array matches the native array when we look at it.  The private
 * boolean nativeArrayIsCopy handles that.  However, this has not been
 * tested.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.3
 */

public class GLFeedbackBuffer extends GLNativeFloatArray
{
  /** Make sure that we load in our native library. */
  static {
    NativePackageLoader.loadNativeLibrary();
  }

  /** Creates a feedback buffer.
      @param bufferSize the size of our buffer. */
  public GLFeedbackBuffer(int bufferSize) {
    super(bufferSize);
  }

  private native void feedbackBuffer(int size, int type, int bufferPointer);

  /** Use this feedback buffer object as the buffer. 
      @param type a constant describing what OpenGL stores in the buffer.  It
      can be one of GL_2D, GL_3D, GL_3D_COLOR, GL_3D_COLOR_TEXTURE, or
      GL_4D_COLOR_TEXTURE.
   */
  public void feedbackBuffer(int type) {
    setBufferPointer(mapBuffer(buffer()));
    feedbackBuffer(buffer().length, type, bufferPointer());
  }
}

