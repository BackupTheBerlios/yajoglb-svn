/*
 * GLUTesselator
 *
 * $Id: GLUTesselator.java,v 1.1 1998/09/10 00:57:11 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/**
 * This is the Java standin for the GLU tesselator object.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1
 */

import java.util.Hashtable;

public class GLUTesselator extends CHeapItem {

  /** Override to return the result of calling gluNewTess(). */
  protected int obtainCHeapItem(Hashtable optionalArguments) {
    return gluNewTess();
  }

  /** Get a new tesselator object. */
  private native int gluNewTess();

  /** Remove the tesselator we are a standin for. */
  private native void gluDeleteTess(int tess);

  /** Overriden to delete the object we are a standin for. */
  protected void freeCHeapItem(int heapItem) {
    gluDeleteTess(heapItem);
  }

  private native void gluTessBeginContour(int GLUtess);

  public void gluTessBeginContour() {
    gluTessBeginContour(heapPointer());
  }

  private native void gluTessBeginPolygon(int GLUTess,Object data);

  public void gluTessBeginPolygon(Object data) {
    gluTessBeginPolygon(heapPointer(), data);
  }

  /* If we ever figure out how to implement the callbacks properly,
   * this is the stub for it.
   *
   * gluTessCallBack(int GLUTess, int which, CallBackFunc()) 
   */


  private native void gluTessEndContour(int GLUTess);

  public void gluTessEndContour() {
    gluTessEndContour(heapPointer());
  }

  private native void gluTessEndPolygon(int GLUTess);

  public void gluTessEndPolygon() {
    gluTessEndPolygon(heapPointer());
  }

  private native void gluTessNormal(int GLUTess, double valueX, double valueY,
				    double valueZ);

  public void gluTessNormal(double valueX, double valueY, double valueZ) {
    gluTessNormal(heapPointer(), valueX, valueY, valueZ);
  }

  private native void gluTessVertex(int GLUTess, double location[],
				    Object data);

  public void gluTessVertex(double location[], Object data) {
    gluTessVertex(heapPointer(), location, data);
  }

  private native void gluTessProperty(int GLUTess, int which, double data);

  public void gluTessProperty(int which, double data) {
    gluTessProperty(heapPointer(), which, data);
  }

  /** Unlike the OpenGL gluGetTessProperty, we return our double
      result rather than pass it by reference.  */
  private native double gluGetTessProperty(int GLUTess, int which);
  
  /** Unlike the OpenGL gluGetTessProperty, we return our double
      result rather than pass it by reference.  */
  public double gluGetTessProperty(int which) {
    return gluGetTessProperty(heapPointer(), which);
  }
}
  

