/*
 * Tess.java
 *
 * $Id: TessVertex.java,v 1.2 1999/01/04 02:00:06 razeh Exp $
 * Taken from the C source inside the redbook examples in glut-3.6.
 * Robert Allan Zeh (razeh@balr.com)
 */

import OpenGL.*;
import java.awt.*;

/**
 * tess.c 
 * <P>
 * This program demonstrates polygon tessellation.  It
 * draws * part of a Dinosaur from Mark Kilgard's reflection tips.
 * This demo is really, really slow because it makes a lot of manual
 * calls to the garbage collect to make sure that the bindingarbage collection properly.
 */

public class TessVertex extends GLUTesselator implements GeometryObject, GLConstants {
  float[] dinoBodyMaterial =  { 0.0f, 0.5f, 0.5f, 0.5f };
  GL gl;
  boolean edgeFlagCalled;

  public void begin(int type, Object polygonData) {
    gl.begin(type);
  }

  public void end(Object polygonData) {
    gl.end();
  }

  public void vertex(Object vertexData, Object polygonData) {
    double[] vertex = (double[]) vertexData;
    // Invoke the garbage collector to make sure the binding keeps things
    // around.  This makes things really, really slow.
    // java.lang.Runtime.getRuntime().gc();
    gl.vertex(vertex[0], vertex[1], vertex[2]);
  }

  public void edgeFlag(boolean flag, Object polygonData) {
    edgeFlagCalled = true;
  }

  public Object combine(double x, double y, double z, 
			Object vertex0Data, Object vertex1Data, Object vertex2Data, Object vertex3Data, 
			float weight0, float weight1, float weight2, float weight3,
			Object polygonData) {
    /* We return an array of three doubles for our combination. */
    double returnVertex[] = new double[3];
    returnVertex[0] = x;
    returnVertex[1] = y;
    returnVertex[2] = z;

    return returnVertex;
  }


  public void error(int errorNumber, Object polygonData) {
    System.out.println("errorNumber = " + errorNumber);
  }


  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    this.gl = gl;
  }


  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    /* These vertices from Mark Kilgard's reflection tips. */
    double body[][] = { {0, 3, 0}, {1, 1, 0}, {5, 1, 0}, {8, 4 ,0}, {10, 4 ,0}, {11, 5 ,0},
  {11, 11.5 ,0}, {13, 12 ,0}, {13, 13 ,0}, {10, 13.5 ,0}, {13, 14 ,0}, {13, 15 ,0}, {11, 16 ,0},
  {8, 16 ,0}, {7, 15 ,0}, {7, 13 ,0}, {8, 12 ,0}, {7, 11 ,0}, {6, 6 ,0}, {4, 3 ,0}, {3, 2 ,0},
  {1, 2 ,0} };
    double arm[][] =  { {8, 10, 0}, {9, 9, 0}, {10, 9, 0}, {13, 8, 0}, {14, 9, 0}, {16, 9, 0},
  {15, 9.5, 0}, {16, 10, 0}, {15, 10, 0}, {15.5, 11, 0}, {14.5, 10, 0}, {14, 11, 0}, {14, 10, 0},
  {13, 9, 0}, {11, 11, 0}, {9, 11, 0}, {9, 11, 0} };

    this.gl = gl;	 

    gl.enable(LIGHT0);
    gl.enable(LIGHTING);
    gl.material(FRONT_AND_BACK, AMBIENT_AND_DIFFUSE, dinoBodyMaterial);

    // See what happens with the edge flag enabled.
    edgeFlagCalled = false;
    enableEdgeFlag();
    beginPolygon(null);
    beginContour();
    for(int i = 0; i < body.length; i++) {
      contourVertex(body[i], body[i]);
      // Make sure that the binding is able to keep things around.
      body[i] = null;
    }
    // Invoke the garbage collector to make sure the binding keeps things
    // around.
    java.lang.Runtime.getRuntime().gc();
    endContour();
    endPolygon();
    disableEdgeFlag();
    if (!edgeFlagCalled) {
      System.out.println("Edge flag wasn't called!");
    }
    
    // See what happens without the edge flag.
    beginPolygon(null);
    beginContour();
    for(int i = 0; i < arm.length; i++) {
      contourVertex(arm[i], arm[i]);
    }
    // Invoke the garbage collector to make sure the binding keeps things
    // around.
    java.lang.Runtime.getRuntime().gc();
    endContour();
    endPolygon();

  }

  public static void main(String args[]) {
    TessVertex     tess1   = new TessVertex();
    GeometryViewer viewer1 = new GeometryViewer();
    GeometryViewer viewer2 = new GeometryViewer();
    ExitableFrame  frame1  = new ExitableFrame();
    Frame          frame2  = new Frame();

    java.lang.Runtime.getRuntime().traceMethodCalls(true);
    java.lang.Runtime.getRuntime().traceInstructions(true);
    viewer1.addElement(tess1);
    viewer1.addElement(new Axis());
    frame1.setLayout(new GridLayout(1,1));
    frame1.add(viewer1);
    frame1.setTitle("A tesselated polygon - Thread 1");
    frame1.pack();
    frame1.setSize(new Dimension(400,400));
    frame1.setBackground(java.awt.Color.black);
    frame1.setVisible(true);

    viewer2.addElement(tess1);
    viewer2.addElement(new Axis());
    frame2.setLayout(new GridLayout(1,1));
    frame2.add(viewer2);
    frame2.setTitle("A tesselated polygon - Thread 2");
    frame2.pack();
    frame2.setLocation(frame1.getSize().width + 
		       frame1.getLocationOnScreen().x,
		       frame1.getLocationOnScreen().y);
    frame2.setSize(new Dimension(400,400));
    frame2.setBackground(java.awt.Color.black);
    frame2.setVisible(true);

    while(true) {
      try {
	Thread.sleep(100);
      } catch (InterruptedException e) {
	;
      }
      
      viewer1.paint();
      viewer2.paint();
    }
  }
}


