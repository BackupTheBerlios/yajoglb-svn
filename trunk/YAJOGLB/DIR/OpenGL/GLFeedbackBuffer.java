/*
 * OpenGLFeedbackBuffer
 *
 * $Id: GLFeedbackBuffer.java,v 1.2 1998/11/01 02:16:43 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/**
 * An GLFeedbackBuffer is used to hold a buffer of floats for the
 * OpenGL feedback buffer.
 *
 * It's possible that the native array allocated will be a copy, in
 * which case we have to take extra steps to make sure that the Java
 * array matches the native array when we look at it.  The private
 * boolean nativeArrayIsCopy handles that.  However, this has not been
 * tested.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1 */

public class GLFeedbackBuffer 
{
  /** This is true if the native version of our buffer is only a copy,
      in which case we have to take special measures when accessing
      it. */
  private boolean nativeArrayIsCopy = false;
  
  /** @param isCopy what nativeArrayIsCopy will be set to. */
  private void setNativeArrayIsCopy(boolean isCopy) {
    nativeArrayIsCopy = isCopy;
  }

  /** @return Returns true if our native array is only a copy. */
  private boolean nativeArrayIsCopy() {
    return nativeArrayIsCopy;
  }

  /** Where our OpenGL feedback buffer lives. */
  private float buffer[];

  /** Where buffer[] lives on the C heap. */
  private int bufferPointer;

  /** Creates a feedback buffer of type and buffer size. <P> 
      @param bufferSize the size of the buffer we will allocate.  
      @exception IllegalArgumentSize thrown if bufferSize is < 1.
  */

  public GLFeedbackBuffer(int bufferSize) {
    if (bufferSize > 0) 
      buffer = new float[bufferSize];
    else
      throw new
	java.lang.IllegalArgumentException("The bufferSize must be > 0.");
    mapBuffer(buffer);
  }

  /** Use this feedback buffer object as the buffer. 
      @param type a constant describing what OpenGL stores in the buffer.  It
      can be one of GL_2D, GL_3D, GL_3D_COLOR, GL_3D_COLOR_TEXTURE, or
      GL_4D_COLOR_TEXTURE.
   */
  public void feedbackBuffer(int type) {
    bufferPointer = mapBuffer(buffer);
    feedbackBuffer(buffer.length, type, bufferPointer);
  }

  private native void feedbackBuffer(int size, int type, int bufferPointer);
  
  /** Map the buffer into the C Heap as a global, and call the private
      method setNativeArrayIsCopy with the appropriate argument. */
  private native int mapBuffer(float buffer[]);

  /** Unmap the buffer from the C Heap. */
  private native void unmapBuffer(float buffer[], int bufferPointer);

  /** Force a copy from the native C heap array to buffer. */
  private native void copyBuffer(float buffer[], int bufferPointer);

  /** Invoke unmapBuffer to release our feedback buffer. */
  public void finalize() throws Throwable {
    unmapBuffer(buffer, bufferPointer);
    buffer = null;
    bufferPointer = 0;
    super.finalize();
  }

  /** Return the size of our buffer. */
  public int elementCount() {
    return buffer.length;
  }

  /** Return the ith element in the feedback buffer. */
  public float elementAt(int i) {
    /* If our array is copy, bring it into sync by calling copyBuffer. */
    if (nativeArrayIsCopy()) {
      copyBuffer(buffer, bufferPointer);
      return buffer[i];
    } else {
      return buffer[i];
    }
  }
}

