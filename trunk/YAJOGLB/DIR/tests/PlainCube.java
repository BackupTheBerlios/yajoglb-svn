/*
 * Plain cube
 *
 * $Id: PlainCube.java,v 1.2 1998/03/30 02:22:21 razeh Exp $
 * 
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

import OpenGL.*;
import java.awt.*;

/** This draws a simple cube with normal pointers. */

public class PlainCube implements GeometryObject, OpenGLConstants {
  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    gl.color(0.0, 1.0, 0.0);
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
  }

  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    gl.enable(LIGHTING);
    gl.enable(LIGHT0);
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

