/*
 *
 * GLUQuadric
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */
package OpenGL;


/**
 * GLUquadric
 *
 * This is a Java standin for the GLU quadric object. 
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 */

public class GLUQuadric extends CHeapItem {
  
  /** We override this method to return the result of calling
      gluNewQudric(). */
  protected int obtainCHeapItem() {
    return gluNewQuadric();
  }

  /** Get a new quadric object. */
  private native int gluNewQuadric();

  /** Remove the quadric we are a standin for. */
  private native void gluDeleteQuadric(int quadric);

  /** We override this to call gluDeleteQuadric(). */
  protected void freeCHeapItem(int heapItem) {
    gluDeleteQuadric(heapItem);
  }
}
