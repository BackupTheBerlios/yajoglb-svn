/*
 * GLUNurbs
 *
 * $Id: GLUNurbs.java,v 1.3 1998/09/10 00:56:36 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

import java.util.Hashtable;

/**
 * This is the Java stand-in for the GLU nurbs object. 
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1
 */

public class GLUNurbs extends CHeapItem {

  /** Overriden to return the result of calling gluNewNurbsRenderer(). */
  protected int obtainCHeapItem(Hashtable optionalArguments) {
    return gluNewNurbsRenderer();
  }

  /** Get a new Nurbs Renderer. */
  private native int gluNewNurbsRenderer();

  /** Release a Nurbs Renderer. */
  private native void gluDeleteNurbsRenderer(int nobj);

  /** Overridden to call gluDeleteNurbsRenderer(). */
  protected void freeCHeapItem(int heapItem) {
    gluDeleteNurbsRenderer(heapItem);
  }

  private native void gluLoadSamplingMatrices(int GLUNurbs,
					      float modelMatrix[],
					      float projMatrix[],
					      int viewport[]);
  public void gluLoadSamplingMatrices(float modelMatrix[],
				      float projMatrix[],
				      int viewport[]) {
    gluLoadSamplingMatrices(heapPointer(), modelMatrix, projMatrix,
			    viewport);
  }
			    
       
  private native void gluNurbsProperty(int nobj, int property,
				       float value);
  public void gluNurbsProperty(int property,
			       float value) {
    gluNurbsProperty(heapPointer(), property, value);
  }

  public native void gluGetNurbsProperty(int nobj, int property, 
					 float value[]);
  public void gluGetNurbsProperty(int property,
					 float value[]) {
    gluGetNurbsProperty(heapPointer(), property, value);
  }


  private native void gluBeginCurve(int nobj);
  public void gluBeginCurve() {
    gluBeginCurve(heapPointer());
  }

  private native void gluEndCurve(int nobj);
  public void gluEndCurve() {
    gluEndCurve(heapPointer());
  }

  private native void gluNurbsCurve(int nobj,
				    float knot[], int stride, 
				    float ctlarray[], int order,
				    int type);

  public void gluNurbsCurve(float knot[], int stride, 
			    float ctlarray[], int order,
			    int type) {
    gluNurbsCurve(heapPointer(), knot, stride, ctlarray, order, type);
  }

  private native void gluBeginSurface(int nobj);
  public void gluBeginSurface() {
    gluBeginSurface(heapPointer());
  }

  private native void gluEndSurface(int nobj);
  public void gluEndSurface() {
    gluEndSurface(heapPointer());
  }

  private native void gluNurbsSurface(int nobj,
				      float sknot[],
				      float tknot[],
				      int s_stride, int t_stride,
				      float ctlarray[],
				      int sorder, int torder, int type);
  public void gluNurbsSurface(float sknot[],
			      float tknot[],
			      int s_stride, int t_stride,
			      float ctlarray[],
			      int sorder, int torder, int type) {
    gluNurbsSurface(heapPointer(),
		    sknot, tknot, s_stride, t_stride, ctlarray, 
		    sorder, torder, type);
  }

  private native void gluBeginTrim(int nobj);
  public void gluBeginTrim() {
    gluBeginTrim(heapPointer());
  }

  private native void gluEndTrim(int nobj);
  public void gluEndTrim() {
    gluEndTrim(heapPointer());
  }

  private native void gluPwlCurve(int nobj, float array[],
				 int stride, int type );
  public void gluPwlCurve(float array[],
			  int stride, int type ) {
    gluPwlCurve(heapPointer(), array, stride, type);
  }

  /*public native void gluNurbsCallback( GLUNurbs nobj, int which, void (*fn)() );*/


}
 
