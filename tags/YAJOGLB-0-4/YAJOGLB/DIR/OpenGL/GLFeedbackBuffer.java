/*
 * GLFeedbackBuffer
 *
 * $Id: GLFeedbackBuffer.java,v 1.5 2002/07/21 16:55:25 razeh Exp $
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

