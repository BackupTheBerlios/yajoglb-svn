/* 
 * Geometry viewer class
 *
 * $Id: GeometryViewer.java,v 1.1 1998/03/30 02:16:31 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

import java.math.*;
import java.util.Vector;
import java.util.Enumeration;
import java.awt.event.*;
import OpenGL.*;


/** A simple framework for drawing geometry that the user can navigate
 through. */
class GeometryViewer extends OpenGLCanvas implements MouseListener, MouseMotionListener, KeyListener, ComponentListener, OpenGLConstants, OpenGLUConstants {
  float[] eyePoint, forwardDirection, sidewaysDirection, 
        upDirection;

  /* We use these for changing the view direction with the mouse. */
  float [] startingForwardDirection, startingSidewaysDirection,
    startingUpDirection;
  int  startingX, startingY;
  boolean mouseViewAdjustmentInProgress = false;

  GLU glu = new GLU();
  GL  gl  = new GL();
  OpenGLContext context;
  Vector renderedObjects = new Vector();

  public void addElement(GeometryObject object) {
    renderedObjects.addElement(object);
  }

  /* How much we scale a single frame movement by. */
  float movementScale = .2f;

  private void setupViewingParameters() {

    /* Set the viewing position */
    eyePoint    = new float[4];
    eyePoint[0] = 0.0f;
    eyePoint[1] = 0.0f;
    eyePoint[2] = -4.0f;

    forwardDirection    = new float[4];
    forwardDirection[0] = 0.0f;
    forwardDirection[1] = 0.0f;
    forwardDirection[2] = 1.0f;
    
    sidewaysDirection    = new float[4];
    sidewaysDirection[0] = 1.0f;
    sidewaysDirection[1] = 0.0f;
    sidewaysDirection[2] = 0.0f;

    upDirection    = new float[4];
    upDirection[0] = 0.0f;
    upDirection[1] = 1.0f;
    upDirection[2] = 0.0f;

  }

  /** We extend this method to add our key event interest.  We do this
      because we want to receive KeyEvents. */
  protected void addListeners() {
    addKeyListener(this);
    addMouseListener(this);
    addMouseMotionListener(this);
    addComponentListener(this);
  }

  public GeometryViewer() {
    addListeners();
    setupViewingParameters();
  }


  synchronized public void glInit() {
    context = new OpenGLContext(this);

    aquireContext();

    gl.enable(DEPTH_TEST);

    /* position viewer */
    gl.matrixMode(MODELVIEW);
    gl.translate(0.0f, 0.0f, 0.5f);   

    /* set viewing projection */
    gl.matrixMode(PROJECTION);
    gl.frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.5f, 12.0f);

    for (Enumeration e = renderedObjects.elements() ; 
	 e.hasMoreElements() ;) {
      GeometryObject g = (GeometryObject)e.nextElement();
      g.glInit(this, gl, glu);
    }
    releaseContext();
  }

  private void orbitView(float angle) {
    float gazePoint[] = new float[3];
    float orbitScale = 7;
    float sidewaysScale = .2f;
    if (angle < 0)
      sidewaysScale = -sidewaysScale;

    gazePoint[0] = eyePoint[0] + (forwardDirection[0] * orbitScale);
    gazePoint[1] = eyePoint[1] + (forwardDirection[1] * orbitScale);
    gazePoint[2] = eyePoint[2] + (forwardDirection[2] * orbitScale);

    eyePoint[0] = eyePoint[0] + (sidewaysDirection[0] * sidewaysScale);
    eyePoint[1] = eyePoint[1] + (sidewaysDirection[1] * sidewaysScale);
    eyePoint[2] = eyePoint[2] + (sidewaysDirection[2] * sidewaysScale);

    forwardDirection[0] = (gazePoint[0] - eyePoint[0]);
    forwardDirection[1] = (gazePoint[1] - eyePoint[1]);
    forwardDirection[2] = (gazePoint[2] - eyePoint[2]);

    float forwardLength = (float)
      Math.sqrt((forwardDirection[0] * forwardDirection[0]) +
		(forwardDirection[1] * forwardDirection[1]) +
		(forwardDirection[2] * forwardDirection[2]));

    forwardDirection[0] /= forwardLength;
    forwardDirection[1] /= forwardLength;
    forwardDirection[2] /= forwardLength;


    /* The sideways vector should always be the cross product of the
       forward vector and the up vector. */
    sidewaysDirection = Vec.crossProduct(upDirection, forwardDirection);

  }

  private void rotateViewOnZ(float angle,
			     float originalSidewaysDirection[],
			     float originalUpDirection[])
  {
    sidewaysDirection = 
      MatrixModifiers.rotate_point(originalSidewaysDirection, angle,
				   forwardDirection[0], forwardDirection[1],
				   forwardDirection[2]);
    upDirection = 
      MatrixModifiers.rotate_point(originalUpDirection, angle,
				   forwardDirection[0], forwardDirection[1],
				   forwardDirection[2]);
  }

  private void rotateViewHorizontally(float angle, 
				      float originalForwardDirection[],
				      float originalSidewaysDirection[])
  {
    forwardDirection =
      MatrixModifiers.rotate_point(originalForwardDirection, angle, 
				   upDirection[0], upDirection[1], 
				   upDirection[2]);
    sidewaysDirection = 
      MatrixModifiers.rotate_point(originalSidewaysDirection, angle,
				   upDirection[0], upDirection[1], 
				   upDirection[2]);
  }

  private void rotateViewVertically(float angle,
				    float originalForwardDirection[],
				    float originalUpDirection[])
  {
    forwardDirection =
      MatrixModifiers.rotate_point(originalForwardDirection, angle,
				   sidewaysDirection[0],
				   sidewaysDirection[1],
				   sidewaysDirection[2]);
    upDirection =
      MatrixModifiers.rotate_point(originalUpDirection, angle,
				   sidewaysDirection[0],
				   sidewaysDirection[1],
				   sidewaysDirection[2]);
  }


  /** We allow the user to change the current viewpoint and view
      direction with various key combinations here. */
  public void keyPressed(KeyEvent event) {
    switch(event.getKeyChar()) {
    case 'a':
    case 'A':
      eyePoint[0] += forwardDirection[0] * movementScale;
      eyePoint[1] += forwardDirection[1] * movementScale;
      eyePoint[2] += forwardDirection[2] * movementScale;
      break;
    case 'z':
    case 'Z':
      eyePoint[0] -= forwardDirection[0] * movementScale;
      eyePoint[1] -= forwardDirection[1] * movementScale;
      eyePoint[2] -= forwardDirection[2] * movementScale;
      break;
    case '.':
      rotateViewOnZ(-1.0f, sidewaysDirection, upDirection);
      break;
    case '/':
      rotateViewOnZ(1.0f, sidewaysDirection, upDirection);
      break;
    case 'q':
    case 'Q':
      orbitView(1.0f);
      break;
    case 'e':
    case 'E':
      orbitView(-1.0f);
      break;
    }

    switch(event.getKeyCode()) {
    case KeyEvent.VK_UP:
      rotateViewVertically(1.0f, forwardDirection, upDirection);
      break;

    case KeyEvent.VK_DOWN:
      rotateViewVertically(-1.0f, forwardDirection, upDirection);
      break;

    case KeyEvent.VK_LEFT:
      rotateViewHorizontally(1.0f, forwardDirection, sidewaysDirection);
      break;

    case KeyEvent.VK_RIGHT:
      rotateViewHorizontally(-1.0f, forwardDirection, sidewaysDirection);
      break;
    }

    paint();
  }

  public void mouseReleased(java.awt.event.MouseEvent e) {
    mouseViewAdjustmentInProgress = false;
  }

  public void mousePressed(MouseEvent e) {
    float pixels[];
    startingX                 = e.getX();
    startingY                 = e.getY();
    startingForwardDirection  = (float[])forwardDirection.clone();
    startingUpDirection       = (float[])upDirection.clone();
    startingSidewaysDirection = (float[])sidewaysDirection.clone();
    mouseViewAdjustmentInProgress = true;
  }

  public void mouseMoved(java.awt.event.MouseEvent e) {
    if (mouseViewAdjustmentInProgress) {
      int   deltaX = (e.getX() - startingX);
      int   deltaY = (startingY - e.getY());
      float rotationAngleHorizontal = deltaX / 4.0f, 
	    rotationAngleVertical   = deltaY / 4.0f;

      forwardDirection = 
	MatrixModifiers.rotate_point(startingForwardDirection, 
				     rotationAngleHorizontal, 
				     startingUpDirection[0], 
				     startingUpDirection[1], 
				     startingUpDirection[2]);
      sidewaysDirection = 
	MatrixModifiers.rotate_point(startingSidewaysDirection,
				     rotationAngleHorizontal,
				     startingUpDirection[0], 
				     startingUpDirection[1], 
				     startingUpDirection[2]);

      forwardDirection =
	MatrixModifiers.rotate_point(forwardDirection,
				     rotationAngleVertical,
				     sidewaysDirection[0],
				     sidewaysDirection[1],
				     sidewaysDirection[2]);
      upDirection =
	MatrixModifiers.rotate_point(startingUpDirection, 
				     rotationAngleVertical,
				     sidewaysDirection[0],
				     sidewaysDirection[1],
				     sidewaysDirection[2]);
    }
    paint();
  }

  public void mouseDragged(java.awt.event.MouseEvent e) {
    mouseMoved(e);
  }

  /** Make context the current OpenGL context.  If we fail we just print
    out the exception and continue on. */
  protected void aquireContext() {
      try {
	context.lock();
	context.makeCurrent(this);
      } catch (java.lang.Throwable exception) {
	System.out.println(exception);
	System.out.println("The exception is in " + 
			   java.lang.Thread.currentThread());
	exception.printStackTrace();
      }
  }

  protected void releaseContext() {
    context.unlock();
  }
    
  /** When the window is resized we change our viewport to match the
      new width and height. */
  public void componentResized(ComponentEvent e) {
    /* It's possible that we may be called before the context has been
       setup, and we don't want to use it until it has been
       created. */
    if (context != null) {
      aquireContext();
      gl.viewport(0, 0, getSize().width, getSize().height);
      releaseContext();
    }
  }

  public void paint() {
    aquireContext();
    gl.pushMatrix();
    gl.clear(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT);
    glu.gluLookAt(eyePoint[0], eyePoint[1], eyePoint[2],
		  eyePoint[0] + forwardDirection[0],
		  eyePoint[1] + forwardDirection[1],
		  eyePoint[2] + forwardDirection[2],
		  upDirection[0], upDirection[1], upDirection[2]);

    for (Enumeration e = renderedObjects.elements() ; 
	 e.hasMoreElements() ;) {
      GeometryObject g = (GeometryObject)e.nextElement();
      g.paint(this, gl, glu);
    }
    gl.popMatrix();
    swapBuffers();
    releaseContext();
  }

  /* Methods we need to implement for our listener status. */
  public void mouseClicked(java.awt.event.MouseEvent e) {
    ;
  }
  public void mouseEntered(java.awt.event.MouseEvent e) {
    ;
  }
  public void mouseExited(java.awt.event.MouseEvent e) {
    ;
  }
  public void keyTyped(java.awt.event.KeyEvent e) {
    ;
  }
  public void keyReleased(java.awt.event.KeyEvent e) {
    ;
  }
  public void componentHidden(java.awt.event.ComponentEvent e) {
    ;
  }
  public void componentMoved(java.awt.event.ComponentEvent e) {
    ;
  }
  public void componentShown(java.awt.event.ComponentEvent e) {
    ;
  }
  
}