/* 
 *
 * CHeapItem
 *
 * $Id: CHeapItem.java,v 1.7 1999/04/29 01:16:58 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

import java.util.Hashtable;

/** 
 * This abstract class maintains a reference to a pointer in the C
 * memory heap.  We keep track of the pointer with an integer, and
 * expect to have a method that allocates the item
 * ( <code>obtainCHeapItem</code>) and another method that frees the
 * item (<code>freeCHeapItem</code>).  We call the allocation method
 * in our base constructor and call the free method in our finalizer.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.3
 *
 */

abstract class CHeapItem {
  /** This is the integer representation of our pointer. */
  private int cHeapPointer;

  /** This returns the integer representation of our pointer.  
    @return the integer representation of our pointer
    @exception IllegalStateException If our pointer has not
    been set yet*/
  int heapPointer() throws IllegalStateException {
    if (cHeapPointer == 0) {
      /* Uh-oh.  Our heap pointer was never set, which is bad. */
      throw new IllegalStateException("Asking for an unset heap pointer.");
    }
    return cHeapPointer;
  }

  /** Class constructor. */
  public CHeapItem() {
    setCHeapItem(null);
  }

  /** Class constructor, with optional arguments (in a
      <code>Hashtable</code>) that are passed to
      <code>setCHeapItem</code>. */
  public CHeapItem(Hashtable optionalArguments) {
    setCHeapItem(optionalArguments);
  }
  

  /** This is used to set our C heap item based on our call to
      <code>obtainCHeapItem</code>.
   @exception IllegalStateException thrown if called more than once. */
  void setCHeapItem(Hashtable optionalArguments) {
    if (cHeapPointer != 0) {
      throw new IllegalStateException("Unable to call setCHeapItem twice.");
    }
    cHeapPointer = obtainCHeapItem(optionalArguments);
    if (0 == cHeapPointer) {
      throw new OutOfMemoryError();
    }
  }
  
  /** The method subclasses should use to implement obtaining
      an item from the C heap.  They should return 0 if they are
      unable to obtain the item. 
      @return the integer representation of our C heap pointer. */
  abstract int obtainCHeapItem(Hashtable optionalArguments);

  /** This is the method subclasses should use to implement freeing
      the item from the C heap.  It will be called from our finalize
      method. 
      @param heapItem the C heap item to free.
  */
  abstract void freeCHeapItem(int heapItem);

  /** Invokes freeCheapItem to release our underlying
    C heap item. <P>
    @exception Throwable Thrown by our superclass. 
    */
  public void finalize() throws Throwable {
    if (cHeapPointer != 0) 
      freeCHeapItem(cHeapPointer);
    super.finalize();
  }
}
