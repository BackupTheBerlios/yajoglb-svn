/* 
 *
 * CHeapItem
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */


package OpenGL;

/**
 * CHeapItem (pun intended)
 *
 * This is a Java class that contains a reference to a pointer in the
 * C memory heap.  We keep track of the pointer with an integer, and
 * expect to have a method that allocates the item (and returns it as
 * an int) and another method that frees the item.  We call the
 * allocation method in our own init method and call the free method
 * in our finalizer. 
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1
 *
*/
public class CHeapItem {
  /** This is the integer representation of our pointer. */
  private int cHeapPointer;

  public int heapPointer() {
    return cHeapPointer;
  }

  public CHeapItem() {
    cHeapPointer = obtainCHeapItem();
    if (cHeapPointer == 0) {
      throw new OutOfMemoryError();
    }
  }

  /** This is the method subclasses should use to implement obtaining
      an item from the C heap.  They should return 0 if they are
      unable to obtain the item. */
  protected int obtainCHeapItem() {
    return 0;
  }

  /** This is the method subclasses should use to implement freeing
      the item from the C heap.  It will be called from without our
      finalize method. */
  protected void freeCHeapItem(int heapItem) {
    ;
  }

  /** We call our freeCheapItem method here to release our underlying
    C Heap Item. */
  public void finalize() throws Throwable {
    if (cHeapPointer != 0) 
      freeCHeapItem(cHeapPointer);
    super.finalize();
  }
}
