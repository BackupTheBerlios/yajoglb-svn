/*
 * Plain cube
 *
 * $Id$
 * 
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import OpenGL.*;
import java.awt.*;

/** This draws a simple lighted cube, rotated 30 degrees from each
    axis, with normal pointers. */
public class PlainCube implements GeometryObject, GLConstants {
  float[] material = { 0.0f, 0.5f, 0.5f, 0.5f };

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    gl.pushMatrix();
    gl.rotate(30.0f, 1.0f, 1.0f, 1.0f);
    gl.material(FRONT_AND_BACK, AMBIENT_AND_DIFFUSE, material);
    gl.begin(QUADS);
    gl.normal( 0.0F, 0.0F, 1.0F);
    gl.vertex( 0.5F, 0.5F, 0.5F); gl.vertex(-0.5F, 0.5F, 0.5F);
    gl.vertex(-0.5F,-0.5F, 0.5F); gl.vertex( 0.5F,-0.5F, 0.5F);
    
    gl.normal( 0.0F, 0.0F,-1.0F);
    gl.vertex(-0.5F,-0.5F,-0.5F); gl.vertex(-0.5F, 0.5F,-0.5F);
    gl.vertex( 0.5F, 0.5F,-0.5F); gl.vertex( 0.5F,-0.5F,-0.5F);
    
    gl.normal( 0.0F, 1.0F, 0.0F);
    gl.vertex( 0.5F, 0.5F, 0.5F); gl.vertex( 0.5F, 0.5F,-0.5F);
    gl.vertex(-0.5F, 0.5F,-0.5F); gl.vertex(-0.5F, 0.5F, 0.5F);
    
    gl.normal( 0.0F,-1.0F, 0.0F);
    gl.vertex(-0.5F,-0.5F,-0.5F); gl.vertex( 0.5F,-0.5F,-0.5F);
    gl.vertex( 0.5F,-0.5F, 0.5F); gl.vertex(-0.5F,-0.5F, 0.5F);
    
    gl.normal( 1.0F, 0.0F, 0.0F);
    gl.vertex( 0.5F, 0.5F, 0.5F); gl.vertex( 0.5F,-0.5F, 0.5F);
    gl.vertex( 0.5F,-0.5F,-0.5F); gl.vertex( 0.5F, 0.5F,-0.5F);
    
    gl.normal(-1.0F, 0.0F, 0.0F);
    gl.vertex(-0.5F,-0.5F,-0.5F); gl.vertex(-0.5F,-0.5F, 0.5F);
    gl.vertex(-0.5F, 0.5F, 0.5F); gl.vertex(-0.5F, 0.5F,-0.5F);
    gl.end();
    gl.popMatrix();
  }

  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    gl.enable(LIGHT0);
    gl.enable(LIGHTING);
  }
  
  public static void main(String args[]) {
    PlainCube      cube   = new PlainCube();
    GeometryViewer viewer = new GeometryViewer();
    ExitableFrame  frame  = new ExitableFrame();

    viewer.addElement(cube);
    viewer.addElement(new Axis());
    frame.setLayout(new GridLayout(1,1));
    frame.add(viewer);
    frame.setTitle("A plain cube");
    frame.pack();
    frame.setSize(new Dimension(400,400));
    frame.setBackground(java.awt.Color.black);
    frame.setVisible(true);
  }
}

