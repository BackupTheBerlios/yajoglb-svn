/*
 * NurbsCallback class
 *
 * $Id: NurbsCallback.java,v 1.5 2001/06/10 19:15:06 razeh Exp $
 *
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 *
 * Used to test callbacks within NURBS.
 *
 */

import java.awt.*;
import OpenGL.*;

public class NurbsCallback extends NurbsSurface
{
  
  class NurbsSurfaceWithCallbacks extends GLUNurbs {
    public void begin(int type) {
      System.out.println("begin(" + type + ")");
    }
    
    public void vertex(float x, float y, float z) {
      Systln("vertex(" + x + "," + y + "," + z + ")");
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
  }

  protected GLUNurbs getNewSurface() {
    return new NurbsSurfaceWithCallbacks();
  }

  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    super.glInit(viewer, gl, glu);
    surface.nurbsProperty(GLU_NURBS_MODE, GLU_NURBS_TESSELLATOR);
  }

  public static void main (String args[]) {
    GeometryViewer viewer   = new GeometryViewer();
    NurbsCallback  surface  = new NurbsCallback();
    ExitableFrame  frame    = new ExitableFrame();

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
