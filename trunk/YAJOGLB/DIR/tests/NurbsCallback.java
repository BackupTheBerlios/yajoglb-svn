/*
 * NurbsCallback class
 *
 * $Id: NurbsCallback.java,v 1.3 1999/05/02 23:50:00 razeh Exp $
 *
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@balr.com)
 *
 * Used to test callbacks within NURBS.
 *
 */

import java.awt.*;
import OpenGL.GLUNurbs;

public class NurbsCallback extends NurbsSurface
{

  public void begin(int type) {
    System.out.println("begin(" + type + ")");
  }

  public void vertex(float x, float y, float z) {
    System.out.println("vertex(" + x + "," + y + "," + z + ")");
  }

  public void normal(float x, float y, float z) {
    System.out.println("normal(" + x + "," + y + "," + z + ")");
  }

  public void color(float red, float green, float blue, float alpha) {
    System.out.println("color(" + red + "," + green + "," + blue + "," + alpha + ")");
  }

  public void texCoord(float texCoord[]) {
    System.out.println("texCoord(" + texCoord + ")");
  }

  public void end() {
    System.out.println("end()");
  }

  public static void main (String args[]) {
    GeometryViewer viewer   = new GeometryViewer();
    NurbsCallback  surface  = new NurbsCallback();
    ExitableFrame  frame    = new ExitableFrame();

    surface.surface.nurbsProperty(GLU_NURBS_MODE, GLU_NURBS_TESSELLATOR);
    viewer.addElement(surface);
    frame.setLayout(new GridLayout(1,1));
    frame.add(viewer);
    frame.setTitle("A Nurbs Surface");
    frame.pack();
    frame.setVisible(true);
    frame.setBackground(java.awt.Color.black);
    frame.setSize(new Dimension(400,400));
  }

}
