/*
 * GLUNurbs
 *
 * $Id: GLUNurbs.java,v 1.6 1999/05/02 23:24:32 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

import java.util.Hashtable;

/**
 * This is the Java stand-in for the GLU nurbs object.  The C API for
 * OpenGL provides a set of functions that all take in a preallocated
 * NURBS structure.  Our binding provides a <code>GLUNurbs</code>
 * object, and all of the functions are provided as instance methods.
 * The mapping between C functions and instance methods is fairly
 * straightforward.  For example, the C function
 * <code>gluGetNurbsProperty(GLUnurbsObj, property, float*)</code> is
 * replaced with the instance method <code>getNurbsProperty(property,
 * float[])</code>. <P>
 *
 * It is important to create GLUNurbs objects while an OpenGLContext is
 * active, especially while using native threads under Linux with Mesa. 
 * 
 * 
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.3
 */

public class GLUNurbs extends CallbackObject {

  /** Make sure that we load in our native library. */
  static {
    NativePackageLoader.loadNativeLibrary();
  }

  
  /*
   * These methods provide the native library with a hash table to map
   * the active NURBS objects.
   */

  static private Hashtable activeNurbs = new Hashtable();
  /** This returns a hash table that is used to store the current
      NURBS for each thread. */
  static protected Hashtable getActiveCallbackDictionary() {
    return activeNurbs;
  }


  /** Overridden to return the result of calling
      <code>gluNewNurbsRenderer</code>.  */
  /* Declare the method final to prevent users from shooting
     themselves in the foot by not actually allocating a NURBS object. */
  final int obtainCHeapItem(Hashtable optionalArguments) {
    return newNurbsRenderer();
  }

  /** Get a new Nurbs Renderer. */
  private native int newNurbsRenderer();

  /** Release a Nurbs Renderer. */
  private native void deleteNurbsRenderer(int nobj);

  /** Overridden to call <code>gluDeleteNurbsRenderer</code>.  */
  /* Declare the method final to prevent users from shooting
     themselves in the foot by not actually freeing our NUBRS
     renderer. */
  final void freeCHeapItem(int heapItem) {
    deleteNurbsRenderer(heapItem);
  }

  private native void loadSamplingMatrices(int GLUNurbs,
					   float modelMatrix[],
					   float projMatrix[],
					   int viewport[]);
  public void loadSamplingMatrices(float modelMatrix[],
				   float projMatrix[],
				   int viewport[]) {
    setActiveCallbackObject();
    try {
      loadSamplingMatrices(heapPointer(), modelMatrix, projMatrix,
			   viewport);
    } finally {
      unsetActiveCallbackObject();
    }
  }
			    
       
  private native void nurbsProperty(int nobj, int property,
				    float value);
  public void nurbsProperty(int property,
			    float value) {
    setActiveCallbackObject();
    try {
      nurbsProperty(heapPointer(), property, value);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  public native void getNurbsProperty(int nobj, int property, 
				      float value[]);
  public void getNurbsProperty(int property,
			       float value[]) {
    setActiveCallbackObject();
    try {
      getNurbsProperty(heapPointer(), property, value);
    } finally {
      unsetActiveCallbackObject();
    }
  }


  private native void beginCurve(int nobj);
  public void beginCurve() {
    setActiveCallbackObject();
    try {
      beginCurve(heapPointer());
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void endCurve(int nobj);
  public void endCurve() {
    setActiveCallbackObject();
    try {
      endCurve(heapPointer());
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void nurbsCurve(int nobj,
				 float knot[], int stride, 
				 float ctlarray[], int order,
				 int type);

  public void nurbsCurve(float knot[], int stride, 
			 float ctlarray[], int order,
			 int type) {
    setActiveCallbackObject();
    try {
      nurbsCurve(heapPointer(), knot, stride, ctlarray, order, type);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void beginSurface(int nobj);
  public void beginSurface() {
    setActiveCallbackObject();
    try {
      beginSurface(heapPointer());
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void endSurface(int nobj);
  public void endSurface() {
    setActiveCallbackObject();
    try {
      endSurface(heapPointer());
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void nurbsSurface(int nobj,
				   float sknot[],
				   float tknot[],
				   int s_stride, int t_stride,
				   float ctlarray[],
				   int sorder, int torder, int type);
  public void nurbsSurface(float sknot[],
			   float tknot[],
			   int s_stride, int t_stride,
			   float ctlarray[],
			   int sorder, int torder, int type) {
    setActiveCallbackObject();
    try {
      nurbsSurface(heapPointer(),
		   sknot, tknot, s_stride, t_stride, ctlarray, 
		   sorder, torder, type);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void beginTrim(int nobj);
  public void beginTrim() {
    setActiveCallbackObject();
    try {
      beginTrim(heapPointer());
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void endTrim(int nobj);
  public void endTrim() {
    setActiveCallbackObject();
    try {
      endTrim(heapPointer());
    } finally {
      unsetActiveCallbackObject();
    }

  }

  private native void pwlCurve(int nobj, float array[],
			       int stride, int type );
  public void pwlCurve(float array[],
		       int stride, int type ) {
    setActiveCallbackObject();
    try {
      pwlCurve(heapPointer(), array, stride, type);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  /* 
   * Callback methods
   *
   * Instead of supplying callback methods like the C API does,
   * the user should override the methods below.
   *
   */

  /** This method should be overridden in place of the GLU_NURBS_ERROR
      callback. */
  public void error(int errorNumber) {
  }

  /** This method should be overridden in place of the GLU_NURBS_BEGIN
      callback. */
  public void begin(int type) {
  }

  /** This method should be overridden in place of the GLU_NURBS_VERTEX
      callback.  The C API provides an array of floats but this
      binding provides the contents of the array as three floating
      point numbers. */
  public void vertex(float x, float y, float z) {

  }

  /** This method should be overridden in place of the GLU_NURBS_NORMAL
      callback.  Instead of providing an array of floats like the C
      API this binding provides the contents of the array as three
      floating point numbers. */
  public void normal(float x, float y, float z) {

  }

  /** This method should be overridden in place of the GLU_NURBS_COLOR
      callback.  Instead of providing an array of four floats like the C
      API this binding breaks out the floats into separate parameters. */
  public void color(float red, float green, float blue, float alpha) {

  }

  /** This method should be overridden in place of the
      GLU_NURBS_TEXTURE_COORD callback. Unlike the other callback
      methods this method is given an array of floats, because the C
      API is given a variable number of floats. */
  public void texCoord(float texCoord[]) {
  }

  /** This method should be overridden in place of the GLU_NURBS_END
      callback. */
  public void end() {

  }

}

 
