/*
 * GLNativeFloatArray
 *
 * $Id: GLNativeFloatArray.java,v 1.1 1999/01/27 00:00:11 razeh Exp $
 *
 * Copyright 1999
 *
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/**
 * A GLNativeFloatArray is used to map floating point Java arrays to
 * native float arrays.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1 */

public class GLNativeFloatArray extends GLNativeArray {
  /** Where our float buffer lives. */
  private float buffer[];
  
  /** Returns the buffer pointer.
      @return the buffer pointer. */
  float[] buffer() {
    return buffer;
  }
  
  /** Sets our new buffer.
      @param newBuffer the new buffer array. */
  private void setBuffer(float[] newBuffer) {
    buffer = newBuffer;
  }
  
  /** Creates a feedback buffer of type and buffer size. <P> 
      @param bufferSize the size of the buffer we will allocate.  
  */
  public GLNativeFloatArray(int bufferSize) {
    setBuffer(new float[bufferSize]);
    mapBuffer(buffer());
  }

  /** Return the size of our buffer.  
      @return the number of elements in our buffer of floats. */
  public int elementCount() {
    return buffer().length;
  }

  /** Map the buffer into the C heap as a global, and call the private
      method setNativeArrayIsCopy with the appropriate argument. */
  native int mapBuffer(float buffer[]);

  /** Unmap the buffer from the C heap. */
  native void unmapBuffer(float buffer[], int bufferPointer);

  /** Force a copy from the native C heap array to buffer. */
  private native void copyBuffer(float buffer[], int bufferPointer);

  /** Invoke unmapBuffer to release our float buffer.  
      @exception java.lang.Throwable thrown by our super class
      <code>finalize()</code> implementation. */
  public void finalize() throws Throwable {
    unmapBuffer(buffer(), bufferPointer());
    setBuffer(null);
    setBufferPointer(0);
    super.finalize();
  }

  /** Return the ith element in the floating point buffer. 
      @param i the buffer element to return.
      @return the ith element of our floating pointer buffer. */
  public float elementAt(int i) {
    /* If our array is copy, bring it into sync by calling copyBuffer.
     This could be made much faster by only copying the region of the
     buffer that we need. */
    if (nativeArrayIsCopy()) {
      copyBuffer(buffer(), bufferPointer());
    }
    return buffer[i];
  }
}

