/*
  Interface to the NURBS objects.
 
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
 * GLUNurbs
 *
 * $Id$
 *
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
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.4
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
  final long obtainCHeapItem(Hashtable optionalArguments) {
    return newNurbsRenderer();
  }

  /** Get a new Nurbs Renderer. */
  private native long newNurbsRenderer();

  /** Release a Nurbs Renderer. */
  private native void deleteNurbsRenderer(long nobj);

  /** Overridden to call <code>gluDeleteNurbsRenderer</code>.  */
  /* Declare the method final to prevent users from shooting
     themselves in the foot by not actually freeing our NUBRS
     renderer. */
  final void freeCHeapItem(long heapItem) {
    deleteNurbsRenderer(heapItem);
  }

  private native void loadSamplingMatrices(long GLUNurbs,
					   float modelMatrix[],
					   float projMatrix[],
					   int viewport[]);
  public void loadSamplingMatrices(float modelMatrix[],
				   float projMatrix[],
				   int viewport[]) {
    setActiveCallbackObject();
    try {
      loadSamplingMatrices(getHeapPointer(), modelMatrix, projMatrix,
			   viewport);
    } finally {
      unsetActiveCallbackObject();
    }
  }
			    
       
  private native void nurbsProperty(long nobj, int property,
				    float value);
  public void nurbsProperty(int property,
			    float value) {
    setActiveCallbackObject();
    try {
      nurbsProperty(getHeapPointer(), property, value);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  public native void getNurbsProperty(long nobj, int property, 
				      float value[]);
  public void getNurbsProperty(int property,
			       float value[]) {
    setActiveCallbackObject();
    try {
      getNurbsProperty(getHeapPointer(), property, value);
    } finally {
      unsetActiveCallbackObject();
    }
  }


  private native void beginCurve(long nobj);
  public void beginCurve() {
    setActiveCallbackObject();
    try {
      beginCurve(getHeapPointer());
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void endCurve(long nobj);
  public void endCurve() {
    setActiveCallbackObject();
    try {
      endCurve(getHeapPointer());
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void nurbsCurve(long nobj,
				 float knot[], int stride, 
				 float ctlarray[], int order,
				 int type);

  public void nurbsCurve(float knot[], int stride, 
			 float ctlarray[], int order,
			 int type) {
    setActiveCallbackObject();
    try {
      nurbsCurve(getHeapPointer(), knot, stride, ctlarray, order, type);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void beginSurface(long nobj);
  public void beginSurface() {
    setActiveCallbackObject();
    try {
      beginSurface(getHeapPointer());
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void endSurface(long nobj);
  public void endSurface() {
    setActiveCallbackObject();
    try {
      endSurface(getHeapPointer());
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void nurbsSurface(long nobj,
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
      nurbsSurface(getHeapPointer(),
		   sknot, tknot, s_stride, t_stride, ctlarray, 
		   sorder, torder, type);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void beginTrim(long nobj);
  public void beginTrim() {
    setActiveCallbackObject();
    try {
      beginTrim(getHeapPointer());
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void endTrim(long nobj);
  public void endTrim() {
    setActiveCallbackObject();
    try {
      endTrim(getHeapPointer());
    } finally {
      unsetActiveCallbackObject();
    }

  }

  private native void pwlCurve(long nobj, float array[],
			       int stride, int type );
  public void pwlCurve(float array[],
		       int stride, int type ) {
    setActiveCallbackObject();
    try {
      pwlCurve(getHeapPointer(), array, stride, type);
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

 
