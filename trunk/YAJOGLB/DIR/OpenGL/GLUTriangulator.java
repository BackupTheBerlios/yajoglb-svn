/*
 * GLUTriangulator
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */


package OpenGL;
import OpenGL.CHeapItem;
/**
 * GLUTriangulator
 *
 * This is a Java standin for the GLU triangulator object. 
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 */

public class GLUTriangulator extends CHeapItem {
  
  /** We override this method to return the result of calling
      gluNewTriangulator(). */
  protected int obtainCHeapItem() {
    return gluNewTess();
  }

  /** Get a new triangulator. */
  public native int gluNewTess();

  /** Release a triangulator. */
  public native void gluDeleteTess(int tobj);  

  /** We override this to call gluDeleteTriangulator. */
  protected void freeCHeapItem(int heapItem) {
    gluDeleteTess(heapItem);
  }

  
}
 
