/*
 * QuadricError.java
 *
 * $Id$
 * 
 * Makes sure that the quadric error method gets called.
 */

import OpenGL.*;
import java.awt.*;

/** Call a quadric to verify that the error method can get called.
 */
public class QuadricError 
  extends GLUQuadric 
  implements GeometryObject, GLConstants, GLUConstants {

  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    /* This should be a bad draw style. */
    quadricDrawStyle(-1);
  }

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    sphere(10, 15, 10);

  }

  public void error(int errorCode) {
    System.out.println("Quadric error: " + errorCode);
  }

  public static void main(String args[]) {
     GeometryViewer viewer = new GeometryViewer();
     QuadricError   error  = new QuadricError();
     ExitableFrame  frame  = new ExitableFrame();

     viewer.addElement(error);
     frame.setLayout(new GridLayout(1,1));
     frame.add(viewer);
     frame.setTitle("Quadric error test");
     frame.pack();
     frame.setSize(new Dimension(400,400));
     frame.setBackground(java.awt.Color.black);
     frame.setVisible(true);
  }
}
