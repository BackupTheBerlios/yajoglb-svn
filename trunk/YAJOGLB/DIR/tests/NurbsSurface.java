/*
 * NurbsSurface class
 *
 * $Id: NurbsSurface.java,v 1.2 1998/03/29 23:28:29 razeh Exp $
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

public class NurbsSurface extends OpenGLWidget {
  GLU glu = new GLU();
  GL  gl  = new GL();

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

    gl.clearColor (0.0f, 0.0f, 0.0f, 0.0f);
    gl.material(FRONT, DIFFUSE, mat_diffuse);
    gl.material(FRONT, SPECULAR, mat_specular);
    gl.material(FRONT, SHININESS, mat_shininess);

    gl.enable(LIGHTING);
    gl.enable(LIGHT0);
    gl.enable(DEPTH_TEST);
    gl.enable(AUTO_NORMAL);
    gl.enable(NORMALIZE);

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
    

    gl.clear(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT);

    gl.pushMatrix();
    gl.rotate(330.0f, 1.f,0.f,0.f);
    gl.scale(0.5f, 0.5f, 0.5f);
    
    theNurb.gluBeginSurface();
    theNurb.gluNurbsSurface(knots, knots,
			    4 * 3, 3, flatControlPoints, 
			    4, 4, MAP2_VERTEX_3);
    theNurb.gluEndSurface();
    
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
    gl.flush();
    swapBuffers();
  }

  public void componentResized(ComponentEvent e) {
    super.componentResized(e);

    gl.viewport(0, 0, getSize().width, getSize().height);
    gl.matrixMode(PROJECTION);
    gl.loadIdentity();
    
    glu.gluPerspective (45.0f, (float)getSize().width/(float)getSize().height, 
			3.0f, 8.0f);
    gl.matrixMode(MODELVIEW);
    gl.loadIdentity();
    gl.translate (0.0f, 0.0f, -5.0f);
  }
}
