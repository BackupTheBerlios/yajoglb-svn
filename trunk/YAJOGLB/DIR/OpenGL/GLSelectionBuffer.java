/*
 * GLSelectionBuffer
 *
 * $Id: GLSelectionBuffer.java,v 1.1 1999/01/27 00:00:11 razeh Exp $
 *
 * Copyright 1999
 *
 * Robert Allan Zeh (razeh@balr.com)
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
 * @version 0.1
 */

public class GLSelectionBuffer extends GLNativeIntArray
{
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
