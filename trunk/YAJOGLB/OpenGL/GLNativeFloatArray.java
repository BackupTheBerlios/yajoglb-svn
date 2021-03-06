/*
  Support for native float arrays.

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
 * GLNativeFloatArray
 *
 * $Id$
 *
 * Copyright 1999
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 */

package OpenGL;

/**
 * A GLNativeFloatArray is used to map floating point Java arrays to
 * native float arrays.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.3 
 */

public class GLNativeFloatArray extends GLNativeArray {
  /** Make sure that we load in our native library. */
  static {
    NativePackageLoader.loadNativeLibrary();
  }

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

