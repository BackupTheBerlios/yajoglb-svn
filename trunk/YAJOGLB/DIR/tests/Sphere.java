/*
 * Sphere
 *
 * $Id: Sphere.java,v 1.6 2002/04/06 15:12:57 razeh Exp $
 *
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 *
 *
 */

import OpenGL.*;

/** Draws a very simple sphere using the GLU library. */
public class Sphere implements GeometryObject, GLConstants, GLUConstants {

  float[] sphereMaterial   = { 1.0f, 0.0f, 0.0f, 0.5f };
  double sphereRadius = .75;

  /** This sets the radius of the sphere we will draw. */
  public void setSphereRadius(float newRadius) {
    sphereRadius = newRadius;
  }

  /** This returns the radius of the sphere we will draw. */
  public double getSphereRadius() {
    return sphereRadius;
  }
  
  GLUQuadric sphere;
  
  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    sphere = new GLUQuadric();
    sphere.quadricDrawStyle(GLU_FILL);
    sphere.quadricNormals(GLU_SMOOTH);
  }

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {  
    gl.pushMatrix();
    gl.translate(-2.0, 0.0, 0.0);
    gl.material(FRONT_AND_BACK, AMBIENT_AND_DIFFUSE, sphereMaterial);
    sphere.sphere(sphereRadius, 15, 10);
    gl.popMatrix();
  }
}
