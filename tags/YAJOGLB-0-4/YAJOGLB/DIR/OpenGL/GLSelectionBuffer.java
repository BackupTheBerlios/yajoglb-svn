/*
 * GLSelectionBuffer
 *
 * $Id: GLSelectionBuffer.java,v 1.3 2002/07/21 16:55:38 razeh Exp $
 *
 * Copyright 1999
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 */

package OpenGL;

/**
 * A GLSelectionBuffer is used to hold the integer buffer used for the
 * OpenGL selection buffer.
 *
 * It's possible that the native array allocated will be a copy, in
 * which case we have to take extra steps to make sure that the Java
 * array matches the native array when we look at it.  The private
 * boolean nativeArrayIsCopy handles that.  However, this has not been
 * tested.
 *
 * @author Robert Allan Zeh
 *
 * @version 0.3
 */

public class GLSelectionBuffer extends GLNativeIntArray
{
  /** Make sure that we load in our native library. */
  static {
    NativePackageLoader.loadNativeLibrary();
  }

  /** Create a selection buffer for use by the
      <code>selectBuffer</code> method.
      @param bufferSize the size of the selection buffer to create. */
  public GLSelectionBuffer(int bufferSize) {
    super(bufferSize);
  }

  private native void selectBuffer(int size, int bufferPointer);

  /** Use this buffer object as the buffer for selection mode. */
  public void selectBuffer() {
    setBufferPointer(mapBuffer(buffer()));
    selectBuffer(buffer().length, bufferPointer());
  }
}
