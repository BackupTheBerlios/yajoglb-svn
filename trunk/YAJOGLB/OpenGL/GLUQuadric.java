/*
  An interface to the quadric section of the GLU library.
 
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
 * GLUQuadric
 *
 * $Id$
 *
 */
package OpenGL;

import java.util.Hashtable;

/**
 * This is the Java stand-in for the GLU Quadric object, with an extra
 * twist.  The extra twist is that instead of supplying an error
 * callback you extend the class and override the <code>error</code>
 * method.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.4
 */

public class GLUQuadric extends CallbackObject {

  /** Make sure that we load in our native library. */
  static {
    NativePackageLoader.loadNativeLibrary();
  }
  
  static private Hashtable activeQuadrics = new Hashtable();
  /** This returns a hash table that is used to store the current
      quadric for each thread, so that our native methods can
      determine the current quadric in the error callback. */
  static protected Hashtable getActiveCallbackDictionary() {
    return activeQuadrics;
  }
  
  /** Override to return the result of calling
      <code>NewQudric</code>. */
  final long obtainCHeapItem(Hashtable optionalArguments) {
    return newQuadric();
  }

  /** Get a new quadric object. */
  private native long newQuadric();

  /** Remove the quadric we are a stand-in for. */
  private native void deleteQuadric(long quadric);

  /** Overridden to call gluDeleteQuadric(). */
  final void freeCHeapItem(long heapItem) {
    deleteQuadric(heapItem);
  }

  private native void quadricDrawStyle(long GLUQuadric,
				       int drawStyle);

  public void quadricDrawStyle(int drawStyle) {
    setActiveCallbackObject();
    try {
      quadricDrawStyle(getHeapPointer(), drawStyle);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void quadricOrientation(long GLUQuadric,
					 int orientation);
  public void quadricOrientation(int orientation) {
    setActiveCallbackObject();
    try {
      quadricOrientation(getHeapPointer(), orientation);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void quadricNormals(long GLUQuadric, int normals);
  public void quadricNormals(int normals) {
    setActiveCallbackObject();
    try {
      quadricNormals(getHeapPointer(), normals);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  private native void quadricTexture(long quadObject,
				     boolean textureCoords);
  public void quadricTexture(boolean textureCoords) {
    setActiveCallbackObject();
    try {
      quadricTexture(getHeapPointer(), textureCoords);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  public native void cylinder(long GLUQuadric,
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
      cylinder(getHeapPointer(),
	       baseRadius, topRadius, height, slices, stacks);
    } finally {
      unsetActiveCallbackObject();
    }
  }

  public native void sphere(long GLUQuadric,
			    double radius, int slices, int stacks);
  public void sphere(double radius, int slices, int stacks) {
    setActiveCallbackObject();
    try {
      sphere(getHeapPointer(), radius, slices, stacks);
    } finally {
      unsetActiveCallbackObject();
    }
  }
  

  private native void disk(long GLUQuadric,
			   double innerRadius, double outerRadius,
			   int slices, int loops);


  public void disk(double innerRadius, double outerRadius,
		   int slices, int loops) {
    setActiveCallbackObject();
    try {
      disk(getHeapPointer(), innerRadius, outerRadius, 
	   slices, loops);
    } finally {
      unsetActiveCallbackObject();
    }
  }


  private native void partialDisk(long GLUQuadric, double innerRadius,
				  double outerRadius, int slices, int loops,
				  double startAngle, double sweepAngle);

  public void partialDisk(double innerRadius, double outerRadius,
			  int slices, int loops,
			  double startAngle, double sweepAngle) {
    setActiveCallbackObject();
    try {
      partialDisk(getHeapPointer(), innerRadius, outerRadius,
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

