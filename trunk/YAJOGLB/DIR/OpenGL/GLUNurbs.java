/*
 * GLUNurbs
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/**
 * GLUNurbs
 *
 * This is a Java standin for the GLU nurbs object. 
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 */

public class GLUNurbs extends CHeapItem {

  /** We override this method to return the result of calling
    gluNewNurbsRenderer(). */
  protected int obtainCHeapItem() {
    return gluNewNurbsRenderer();
  }

  /** Get a new Nurbs Renderer. */
  public native int gluNewNurbsRenderer();

  /** Release a Nurbs Renderer. */
  public native void gluDeleteNurbsRenderer(int nobj);

  /** We override this to call gluDeleteNurbsRenderer(). */
  protected void freeCHeapItem(int heapItem) {
    gluDeleteNurbsRenderer(heapItem);
  }
}
 
