/*
 * OpenGLCanvasTest class
 *
 * $Id: Stretch.java,v 1.6 2001/06/10 19:16:45 razeh Exp $
 * 
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 */


import java.awt.*;
import OpenGL.*;
import java.awt.event.*;

/** This demonstrates the use of gluScaleImage by displaying a raster
    image on the screen that can be stretched by clicking the mouse on
    different portions of the screen. */
public class Stretch extends OpenGLCanvas 
implements GLUConstants, GLConstants, MouseListener, MouseMponentListener {

  /** Our own OpenGL context. */
  private OpenGLContext context;
 
  GLU glu = new GLU();
  GL  gl  = new GL();

  int [] textureIDs;
  TGAFile image;
  private int imageSizeX, imageSizeY;
  byte[] imageData;
  boolean dragInProgress;

  /** Flip image's data on the Y axis, so that is isn't upside down in
      the display. */
  private void flip() {
    int imagePosition = 0;
    byte imageData[] = image.getData();

    for(int y = 0; y < image.getSize().height/2; y++) {
      for(int x = 0; x < image.getSize().width; x++) {
	byte temp1, temp2, temp3, temp4;
	int startingImagePosition;
	int endingImagePosition;

	startingImagePosition = 4*( (y*image.getSize().width) + x);

	endingImagePosition = 4*(((image.getSize().height-y-1)*image.getSize().width) 
	  + x);
	
	temp1 = imageData[startingImagePosition];
	temp2 = imageData[startingImagePosition+1];
	temp3 = imageData[startingImagePosition+2];
	temp4 = imageData[startingImagePosition+3];

	imageData[startingImagePosition] = imageData[endingImagePosition];
	imageData[startingImagePosition+1] = imageData[endingImagePosition+1];
	imageData[startingImagePosition+2] = imageData[endingImagePosition+2];
	imageData[startingImagePosition+3] = imageData[endingImagePosition+3];

	imageData[endingImagePosition] = temp1;
	imageData[endingImagePosition+1] = temp2;
	imageData[endingImagePosition+2] = temp3;
	imageData[endingImagePosition+3] = temp4;
      }
    }
  }

  /** Change the size of the image to fit imageSizeX and imageSizeY. */
  private void rescale() {
    aquireContext();
    if (imageSizeX < 1)
      imageSizeX = 1;
    if (imageSizeY < 1)
      imageSizeY = 1;

    int imageSize = 4*imageSizeX * imageSizeY;

    imageData = new byte[imageSize];
    glu.gluScaleImage(RGBA, 
		      image.getSize().width, image.getSize().height, GL_UNSIGNED_BYTE,
		      image.getData(),
		      imageSizeX, imageSizeY, GL_UNSIGNED_BYTE, imageData);
    releaseContext();
  }

  /** Construct a Stretch object by making it a Mouse Listener, Mouse
      Motion Listener, and Component Listener. */
  public Stretch()  {
    addMouseListener(this);
    addMouseMotionListener(this);
    addComponentListener(this);
  }

  /** Create our OpenGL context, setup our display matricies, and read in
    our texture file. */
  public void glInit() {
    super.glInit();

    context = new OpenGLContext(this);
    aquireContext();

    gl.matrixMode(PROJECTION);
    gl.loadIdentity();
    glu.gluOrtho2D(0, getSize().width, 0, getSize().height);

    gl.matrixMode(MODELVIEW);
    imageSizeX = getSize().width/2;
    imageSizeY = getSize().height/2;
    
    image = new TGAFile("ogl.tga");
    flip();
    rescale();
    dragInProgress = false;
    releaseContext();
  }

  /** Take note that the mouse is no longer being held done. */
  public void mouseReleased(java.awt.event.MouseEvent e) {
    dragInProgress = false;
  }

  /** Take note that the user pressed down on the mouse by rescaling 
    our image. */
  public void mousePressed(java.awt.event.MouseEvent e) {
    dragInProgress = true;

    imageSizeX = e.getX();
    imageSizeY = getSize().height - e.getY() ;
    rescale();
    paint();
  }

  /** Resize our image by calling <code>mousePressed</code>. */
  public void mouseMoved(java.awt.event.MouseEvent e) {
    if (dragInProgress)
      mousePressed(e);
  }

  /** We need this method, which does nothing, to be a MouseListener. */
  public void mouseClicked(java.awt.event.MouseEvent e) {
    ;
  }

  /** We need this method, which does nothing, to be a MouseListener. */
  public void mouseEntered(java.awt.event.MouseEvent e) {
    ;
  }

  /** We need this method, which does nothing, to be a MouseListener. */
  public void mouseExited(java.awt.event.MouseEvent e) {
    ;
  }

  /** We need this method, which does nothing, to be a MouseListener. */
  public void mouseDragged(java.awt.event.MouseEvent e) {
    imageSizeX = e.getX();
    imageSizeY = getSize().height - e.getY() ;
    rescale();
    paint();
  }
    


  /** When the window is resized we change our viewport to match the
      new width and height. */
  public void componentResized(ComponentEvent e) {

    if (context != null) {
      aquireContext();
      gl.viewport(0, 0, getSize().width, getSize().height);
      releaseContext();
    }
  }

  /** We need this method, which does nothing, to be a ComponentListener. */
  public void componentHidden(java.awt.event.ComponentEvent e) {
    ;
  }

  /** We need this method, which does nothing, to be a ComponentListener. */
  public void componentMoved(java.awt.event.ComponentEvent e) {
    ;
  }

  /** We need this method, which does nothing, to be a ComponentListener. */
  public void componentShown(java.awt.event.ComponentEvent e) {
    ;
  }

  /** Draw our image with the current scaling parameters. */
  public void paint() {
    aquireContext();
    gl.clear(COLOR_BUFFER_BIT);
    gl.rasterPos(0, 0);
    gl.drawPixels(imageSizeX, imageSizeY, RGBA, GL_UNSIGNED_BYTE,
		  imageData);

    swapBuffers();
    releaseContext();
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

  /** Unlock our context. */
  protected void releaseContext() {
    context.unlock();
  }

  public static void main(String args[]) {
    Stretch       canvas = new Stretch();
    ExitableFrame frame  = new ExitableFrame();

    frame.setBackground(java.awt.Color.black);
    frame.setLayout(new GridLayout(1,1));
    frame.add(canvas);
    frame.setSize(new Dimension(100,100));
    frame.setTitle("gluScaleImage test");
    frame.setVisible(true);
  }
}
