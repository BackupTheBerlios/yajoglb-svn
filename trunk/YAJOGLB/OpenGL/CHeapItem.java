/*
  Provides references to items on the C memory heap.
 
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
 *
 * CHeapItem
 *
 * $Id$
 *
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
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.4
 *
 */

abstract class CHeapItem {
  /** This is the integer representation of our pointer. */
  private long cHeapPointer;

  /** This returns the integer representation of our pointer.  
    @return the integer representation of our pointer
    @exception IllegalStateException If our pointer has not
    been set yet*/
  /* Public is temporary #warning */
  public long getHeapPointer() throws IllegalStateException {
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
  abstract long obtainCHeapItem(Hashtable optionalArguments);

  /** This is the method subclasses should use to implement freeing
      the item from the C heap.  It will be called from our finalize
      method. 
      @param heapItem the C heap item to free.
  */
  abstract void freeCHeapItem(long heapItem);

  /** Invokes freeCheapItem to release our underlying C heap item.
    @exception Throwable Thrown by our superclass.  */
  public void finalize() throws Throwable {
    if (cHeapPointer != 0) 
      freeCHeapItem(cHeapPointer);
    super.finalize();
  }
}
