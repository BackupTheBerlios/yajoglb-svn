/*
  Represents the tesselator object.
 
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
 * GLUTesselator
 *
 * $Id: GLUTesselator.java,v 1.4 2001/07/06 23:43:47 razeh Exp $
 *
 */

package OpenGL;

import java.util.Hashtable;

/**
 * This is the Java stand-in for the GLU tesselator object.  There are
 * a couple of important differences from the C API that should be
 * noted up front. 
 * <P>
 * The most important difference is that callbacks are provided by
 * extending the GLUTesselator class rather than providing functions.
 * For example, someone interesting in error handling would override
 * GLUTesselator's <code>error(int errorNumber, Object
 * polygonData)</code> method rather than supplying an error function.
 * <P>
 * Because supplying the edge call back changes a tesselator's
 * behaviour it can be toggled on or off with the
 * <code>enableEdgeFlag</code> and <code>disableEdgeFlag</code> calls.
 * Its setting can be queried with the <code>isEdgeFlagEnabled</code>
 * method.  By default the edge flag callback is disabled.
 * <P>
 * The gluTessVertex function's equivalent is the
 * <code>contourVertex</code> method.
 * <P>
 * Another difference is that the binding retains the polygon and
 * vertex data provided to the beginPolygon and contourVertex method.
 * <P>
 * Making calls to a tesselator from more than one thread is not advised,
 * although it should work.  But do not be surprised if it does not.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.4
 */

public class GLUTesselator extends CallbackObject {
  
    /** Make sure that we load in our native library. */
    static {
	NativePackageLoader.loadNativeLibrary();
    }

    /*
     * All of the native methods are synchronized to prevent multiple threads
     * from trashing the native library's internal tesselator structures.
     */
  
    /*
     * Tesselator mapping methods. 
     *
     * These methods help the native library map the native tesselators
     * to their Java counterparts.  This is something of a pain because
     * we do not have direct access to any of the JNI pointers from
     * within the tesselator callbacks.
     */

    static private Hashtable activeGLUTesselators = new Hashtable();
    /** This returns a hash table that is used to store the current
	tesselator for each thread. */
    static protected Hashtable getActiveCallbackDictionary() {
	return activeGLUTesselators;
    }

    /*
     * Native heap memory managment.
     *
     * We provide methods here to manager our C heap.
     */
  
    /** Overridden to return the result of calling
	<code>gluNewTess()</code>. 
	@return a heap pointer to a newly allocated tesselator. */
    final long obtainCHeapItem(Hashtable optionalArguments) {
	return newTess();
    }

    /** Get a new tesselator object. */
    synchronized private native long newTess();

    /** Remove the tesselator we are a stand-in for. */
    synchronized private native void deleteTess(long tess);

    /** Overridden to delete the object we are a stand-in for.  Do not
	override this method. */
    final void freeCHeapItem(long heapItem) {
	deleteTess(heapItem);
    }


    /*
     * Tesselator functions
     *
     * The tesselator methods are provided here.
     *
     */

    synchronized private native void beginContour(long GLUTess);

    /** Begin a contour.  This is the equivalent of
	<code>gluTessBeginContour</code>. */
    public void beginContour() {
	setActiveCallbackObject();
	try {
	    System.out.println("beginContour: heap pointer = " + getHeapPointer());
	    beginContour(getHeapPointer());
	} finally {
	    unsetActiveCallbackObject();
	}
    }

    synchronized private native void beginPolygon(long GLUTess, Object polygonData);

    /** Begin a polygon.  This is the equivalent of
	<code>gluTessBeginPolygon</code>, except that the binding makes
	sure that polygonData is still available when
	<code>endPolygon()</code> is called.  
      
	@param polygonData an object passed to <code>begin</code>,
	<code>end</code>, <code>vertex</code>, <code>edgeFlag</code>, or
	<code>error</code>. */
    public void beginPolygon(Object polygonData) {
	//setActiveCallbackObject();
	try {
	    System.out.println("beginPolygon: heap pointer = " + getHeapPointer());
	    beginPolygon(getHeapPointer(), polygonData);
	} finally {
	    //unsetActiveCallbackObject();
	}
    }

    synchronized private native void endContour(long GLUTess);

    /** End a contour.  This is the equivalent of
	<code>gluTessEndContour</code>. */
    public void endContour() {
	setActiveCallbackObject();
	try {
	    endContour(getHeapPointer());
	} finally {
	    unsetActiveCallbackObject();
	}
    }

    synchronized private native void endPolygon(long GLUTess);

    /** Begin a polygon.  This is the equivalent of
	<code>gluTessEndPolygon</code>. */
    public void endPolygon() {
	//setActiveCallbackObject();
	try {
	    endPolygon(getHeapPointer());
	} finally {
	    //unsetActiveCallbackObject();
	}
    }

    synchronized private native void normal(long GLUTess, double valueX, double valueY,
					    double valueZ);
    /** Specify the normal for the current polygon.  This is the
	equivalent of <code>gluTessNormal</code>. */
    public void normal(double valueX, double valueY, double valueZ) {
	setActiveCallbackObject();
	try {
	    normal(getHeapPointer(), valueX, valueY, valueZ);
	} finally {
	    unsetActiveCallbackObject();
	}
    }

    synchronized private native void contourVertex(long GLUTess, 
						   double location[],
						   Object vertexData);

    /** Specify a vertex of the current contour.  This is the equivalent
	of <code>gluTessVertex</code>, except that the binding makes sure that
	vertexData is still around by the time <code>endPolygon</code> is called.
	The extra contour was added to the name to distinguish it from
	the vertex callback method.
	@param location the location of the vertex as an array of three doubles.
	@param vertexData an object passed to <code>vertex</code>.
    */
    public void contourVertex(double location[], Object vertexData) {
	if (3 == location.length) {
	    setActiveCallbackObject();
	    try {
		contourVertex(getHeapPointer(), location, vertexData);
	    } finally {
		unsetActiveCallbackObject();
	    }
	} else {
	    throw new IllegalArgumentException("Expected a double array of length 3.");
	}
    }

    synchronized private native void setProperty(long GLUTess, 
						 int which, 
						 double data);

    /** Sets the supplied tesselator property.  This is the equivalent
	of <code>gluTessSetProperty</code>.
	@param which the tesselator property to set
	@param data the value to set the tesselator property to.  */
    public void setProperty(int which, double data) {
	setActiveCallbackObject();
	try {
	    setProperty(getHeapPointer(), which, data);
	} finally {
	    unsetActiveCallbackObject();
	}
    }

    synchronized private native double property(long GLUTess, int which);

    /** Unlike the OpenGL C API's <code>gluGetTessProperty</code>, we return our
	double result rather than pass it by reference.
	@param which the tesselator property to get.
	@return the value of the tesselator property.  */
    public double property(int which) {
	double property;
	setActiveCallbackObject();
	try {
	    property = property(getHeapPointer(), which);
	} finally {
	    unsetActiveCallbackObject();
	}
	return property;
    }


    synchronized private native void enableEdgeFlag(long GLUTess);
    private boolean isEdgeFlagEnabled = false;

    /** Determines if the edge flag callback is enabled or disabled.
	@return true if the <code>edgeFlag</code> will be invoked by the
	tesselator. */
    public boolean isEdgeFlagEnabled() {
	return isEdgeFlagEnabled;
    }

    /** Enable the edge flag callback.  If the edge flag callback is not
	enabled the <code>edgeFlag</code> method will never be invoked by the
	tesselator. */
    public void enableEdgeFlag() {
	enableEdgeFlag(getHeapPointer());
	isEdgeFlagEnabled = true;
    }

    synchronized private native void disableEdgeFlag(long GLUTess);
    /** Disable the edge flag callback.  This will prevent the
	<code>edgeFlag</code> method from ever being invoked by the
	tesselator. */
    public void disableEdgeFlag() {
	disableEdgeFlag(getHeapPointer());
	isEdgeFlagEnabled = false;
    }




    /* 
     * Callback methods
     *
     * Instead of supplying callback methods like the C API does,
     * the user should override the methods below.
     *
     */

    /** This method is used in place of the GLU_TESS_BEGIN callback.*/
    public void begin(int type, Object polygonData) {
    }

    /** This method should be overridden to take the place of the
	GLU_TESS_EDGE_FLAG callback. */
    public void edgeFlag(boolean flag, Object polygonData) {
    }
  
    /** This method should be overridden to take the place of the
	GLU_TESS_VERTEX callback. */
    public void vertex(Object vertexData, Object polygonData) {
    }

    /** This method should be overridden to take the place of the
	GLU_TESS_END calllback. */
    public void end(Object polygonData) {
    }

    /** This method should be overridden in place of the GLU_TESS_COMBINE
	callback.  The out data is returned rather than passed in as an
	argument.  Instead of providing the weights, coordinates, and
	vertex data as arrays (as in the C API) we present them as
	instances. */
    public Object combine(double x, double y, double z, 
			  Object vertex0Data, Object vertex1Data, 
			  Object vertex2Data, Object vertex3Data, 
			  float weight0, float weight1, float weight2, float weight3,
			  Object polygonData) {
	return null;
    }

    /** This method should be overridden in place of the GLU_TESS_ERROR
	callback. */
    public void error(int errorNumber, Object polygonData) {
    }
}
  

