/*
 * A set of axis
 *
 * $Id$
 * 
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */


import OpenGL.*;
import java.util.Date;

/** This draws a simple set of axis with boxes extending out along each
  axis.  The boxes are drawn within a display list. */
public class TurningAxis implements GeometryObject, GLConstants, GLUConstants {
  /** How far out each axis extends. */
  double axisRange = 100.0;
  /** The first time we painted things. */
  Date firstDrawingDate = null;
  /** How many milliseconds a complete turn should take. */
  double turnTime = 10000.0;

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    gl.enable(LINE_SMOOTH);
    
    gl.color(0.0, 1.0, 0.0);
    gl.begin(LINES);
    gl.vertex(-axisRange, 0.0, 0.0); gl.vertex(axisRange, 0.0, 0.0);
    gl.vertex(0.0, -axisRange, 0.0); gl.vertex(0.0, axisRange, 0.0);
    gl.vertex(0.0, 0.0, -axisRange); gl.vertex(0.0, 0.0, axisRange);
    gl.end();

    {
      Date currentDate = new Date();
      double rotationAmount = 0.0;

      if (null != firstDrawingDate) {
	double timeDelta = currentDate.getTime() - firstDrawingDate.getTime();
	rotationAmount = (timeDelta / turnTime) * 360.0;
	rotationAmount = rotationAmount % 360.0;

      } else {
	firstDrawingDate = currentDate;
      }
      gl.pushMatrix();
      gl.rotate(rotationAmount, 1.0, 0.0, 0.0);
      drawAxisBoxes(gl);
      gl.popMatrix();
    }
  }

  /** Our display list reference. */
  private int axisBoxNumber;
  private void drawAxisBoxes(GL gl) {
    gl.callList(axisBoxNumber);
  }

  private int makeAxisBoxes(GL gl, float boxSize) {
    int boxListNumber = gl.genLists(1);
    gl.newList(boxListNumber, COMPILE);
    drawAxisBoxesOnAxis(gl, boxSize, 0);
    drawAxisBoxesOnAxis(gl, boxSize, 1);
    drawAxisBoxesOnAxis(gl, boxSize, 2);
    gl.endList();
    return boxListNumber;
  }

  private void drawAxisBoxesOnAxis(GL gl, float boxSize, int axisNumber) {

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
	//solidCube(gl, boxSize);
	GLUTShapes.solidTorus(gl, .75*boxSize, boxSize, 10, 10);
      gl.translate(xIncrement, yIncrement, zIncrement);
    }
    
    gl.popMatrix();
  }

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

  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    axisBoxNumber = makeAxisBoxes(gl, 0.1f);
  }

}
