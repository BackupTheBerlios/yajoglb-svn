/*
 * Concurrence
 *
 * $Id: Concurrence.java,v 1.6 2002/09/07 17:22:06 razeh Exp $
 *
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import java.awt.*;
import OpenGL.*;


/** This tests the OpenGL package's ability to render in multiple
    canvases concurrently. */

public class Concurrence {

  public static void main(String args[]) {
    Sphere         sphere1 = new Sphere();
    Sphere         sphere2 = new Sphere();
    PlainCube      cube    = new PlainCube();
    GeometryViewer viewer1 = new GeometryViewer();
    GeometryViewer viewer2 = new GeometryViewer();
    ExitableFrame  frame1  = new ExitableFrame();
    Frame          frame2  = new Frame();

    /* We use this transformation matrix to move the
     * spheres off to the side. */
    double translation[] = {  1.0, 0.0, 0.0, 0.0, 
			      0.0, 1.0, 0.0, 0.0,
			      0.0, 0.0, 1.0, 0.0,
			      -2.0, 0.0, 0.0, 1.0 };

    viewer1.addElement(cube);
    viewer1.addElement(new TurningAxis());
    viewer1.addElement(new MatrixTransform(translation, sphere1));
    frame1.setLayout(new GridLayout(1,1));
    frame1.add(viewer1);
    frame1.setTitle("Thread #1");
    frame1.pack();
    frame1.setSize(new Dimension(400,400));

    frame1.setBackground(java.awt.Color.black);
    frame1.setVisible(true);

    viewer2.addElement(cube);
    viewer2.addElement(new TurningAxis());
    viewer2.addElement(new MatrixTransform(translation, sphere2));
    frame2.setLayout(new GridLayout(1,1));
    frame2.add(viewer2);
    frame2.setTitle("Thread #2");
    frame2.pack();
    frame2.setLocation(frame1.getSize().width + 
		       frame1.getLocationOnScreen().x,
		       frame1.getLocationOnScreen().y);
    frame2.setSize(new Dimension(400,400));
    frame2.setBackground(java.awt.Color.black);
    frame2.setVisible(true);

    int sphereCycle = 0;
    while(true) {
      sphereCycle++;
      double sphereRadius 
	= 2.5 * Math.abs(Math.sin((double) sphereCycle / (50.0 * Math.PI)));
      sphere1.setSphereRadius((float) sphereRadius);
      sphere2.setSphereRadius((float) sphereRadius);
      viewer1.nativePaint();
      viewer2.nativePaint();
    }
  }
}
