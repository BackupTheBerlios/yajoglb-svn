/*
 * GLUQuadric
 *
 * $Id: GLUQuadric.java,v 1.2 1998/09/10 00:57:01 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */
package OpenGL;

import java.util.Hashtable;

/**
 * This is the Java standin for the GLU quadric object. 
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1
 */

public class GLUQuadric extends CHeapItem {
  
  /** Override to return the result of calling
      gluNewQudric(). */
  protected int obtainCHeapItem(Hashtable optionalArguments) {
    return gluNewQuadric();
  }

  /** Get a new quadric object. */
  private native int gluNewQuadric();

  /** Remove the quadric we are a standin for. */
  private native void gluDeleteQuadric(int quadric);

  /** Overriden to call gluDeleteQuadric(). */
  protected void freeCHeapItem(int heapItem) {
    gluDeleteQuadric(heapItem);
  }

  private native void gluQuadricDrawStyle(int GLUQuadric,
					  int drawStyle);

  public void gluQuadricDrawStyle(int drawStyle) {
    gluQuadricDrawStyle(heapPointer(), drawStyle);
  }

  private native void gluQuadricOrientation(int GLUQuadric,
					   int orientation);
  public void gluQuadricOrientation(int orientation) {
    gluQuadricOrientation(heapPointer(), orientation);
  }

  private native void gluQuadricNormals(int GLUQuadric, int normals);
  public void gluQuadricNormals(int normals) {
    gluQuadricNormals(heapPointer(), normals);
  }

  private native void gluQuadricTexture(int quadObject,
				       boolean textureCoords);
  public void gluQuadricTexture(boolean textureCoords) {
    gluQuadricTexture(heapPointer(), textureCoords);
  }

  /*public native void gluQuadricCallback(GLUQuadric qobj,
					int which, void (*fn)());*/

  public native void gluCylinder(int GLUQuadric,
				 double baseRadius,
				 double topRadius,
				 double height,
				 int slices, int stacks);
  public void gluCylinder(double baseRadius,
			  double topRadius,
			  double height,
			  int slices, int stacks) {
    gluCylinder(heapPointer(),
		baseRadius, topRadius, height, slices, stacks);
  }

  public native void gluSphere(int GLUQuadric,
			       double radius, int slices, int stacks);
  public void gluSphere(double radius, int slices, int stacks) {
    gluSphere(heapPointer(), radius, slices, stacks);
  }
  

  private native void gluDisk(int GLUQuadric,
			      double innerRadius, double outerRadius,
			      int slices, int loops);


  public void gluDisk(double innerRadius, double outerRadius,
		      int slices, int loops) {
    gluDisk(heapPointer(), innerRadius, outerRadius, 
	    slices, loops);
  }


  private native void gluPartialDisk(int GLUQuadric, double innerRadius,
				    double outerRadius, int slices, int loops,
				    double startAngle, double sweepAngle);

  public void gluPartialDisk(double innerRadius, double outerRadius,
			     int slices, int loops,
			     double startAngle, double sweepAngle) {
    gluPartialDisk(heapPointer(), innerRadius, outerRadius,
		   slices, loops, startAngle, sweepAngle);
  }
    

}
