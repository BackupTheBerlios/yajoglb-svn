/*
 * GLNativeArray
 *
 * $Id: GLNativeArray.java,v 1.2 1999/04/29 01:16:58 razeh Exp $
 *
 * Copyright 1999
 *
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/**
 * GLNativeArray is an abstract base class for the other package classes
 * that map native arrays to Java arrays.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.3
 */

abstract public class GLNativeArray {
  /** This is true if the native version of our buffer is only a copy,
      in which case we have to take special measures when accessing
      it. */
  private boolean nativeArrayIsCopy = false;
  
  /** Records whether the native array is a copy (a supplied value of
      true) or a direct map of our own array (a supplied value of
      false).
      @param isCopy what nativeArrayIsCopy will be set to. */
  void setNativeArrayIsCopy(boolean isCopy) {
    nativeArrayIsCopy = isCopy;
  }

  /** @return Returns true if our native array is only a copy. */
  public boolean nativeArrayIsCopy() {
    return nativeArrayIsCopy;
  }
  
  /* Returns the native buffer pointer. 
     @return the native buffer pointer. */
  int bufferPointer() {
    return bufferPointer;
  }

  /* Sets the native buffer pointer.
     @param newBufferPointer the new native buffer pointer. */
  void setBufferPointer(int newBufferPointer) {
    bufferPointer = newBufferPointer;
  }

  /** Where buffer[] lives on the C heap. */
  private int bufferPointer;

  /** Return the size of our buffer. */
  abstract public int elementCount();

}

