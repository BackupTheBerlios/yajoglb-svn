/*
 * VertexPointerTest class
 *
 * $Id: VertexPointer.java,v 1.1 1998/10/12 16:17:44 razeh Exp $
 * 
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

import java.awt.*;
import java.awt.event.*;
import OpenGL.*;


public class VertexPointer implements GeometryObject, OpenGLConstants {

  OpenGLVertexPointer testVertex;
  
  public  VertexPointer() {
    testVertex = new OpenGLVertexPointer();

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
    

    viewer.addElement(vertexPointer);
    viewer.addElement(new Axis());

    frame.setLayout(new GridLayout(1,1));
    frame.add(viewer);
    frame.setTitle("Vertex Pointer Test");
    frame.pack();
    frame.setVisible(true);
    frame.setSize(new Dimension(400,400));
  }
} 
