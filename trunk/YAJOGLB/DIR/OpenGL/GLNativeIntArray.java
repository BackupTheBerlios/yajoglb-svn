/*
 * GLNativeIntArray
 *
 * $Id: GLNativeIntArray.java,v 1.2 1999/04/29 01:16:58 razeh Exp $
 *
 * Copyright 1999
 *
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/**
 * A GLNativeIntArray is used to map integer Java arrays to native int
 * arrays.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.3
 */

public class GLNativeIntArray extends GLNativeArray {
  /** Make sure that we load in our native library. */
  static {
    NativePackageLoader.loadNativeLibrary();
  }

  /** Where our integer buffer lives. */
  private int buffer[];

  /** Returns the buffer pointer.
      @return the buffer pointer. */
  int[] buffer() {
    return buffer;
  }
  
  /** Sets our new buffer. 
      @param newBuffer the new buffer array. */
  private void setBuffer(int[] newBuffer) {
    buffer = newBuffer;
  }
  
  public GLNativeIntArray(int bufferSize) {
    setBuffer(new int[bufferSize]);
    mapBuffer(buffer());
  }

  /* Return the size of our buffer.
     @return the number of integers in our buffer. */
  public int elementCount() {
    return buffer().length;
  }

  /** Map the buffer into the C heap as a global, and call the private
      method setNativeArrayIsCopy with the appropriate argument. */
  native int mapBuffer(int buffer[]);

  /** Unmap the buffer from the C heap. */
  native void unmapBuffer(int buffer[], int bufferPointer);

  /** Force a copy from the native C heap array to buffer. */
  private native void copyBuffer(int buffer[], int bufferPointer);

  /** Invoke unmapBuffer to release our buffer. 
      @exception java.lang.Throwable thrown by our super class
      <code>finalize()</code> implementation. */ 
    public void finalize() throws Throwable {
      unmapBuffer(buffer(), bufferPointer());
      setBuffer(null);
      setBufferPointer(0);
      super.finalize();
    }

  /** Return the ith element in the integer buffer.
      @param i the buffer element to return.
      @return the ith element of our integer buffer. */
  public int elementAt(int i) {
    /* If our array is copy, bring it into sync by calling copyBuffer.
     This could be made much faster by only copying the region of the
     buffer that we need. */
    if (nativeArrayIsCopy()) {
      copyBuffer(buffer(), bufferPointer());
    }
    return buffer[i];
  }
}
