/*
 * NurbsSurface class
 *
 * $Id: NurbsSurface.java,v 1.11 2002/04/06 15:12:33 razeh Exp $
 *
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 *
 * Converted into Java from the SGI example.
 *
 */

import OpenGL.*;
import java.awt.event.*;
import java.awt.*;

/**  This program draws a NURBS surface in the shape of a 
 *  symmetrical hill. Taken from the SGI examples. 
 */

public class NurbsSurface extends Object implements GeometryObject, GLConstants, GLUConstants {

  GLUNurbs surface = null;

  public static void main (String args[]) {
    NurbsSurface   surface  = new NurbsSurface();
    GeometryViewer viewer   = new GeometryViewer();
    ExitableFrame  frame    = new ExitableFrame();

    viewer.addElement(surface);
    frame.setLayout(new GridLayout(1,1));
    frame.add(viewer);
    frame.setTitle("A Nurbs Surface");
    frame.pack();
    frame.setBackground(java.awt.Color.black);
    frame.setSize(new Dimension(400,400));
    frame.setVisible(true);
  }

  private boolean showPoints;
  private float controlPoints[][][];

  private void initSurface() {
    int u,v;

    controlPoints = new float[4][4][3];

    for (u = 0; u < 4; u++) {
      for (v = 0; v < 4; v++) {
	controlPoints[u][v][0] = 2.0f * ((float)u - 1.5f);
         controlPoints[u][v][1] = 2.0f * ((float)v - 1.5f);

         if ((u == 1 || u == 2) && (v == 1 || v == 2))
            controlPoints[u][v][2] = 3.0f;
         else
            controlPoints[u][v][2] = -3.0f;
      }
    }			
  }				

  protected GLUNurbs getNewSurface() {
    return new GLUNurbs();
  }

  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    surface = getNewSurface();

    float mat_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    float mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float mat_shininess[] = { 100.0f };

    gl.material(FRONT, DIFFUSE, mat_diffuse);
    gl.material(FRONT, SPECULAR, mat_specular);
    gl.material(FRONT, SHININESS, mat_shininess);

    gl.enable(LIGHTING);
    gl.enable(LIGHT0);
    gl.enable(DEPTH_TEST);
    gl.enable(AUTO_NORMAL);
    gl.enable(NORMALIZE);

    initSurface();

    surface.nurbsProperty(GLU_SAMPLING_TOLERANCE, 25.0f);
    surface.nurbsProperty(GLU_DISPLAY_MODE, GLU_FILL);
  }

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    float knots[] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    float flatControlPoints[];
    int i, j, k, flatCounter = 0;

    flatControlPoints = new float[4*4*3];
    for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++) 
	for(k = 0; k < 3; k++)
	  flatControlPoints[flatCounter++] = controlPoints[i][j][k];
    

    gl.pushMatrix();
    gl.rotate(330.0f, 1.f,0.f,0.f);
    gl.scale(0.5f, 0.5f, -0.5f);
    
    surface.beginSurface();
    surface.nurbsSurface(knots, knots,
		 4 * 3, 3, flatControlPoints, 
		 4, 4, MAP2_VERTEX_3);
    surface.endSurface();
    
    if (showPoints == true) {
      gl.pointSize(5.0f);
      gl.disable(LIGHTING);
      gl.color(1.0f, 1.0f, 0.0f);
      gl.begin(POINTS);
      for (i = 0; i < 4; i++) {
	for (j = 0; j < 4; j++) {
	  gl.vertex(controlPoints[i][j][0], 
		    controlPoints[i][j][1], controlPoints[i][j][2]);
	}
      }
      gl.end();
      gl.enable(LIGHTING);
    }
    gl.popMatrix();
  }
}

