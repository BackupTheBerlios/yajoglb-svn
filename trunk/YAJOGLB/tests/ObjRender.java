/*
 * Object file render class
 *
 * $Id$
 *
 * Copyright 2001
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import java.util.*;
import OpenGL.*;
import java.io.*;
import java.awt.*;

public class ObjRender implements GeometryObject, GLConstants, GLUConstants {
  OBJ obj;

  public ObjRender(OBJ nObj) {
    obj = nObj;
  }

  protected int render(GL gl, GLU glu) {
    int listNumber = gl.genLists(1);
    gl.newList(listNumber, COMPILE);

    Iterator drawables = obj.getDrawables();
    while (drawables.hasNext()) {
      ObjDrawable drawable = (ObjDrawable) drawables.next();
      drawable.paint(gl, glu);
    }
    gl.endList();
    return listNumber;
  }

  private int objectNumber;
  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    objectNumber = render(gl, glu);
  }

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    gl.pushMatrix();

    gl.enable(LIGHT0);
    gl.enable(LIGHT1);
    gl.enable(LIGHTING);
    gl.enable(NORMALIZE);
    gl.callList(objectNumber);
    gl.color(.5, .5, .5);

    gl.popMatrix();
  }

  public static void main(String args[]) {
    ObjRender      render = null;
    GeometryViewer viewer = new GeometryViewer();
    ExitableFrame  frame  = new ExitableFrame();
    
    try {
      ObjReader obj = new ObjReader(args[0]);
      render = new ObjRender(obj.readFile());
      obj.readFile();

      viewer.addElement(render);
      viewer.addElement(new Axis());
      frame.setLayout(new GridLayout(1,1));
      frame.add(viewer);
      frame.setTitle("Image");
      frame.pack();
      frame.setSize(new Dimension(400,400));
      frame.setBackground(java.awt.Color.black);
      frame.setVisible(true);
    } catch (FileNotFoundException ex) {
      System.err.println(ex);
      ex.printStackTrace();
    } catch (IOException ex) {
      System.err.println(ex);
      ex.printStackTrace();
    }
  }
}
