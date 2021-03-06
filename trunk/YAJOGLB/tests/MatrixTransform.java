/*
 * MatrixTransform.java
 *
 * $Id$
 *
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 *
 *
 */

import OpenGL.*;

/** This draws another object after performing a matrix transformation
 * supplied at creation time.  You can use it to move or rotate
 * objects before drawing them.
 */
public class MatrixTransform implements GeometryObject {
  GeometryObject o;
  double m[];

  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    o.glInit(viewer, gl, glu);
  }

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    gl.pushMatrix();
    gl.multMatrix(m);
    o.paint(viewer, gl, glu);
    gl.popMatrix();
  }
  /** Construct a matrix transform.
   * @param ma the matrix transformation to apply.
   * @param ob the object that gets drawn.
   */
  public MatrixTransform(double ma[], GeometryObject ob) {
    m = ma;
    o = ob;
  }
}
