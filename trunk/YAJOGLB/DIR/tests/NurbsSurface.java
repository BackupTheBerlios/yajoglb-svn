/*
 * NurbsSurface class
 *
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@balr.com)
 *
 * Converted into Java from the SGI example.
 *
 */

import OpenGL.*;
import java.awt.event.*;

/**  This program draws a NURBS surface in the shape of a 
 *  symmetrical hill.  
 */

class NurbsSurface extends OpenGLWidget {
  GLU glu = new GLU();

  public NurbsSurface() throws OpenGLWidgetOpenFailedException {
    addMouseListener(this);
    addMouseMotionListener(this);
  }
  
  public static void main (String args[]) {
    try {
      NurbsSurface demo = new NurbsSurface();
      demo.run();
    } catch (java.lang.Throwable e) {
      System.err.println("Opps! " + e);
    }
  }



  private boolean showPoints;
  private float controlPoints[][][];

  private void initSurface() {
    int u,v;

    controlPoints = new float[4][4][3];

    for (u = 0; u < 4; u++) {
      for (v = 0; v < 4; v++) {
	controlPoints[u][v][0] =  2.0f*((float)u - 1.5f);
         controlPoints[u][v][1] =  2.0f*((float)v - 1.5f);

         if ( (u == 1 || u == 2) && (v == 1 || v == 2))
            controlPoints[u][v][2] = 3.0f;
         else
            controlPoints[u][v][2] = -3.0f;
      }
    }			
  }				

  GLUNurbs theNurb;

  public void glInit() {
    super.glInit();
    
    float mat_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    float mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float mat_shininess[] = { 100.0f };

    clearColor (0.0f, 0.0f, 0.0f, 0.0f);
    material(FRONT, DIFFUSE, mat_diffuse);
    material(FRONT, SPECULAR, mat_specular);
    material(FRONT, SHININESS, mat_shininess);

    enable(LIGHTING);
    enable(LIGHT0);
    enable(DEPTH_TEST);
    enable(AUTO_NORMAL);
    enable(NORMALIZE);

    initSurface();

    theNurb = new GLUNurbs();

    theNurb.gluNurbsProperty(GLU_SAMPLING_TOLERANCE, 25.0f);
    theNurb.gluNurbsProperty(GLU_DISPLAY_MODE, GLU_FILL);
  }

  public void paint() {
    float knots[] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    float flatControlPoints[];
    int i, j, k, flatCounter = 0;

    flatControlPoints = new float[4*4*3];
    for(i = 0; i < 4; i++)
      for(j = 0; j < 4; j++) 
	for(k = 0; k < 3; k++)
	  flatControlPoints[flatCounter++] = controlPoints[i][j][k];
    

    clear(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT);

    pushMatrix();
    rotate(330.0f, 1.f,0.f,0.f);
    scale(0.5f, 0.5f, 0.5f);
    
    theNurb.gluBeginSurface();
    theNurb.gluNurbsSurface(knots, knots,
			    4 * 3, 3, flatControlPoints, 
			    4, 4, MAP2_VERTEX_3);
    theNurb.gluEndSurface();
    
    if (showPoints == true) {
      pointSize(5.0f);
      disable(LIGHTING);
      color(1.0f, 1.0f, 0.0f);
      begin(POINTS);
      for (i = 0; i < 4; i++) {
	for (j = 0; j < 4; j++) {
	  vertex(controlPoints[i][j][0], 
		 controlPoints[i][j][1], controlPoints[i][j][2]);
	}
      }
      end();
      enable(LIGHTING);
    }
    popMatrix();
    flush();
    swapBuffers();
  }

  public void componentResized(ComponentEvent e) {
    super.componentResized(e);

    viewport(0, 0, getSize().width, getSize().height);
    matrixMode(PROJECTION);
    loadIdentity();
    
    glu.gluPerspective (45.0f, (float)getSize().width/(float)getSize().height, 
			3.0f, 8.0f);
    matrixMode(MODELVIEW);
    loadIdentity();
    translate (0.0f, 0.0f, -5.0f);
  }
}
