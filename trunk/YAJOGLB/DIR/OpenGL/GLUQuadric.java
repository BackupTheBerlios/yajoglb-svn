/*
 * GLUQuadric
 *
 * $Id: GLUQuadric.java,v 1.3 1999/01/27 00:00:11 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */
package OpenGL;

import java.util.Hashtable;

/**
 * This is the Java stand-in for the GLU Quadric object, with an extra
 * twist.  The extra twist is that instead of supplying an error
 * callback you extend the class and override the <code>error</code>
 * method.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1 
 */

public class GLUQuadric extends CallbackObject {
  
  static private Hashtable activeQuadrics = new Hashtable();
  /** This returns a hash table that is used to store the current
      quadric for each thread, so that our native methods can
      determine the current quadric in the error callback. */
  static protected Hashtable getActiveCallbackDictionary() {
    return activeQuadrics;
  }
  
  /** Override to return the result of calling
      <code>NewQudric</code>. */
  final int obtainCHeapItem(Hashtable optionalArguments) {
    return newQuadric();
  }

  /** Get a new quadric object. */
  private native int newQuadric();

  /** Remove the quadric we are a stand-in for. */
  private native void deleteQuadric(int quadric);

  /** Overridden to call gluDeleteQuadric(). */
  final void freeCHeapItem(int heapItem) {
    deleteQuadric(heapItem);
  }

  private native void quadricDrawStyle(int GLUQuadric,
				       int drawStyle);

  public void quadricDrawStyle(int drawStyle) {
    setActiveCallbackObject();
    try {
      quadricDrawStyle(heapPointer(), drawStyle);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void quadricOrientation(int GLUQuadric,
					 int orientation);
  public void quadricOrientation(int orientation) {
    setActiveCallbackObject();
    try {
      quadricOrientation(heapPointer(), orientation);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void quadricNormals(int GLUQuadric, int normals);
  public void quadricNormals(int normals) {
    setActiveCallbackObject();
    try {
      quadricNormals(heapPointer(), normals);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void quadricTexture(int quadObject,
				     boolean textureCoords);
  public void quadricTexture(boolean textureCoords) {
    setActiveCallbackObject();
    try {
      quadricTexture(heapPointer(), textureCoords);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  public native void cylinder(int GLUQuadric,
			      double baseRadius,
			      double topRadius,
			      double height,
			      int slices, int stacks);
  public void cylinder(double baseRadius,
		       double topRadius,
		       double height,
		       int slices, int stacks) {
    setActiveCallbackObject();
    try {
      cylinder(heapPointer(),
	       baseRadius, topRadius, height, slices, stacks);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  public native void sphere(int GLUQuadric,
			    double radius, int slices, int stacks);
  public void sphere(double radius, int slices, int stacks) {
    setActiveCallbackObject();
    try {
      sphere(heapPointer(), radius, slices, stacks);
    } finally {
      unsetActiveCallbackObject();
    }
  }
  

  private native void disk(int GLUQuadric,
			   double innerRadius, double outerRadius,
			   int slices, int loops);


  public void disk(double innerRadius, double outerRadius,
		   int slices, int loops) {
    setActiveCallbackObject();
    try {
      disk(heapPointer(), innerRadius, outerRadius, 
	   slices, loops);
    } finally {
      unsetActiveCallbackObject();
    }
  }


  private native void partialDisk(int GLUQuadric, double innerRadius,
				  double outerRadius, int slices, int loops,
				  double startAngle, double sweepAngle);

  public void partialDisk(double innerRadius, double outerRadius,
			  int slices, int loops,
			  double startAngle, double sweepAngle) {
    setActiveCallbackObject();
    try {
      partialDisk(heapPointer(), innerRadius, outerRadius,
		  slices, loops, startAngle, sweepAngle);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  /** This method should be overridden in place of the GLU_QUADRIC_ERROR callback. */
  public void error(int errorNumber) {
    ;
  }
}

