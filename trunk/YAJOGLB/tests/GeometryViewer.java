/* 
 * Geometry viewer class
 *
 * $Id$
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import java.math.*;
import java.util.Vector;
import java.util.Enumeration;
import java.awt.event.*;
import java.awt.*;
import java.lang.reflect.*;
import OpenGL.*;


/** A simple framework for drawing geometry that the user can navigate
 through with the mouse and keyboard.  Only depth testing is enabled
 by default, so lighting has to be handled by the objects (which is
 not so good for performance, but this is supposed to be just a simple
 demo...).
*/
public class GeometryViewer extends OpenGL.Canvas 
  implements MouseListener, MouseMotionListener, 
	     KeyListener, ComponentListener, 
	     GLConstants, GLUConstants {
  /** Where the viewer is located. */
  float[] eyePoint;
  /** Where the viewer is looking. */
  float[] forwardDirection;
  /** The viewer's orientation --- the direction the viewer's right
   * arm points. */
  float[] sidewaysDirection;
  /** The viewer's orientation --- the direction the viewer's head points. */
  float[] upDirection;
  /** Used for scaling. */
  double scale = 1.0;
    
  /** Our initial forward direction for a mouse drag. */
  float [] startingForwardDirection;
  /** Our initial sideways direction for a mouse drag. */
  float [] startingSidewaysDirection;
  /** Our initial up direction for a mouse drag. */
  float[] startingUpDirection;
  /** Where the mouse starts horizontally. */
  int  startingX;
  /** Where the mouse starts vertically. */
  int startingY;
  /** Set to true when the user is dragging the mouse. */
  boolean mouseViewAdjustmentInProgress = false;

  /** Used for our calls to the GLU library. */
  GLU glu = new GLU();
  /** Used for our calls to OpenGL. */
  GL  gl  = new GL();
  Context context = null;
  Vector renderedObjects = new Vector();
  /** Used to handle our resize callback, which needs to use the 
   * locked method interface. 
   */
  Method resizedMethod;
  /** Used to handle our info panel callback, which needs to use the 
   *  locked method interface. 
   */
  Method lockedInfoPanelMethod;
  /** Used to handle our image grabbing callback, which needs to use
   * the locked method interface.
   */
  Method lockedWriteImageMethod;
  /** The panel used to display our frame rate. */
  FrameRatePanel frameRate;

  /*** Add an element to the list of elements we render.
   * @param object the object to render. 
   */
  public void addElement(GeometryObject object) {
    renderedObjects.addElement(object);
  }

  /** How much we scale a single frame movement by.  */
  float movementScale = .2f;

  /** Set our initial viewing parameters. */
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
      because we want to receive KeyEvents, MouseEvents,
      MouseMotionEvents, and ComponentEvents. */
  protected void addListeners() {
    addKeyListener(this);
    addMouseListener(this);
    addMouseMotionListener(this);
    addComponentListener(this);
  }

  public GeometryViewer() {
    addListeners();
    setupViewingParameters();
    try {
      Class parameterTypes[] = new Class[1];
      java.lang.Object o = new java.lang.Object();
      parameterTypes[0] = o.getClass();
      resizedMethod = getClass().getMethod("lockedComponentResized", 
					   parameterTypes);
      lockedInfoPanelMethod = getClass().getMethod("lockedInfoPanel", 
						   parameterTypes);
      lockedWriteImageMethod = getClass().getMethod("lockedWriteImage",
						    parameterTypes);
    } catch (java.lang.NoSuchMethodException e) {
      System.err.println("Unable to find a method.");
    }
  }

  /** Enable depth testing, and position our viewer. */
  public void glInit() {
    try {
      context = new Context(this);
      
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
      
      gl.matrixMode(MODELVIEW);
      } finally {
	releaseContext();
      }
  }

  /** Rotate the viewer's position around a point 7 units
   * a head of the viewer's current position.  The forwardDirection
   * and sidewaysDirection instance variables are updated.
   * @param angle the amount to rotate the viewer's position.
   */
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

  /** Change the viewer's direction around the Z axis (the axis going
   * into and out of the screen).
   * @param angle the amount to change the viewer's direction.
   * @param originalSidewaysDirection the starting sideways direction.
   * @param originalUpDirection the starting up direction.
   */
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

  /** Change the viewer's direction around the horizontal axis.
   * @param angle the amount to change the viewer's direction.
   * @param originalForwardDirection the starting forward direction.
   * @param orignalSidewaysDirection the starting sideways direction.
   */
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

  /** Change the viewer's direction around the vertical axis.
   * @param angle the amount to change the viewer's direction.
   * @param originalForwardDirection the starting forward direction.
   * @param orignalUpDirection the starting up direction.
   */
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
    case 'f':
    case 'F':
      if (frameRate == null) {
	frameRate = new FrameRatePanel();
      } else {
	frameRate.toFront();
      }
      break;
    case 'i':
    case 'I':
      lockedMethod(lockedInfoPanelMethod, this, null);
      break;
    case 'w':
    case 'W':
      writeOutImage();
      break;
    case '+':
      scale /= 1.1;
      break;
    case '-':
      scale *= 1.1;
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

    nativePaint();
  }

  /** Called when the mouse is released; we stop adjusting our
   * viewpoint when this happens.
   * @param e describes the mouse release event.
   */
  public void mouseReleased(java.awt.event.MouseEvent e) {
    mouseViewAdjustmentInProgress = false;
  }

  
  /** Called when the mouse is clicked; we start adjusting our
   * viewpoint when this happens.
   * @param e describes the mouse release event.
   */
  public void mousePressed(MouseEvent e) {
    float pixels[];
    startingX                 = e.getX();
    startingY                 = e.getY();
    startingForwardDirection  = (float[])forwardDirection.clone();
    startingUpDirection       = (float[])upDirection.clone();
    startingSidewaysDirection = (float[])sidewaysDirection.clone();
    mouseViewAdjustmentInProgress = true;
  }

  /** Called when the mouse is moved; we repaint our view so that
   * you can see the movement's affect right away.
   * @param e describes the mouse movement event.
   */
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
      nativePaint();
    }
  }

  /** Called when the mouse is dragged, which for our purposes
   * is the same as a movement.
   * @param e describes the mouse drag event.
   */
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

  /** Release our current context. */
  protected void releaseContext() {
    context.unlock();
  }

  /** When the window is resized we change our viewport to match the
   * new width and height. 
   * @param e describes the resize event; ignored.
  */
  public void componentResized(ComponentEvent e) {
    lockedMethod(resizedMethod, this, null);
  }

  /** We have to do the resize as locked method, and this is the locked
   * method that does it.
   * @param arg ignored, non-optional argument for a locked method.
   */
  public void lockedComponentResized(Object arg) {
    /* It's possible that we may be called before the context has been
       setup, and we don't want to use it until it has been
       created. */
    if (context != null) {
      aquireContext();
      gl.viewport(0, 0, getSize().width, getSize().height);
      releaseContext();
    }
  }

  /** Brings up our info panel. */
  public void lockedInfoPanel(Object arg) {
    aquireContext();
    new InfoPanel(gl);
    releaseContext();
  }

  /** Used for our frame rate, so we know how long we've been up. */
  java.util.Date startDate = null;
  /** Used for our frame rate, so we know how many times we've
      painted. */
  float paintCount = 0;
  
  /** Render all of our GeometryObjects.
   */
  synchronized public void paint() {
    if (context != null) {
      try {
	if (startDate == null) {
	  startDate = new java.util.Date();
	}
	paintCount++;
	aquireContext();

	gl.pushMatrix();
	gl.clear(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT);
	glu.gluLookAt(eyePoint[0], eyePoint[1], eyePoint[2],
		      eyePoint[0] + forwardDirection[0],
		      eyePoint[1] + forwardDirection[1],
		      eyePoint[2] + forwardDirection[2],
		      upDirection[0], upDirection[1], upDirection[2]);
      
	gl.scale(scale, scale, scale);
	for (Enumeration e = renderedObjects.elements() ; 
	     e.hasMoreElements() ;) {
	  GeometryObject g = (GeometryObject)e.nextElement();
	  g.paint(this, gl, glu);
	}
	gl.popMatrix();
	swapBuffers();
	java.util.Date endDate = new java.util.Date();
	if ((frameRate != null) && (paintCount % 100) == 0) {
	  frameRate.setFrameRate(
				 paintCount /
				 ((endDate.getTime() - startDate.getTime())/1000.0));
	  
	}
	/* Check for any OpenGL errors. */      
	int errorNumber = gl.getError();
	if (errorNumber  != NO_ERROR) {
	  System.out.println("error = " + errorNumber);
	  System.out.println("error description = " + glu.gluErrorString(errorNumber));
	}
      } finally {
	releaseContext();
      }
    }
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

  /** Write out the current screen image to a file name specified
   * by the user.
   */
  public void writeOutImage() {
    // Get a filename.
    FileDialog fileDialog = 
      new FileDialog(new Frame(), "Save screen dump to...",  
		     FileDialog.SAVE);
    fileDialog.show();
    if (fileDialog.getFile() != null) {
      String imageFilename = fileDialog.getDirectory() + "/" + fileDialog.getFile();
      Object arguments[] = new Object[1];
      arguments[0] = imageFilename;
      lockedMethod(lockedWriteImageMethod, this, arguments);
    }
  }

  /** The locked method to write out the image.  It needs to be locked
   * because it aquires the GL context.
   * @param imageFilename the name of the file to write out.
   */
  public void lockedWriteImage(Object imageFilename) {
    String filename = (String) imageFilename;
    aquireContext();
    TGAFile file = new TGAFile(gl, this);
    try {
      file.write(filename);
    } catch (java.io.IOException exception) {
      System.out.println("Exception " + exception + 
			 " writing " + filename + " to disk.");
    }
    releaseContext();
  }
}
