/* 
 *
 * CHeapItem
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/**
 * CHeapItem (pun intended) <P>
 *
 * This abstract class maintains a reference to a pointer in the C
 * memory heap.  We keep track of the pointer with an integer, and
 * expect to have a method that allocates the item (<a
 * href="#obtainCHeapItem">obtainCHeapItem</a>) and another method
 * that frees the item (<a href="#freeCHeapItem">freeCHeapItem</a>).
 * We call the allocation method in our base construcor and call the
 * free method in our finalizer.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1
 *
 */

public class CHeapItem {
  /** This is the integer representation of our pointer. */
  private int cHeapPointer;

  /** This returns the integer representation of our pointer.  
    
    @exception IllegalAccessException If our pointer has not
    been set yet*/
  public int heapPointer() throws IllegalAccessException {
    if (cHeapPointer == 0) {
      /* Uh-oh.  Our heap pointer was never set, which is bad. */
      throw new IllegalStateException("Asking for an unset heap pointer.");
    }
    return cHeapPointer;
  }

  /** Class constructor.  The C heap item is allocated immediately. */
  public CHeapItem() {
    setCHeapItem();
  }

  /** Class constructor with the option of delaying the C heap allocation.  
   *
   * @param avoidSetCheapItem if true, delay the C heap item's allocation until setCHeapItem is invoked
   */

  public CHeapItem(boolean avoidSetCHeapItem) {
    if (avoidSetCHeapItem == false)
      setCHeapItem();
  }

  /** This is used to set our C heap item based on our call to
   obtainCHeapItem.  If called more than once it will throw an
   IllegalStateException. */
  private void setCHeapItem() {
    if (cHeapPointer != 0) {
      throw new IllegalStateException("Unable to call setCHeapItem twice.");
    }
    cHeapPointer = obtainCHeapItem();
    if (0 == cHeapPointer) {
      throw new OutOfMemoryError();
    }
  }
  
  /** This is the method subclasses should use to implement obtaining
      an item from the C heap.  They should return 0 if they are
      unable to obtain the item. */
  private int obtainCHeapItem() {
    return 0;
  }

  /** This is the method subclasses should use to implement freeing
      the item from the C heap.  It will be called from our finalize
      method. 
      
      @param heapItem the C heap item to free.

      */
  private void freeCHeapItem(int heapItem) {
    ;
  }

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
