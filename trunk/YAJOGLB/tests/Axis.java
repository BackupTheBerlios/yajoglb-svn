/*
 * A set of axis
 *
 * $Id$
 *
 * Copyright 1998, 2004
 * Robert Allan Zeh (razeh@yahoo.com)
 */


import OpenGL.*;

/** This draws a simple set of markers (currently solid toruses)
  xextending out along each axis.  The boxes are drawn within a display
  list. */

public class Axis implements GeometryObject, GLConstants, GLUConstants {
  /** How far out each axis extends. */
  double axisRange = 100.0;

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    gl.enable(LINE_SMOOTH);
    
    gl.color(0.0, 1.0, 0.0);
    gl.begin(LINES);
    gl.vertex(-axisRange, 0.0, 0.0); gl.vertex(axisRange, 0.0, 0.0);
    gl.vertex(0.0, -axisRange, 0.0); gl.vertex(0.0, axisRange, 0.0);
    gl.vertex(0.0, 0.0, -axisRange); gl.vertex(0.0, 0.0, axisRange);
    gl.end();

    drawAxisMarkers(gl);
  }

  /** Our display list reference. */
  private int axisMarkerNumber;
  private void drawAxisMarkers(GL gl) {
    gl.callList(axisMarkerNumber);
  }

  /** Construct an axis box. 
   * @param gl used for drawing.
   * @param boxSize the dimensions of the box.
   */
  private int makeAxisMarkers(GL gl, float boxSize) {
    int markerListNumber = gl.genLists(1);
    gl.newList(markerListNumber, COMPILE);
    drawAxisMarkersOnAxis(gl, boxSize, 0);
    drawAxisMarkersOnAxis(gl, boxSize, 1);
    drawAxisMarkersOnAxis(gl, boxSize, 2);
    gl.endList();
    return markerListNumber;
  }

  /** Draw a seriees of boxes along a specified axis.
   * @param gl used for drawing.
   * @param boxSize how large each box should be.
   * @param axisNumber 0 for the x axis, 1 for the y axis, 2 for
   * the z axis. */
  private void drawAxisMarkersOnAxis(GL gl, float boxSize, int axisNumber) {

    double xIncrement = 0.0f, yIncrement = 0.0f, zIncrement = 0.0f;
    int boxCount = 100;

    if (0 == axisNumber) {
      xIncrement = -axisRange;
    }

    if (1 == axisNumber) {
      yIncrement = -axisRange;
    }

    if (2 == axisNumber) {
      zIncrement = -axisRange;
    }

    gl.pushMatrix();
    gl.color(0.8, 0.0, 0.0);

    gl.translate(xIncrement, yIncrement, zIncrement);

    xIncrement = 2.0 * -xIncrement / (float) boxCount;
    yIncrement = 2.0 * -yIncrement / (float) boxCount;
    zIncrement = 2.0 * -zIncrement / (float) boxCount;

    for(int i = 0; i  < boxCount; i++) {
	GLUTShapes.solidTorus(gl, .75*boxSize, boxSize, 10, 10);
      gl.translate(xIncrement, yIncrement, zIncrement);
    }
    
    gl.popMatrix();
  }

  /** Draw a solid cube.
   * @param gl what to draw with.
   * @param size how large to make the cube.
   */  
  private void solidCube(GL gl, float size) {
    gl.begin(QUADS);
    gl.normal( 0.0F, 0.0F, 1.0F);
    gl.vertex( size, size, size); gl.vertex(-size, size, size);
    gl.vertex(-size,-size, size); gl.vertex( size,-size, size);
    
    gl.normal( 0.0F, 0.0F,-1.0F);
    gl.vertex(-size,-size,-size); gl.vertex(-size, size,-size);
    gl.vertex( size, size,-size); gl.vertex( size,-size,-size);
    
    gl.normal( 0.0F, 1.0F, 0.0F);
    gl.vertex( size, size, size); gl.vertex( size, size,-size);
    gl.vertex(-size, size,-size); gl.vertex(-size, size, size);
    
    gl.normal( 0.0F,-1.0F, 0.0F);
    gl.vertex(-size,-size,-size); gl.vertex( size,-size,-size);
    gl.vertex( size,-size, size); gl.vertex(-size,-size, size);
    
    gl.normal( 1.0F, 0.0F, 0.0F);
    gl.vertex( size, size, size); gl.vertex( size,-size, size);
    gl.vertex( size,-size,-size); gl.vertex( size, size,-size);
    
    gl.normal(-1.0F, 0.0F, 0.0F);
    gl.vertex(-size,-size,-size); gl.vertex(-size,-size, size);
    gl.vertex(-size, size, size); gl.vertex(-size, size,-size);
    gl.end();
  }

  /** Setup our display list. 
   * @param viewer the geometry viewer construct us.
   * @param gl used to draw.
   * @param GLU used to draw.
   */
  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
      axisMarkerNumber = makeAxisMarkers(gl, 0.1f);
  }
}
