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

/** Render an OBJ with a GeometryViewer. */
public class ObjRender implements GeometryObject, GLConstants, GLUConstants {
  /** The OBJ we are going to render. */
  OBJ obj;

  /** Construct a rendering object.
   * @param nObj the obj to render. 
   */
  public ObjRender(OBJ nObj) {
    obj = nObj;
  }

  /** Generate a display list for our obj.
   * @return the display list identifier. 
   */
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

  /** Our display list identifier. */
  private int objectNumber;

  /** Setup our initial state by creating our display list. */
  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    objectNumber = render(gl, glu);
  }

  /** Render our obj file by calling our display list.  We enable
   * lighting so that the materials will have something to work
   * with.
   
   * @param viewer the geometry viewer doing the rendering.
   * @param gl the OpenGL object to render with.
   * @param glu the GLU object to render with.
   */
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
