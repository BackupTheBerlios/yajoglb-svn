/*
 * A set of axis
 *
 * $Id: Axis.java,v 1.1 1998/03/30 02:15:47 razeh Exp $
 * 
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */


import OpenGL.*;

/** This draws a simple set of axis. */

public class Axis implements GeometryObject, OpenGLConstants,
OpenGLUConstants {
  /** How far our the each axis extends. */
  double axisRange = 100.0;

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
      gl.disable(LIGHTING);
      gl.enable(FOG);
      gl.fog(FOG_DENSITY, 0.25f);
      
      gl.color(0.0, 1.0, 0.0);
      gl.begin(LINES);
      gl.vertex(-axisRange, 0.0, 0.0); gl.vertex(axisRange, 0.0, 0.0);
      gl.vertex(0.0, -axisRange, 0.0); gl.vertex(0.0, axisRange, 0.0);
      gl.vertex(0.0, 0.0, -axisRange); gl.vertex(0.0, 0.0, axisRange);
      gl.end();
      gl.disable(FOG);
  }

  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    ;
  }

}

    axisBoxNumber = makeAxisBoxes(