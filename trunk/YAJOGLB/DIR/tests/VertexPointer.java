/*
 * VertexPointerTest class
 *
 * $Id: VertexPointer.java,v 1.3 1999/05/02 23:32:02 razeh Exp $
 * 
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

import java.awt.*;
import java.awt.event.*;
import OpenGL.*;


public class VertexPointer implements GeometryObject, GLConstants {

  GLVertexPointer testVertex;
  
  public  VertexPointer() {
    testVertex = new GLVertexPointer();

    float vertexPoints[] = 
    {
      0.5F, 0.5F, 0.5F, -0.5F, 0.5F, 0.5F,
      -0.5F,-0.5F, 0.5F,  0.5F,-0.5F, 0.5F,
      
      -0.5F,-0.5F,-0.5F, -0.5F, 0.5F,-0.5F,
      0.5F, 0.5F,-0.5F,  0.5F,-0.5F,-0.5F,
      
      0.5F, 0.5F, 0.5F,  0.5F, 0.5F,-0.5F,
      -0.5F, 0.5F,-0.5F, -0.5F, 0.5F, 0.5F,
      
      -0.5F,-0.5F,-0.5F,  0.5F,-0.5F,-0.5F,
      0.5F,-0.5F, 0.5F, -0.5F,-0.5F, 0.5F,
      
      0.5F, 0.5F, 0.5F,  0.5F,-0.5F, 0.5F,
      0.5F,-0.5F,-0.5F,  0.5F, 0.5F,-0.5F,
      
      -0.5F,-0.5F,-0.5F, -0.5F,-0.5F, 0.5F,
      -0.5F, 0.5F, 0.5F, -0.5F, 0.5F,-0.5F,
    };

    testVertex.setVertexPointer(vertexPoints);
    testVertex.setVertexPointerSize(3);
    
    float normalPoints[] = 
    { 
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
     -1.f, 0.0f, 0.0f 
     -1.f, 0.0f, 0.0f 
     -1.f, 0.0f, 0.0f 
     -1.f, 0.0f, 0.0f 
    };
    testVertex.setNormalPointer(normalPoints); 
    
    float colorPoints[] = {
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.5f, 0.0f,
      1.0f, 0.5f, 0.0f,
      1.0f, 0.5f, 0.0f,
      1.0f, 0.5f, 0.0f,
      1.0f, 1.0f, 0.5f,
      1.0f, 1.0f, 0.5f,
      1.0f, 1.0f, 0.5f,
      1.0f, 1.0f, 0.5f,
      0.8f, 1.0f, 0.0f,
      0.8f, 1.0f, 0.0f,
      0.8f, 1.0f, 0.0f,
      0.8f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.5f,
      0.0f, 1.0f, 0.5f,
      0.0f, 1.0f, 0.5f,
      0.0f, 1.0f, 0.5f,
      0.5f, 1.0f, 0.1f, 
      0.5f, 1.0f, 0.1f, 
      0.5f, 1.0f, 0.1f, 
      0.5f, 1.0f, 0.1f 
    };
    testVertex.setColorPointer(colorPoints);
  }
  
  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    gl.pushMatrix();
    gl.rotate(45.0f, 1.0f, 1.0f, 1.0f);
    testVertex.draw(QUADS, 0, 24);
    gl.popMatrix();
  }

  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    ;
  }

  public static void main (String args[]) {
    VertexPointer  vertexPointer    = new VertexPointer();
    GeometryViewer viewer           = new GeometryViewer();
    ExitableFrame  frame            = new ExitableFrame();
    Panel          centerPanel      = new Panel();

    viewer.addElement(vertexPointer);
    viewer.addElement(new Axis());
    viewer.setBackground(java.awt.Color.black);

    centerPanel.add(viewer);
    centerPanel.setLayout(new GridLayout(1,1));
    frame.setLayout(new BorderLayout());
    frame.add(centerPanel);

    frame.setBackground(java.awt.Color.black);
    frame.setTitle("Vertex Pointer Test");
    frame.pack();
    frame.setVisible(true);
    frame.setSize(new Dimension(400,400));
  }
} 
