/*
 * Sphere
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
import java.awt.*;

/** Draws a very simple sphere using the GLU library. */
public class Sphere implements GeometryObject, GLConstants, GLUConstants {

  float[] sphereMaterial   = { 1.0f, 0.0f, 0.0f, 0.5f };
  double sphereRadius = .75;
  int slices = 15;
  int stacks = 10;

  /** This sets the radius of the sphere we will draw. */
  public void setSphereRadius(float newRadius) {
    sphereRadius = newRadius;
  }

  /** This returns the radius of the sphere we will draw. */
  public double getSphereRadius() {
    return sphereRadius;
  }
  
  /** Returns the number of slices used to draw the sphere. */
  protected int getSlices() { return slices; }
  /** Returns the number of stacks used to draw the sphere. */
  protected int getStacks() { return stacks; }
  void setSlices(int s) { slices = s; }
  void setStacks(int s) { stacks = s; }

  public void texture(boolean textureCoords) {
    sphere.quadricTexture(textureCoords);
  }

  GLUQuadric sphere;
  
  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    sphere = new GLUQuadric();
    sphere.quadricDrawStyle(GLU_FILL);
    sphere.quadricNormals(GLU_SMOOTH);
  }

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {  
    gl.pushMatrix();
    //gl.translate(-2.0, 0.0, 0.0);
    gl.material(FRONT_AND_BACK, AMBIENT_AND_DIFFUSE, sphereMaterial);
    sphere.sphere(sphereRadius, getSlices(), getStacks());
    gl.popMatrix();
  }

  public static void main(String args[]) {
    Sphere         sphere = new Sphere();
    GeometryViewer viewer = new GeometryViewer();
    ExitableFrame  frame  = new ExitableFrame();

    viewer.addElement(sphere);
    viewer.addElement(new Axis());
    frame.setLayout(new GridLayout(1,1));
    frame.add(viewer);
    frame.setTitle("A plain sphere");
    frame.pack();
    frame.setSize(new Dimension(400,400));
    frame.setBackground(java.awt.Color.black);
    frame.setVisible(true);
  }
}
