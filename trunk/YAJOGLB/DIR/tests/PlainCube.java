/*
 * Plain cube
 *
 * $Id: PlainCube.java,v 1.3 1998/11/01 02:24:27 razeh Exp $
 * 
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

import OpenGL.*;
import java.awt.*;

/** This draws a simple lighted cube, rotate 30 degress from each
    axis, with normal pointers. */

public class PlainCube implements GeometryObject, GLConstants {
  float[] material = { 0.0f, 0.5f, 0.5f, 0.5f };

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    gl.enable(LIGHT0);
    gl.enable(LIGHTING);
    gl.pushMatrix();
    gl.rotate(30.0f, 1.0ff);
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

