/*
 * Stretch class
 *
 * $Id: Stretch.java,v 1.11 2002/04/14 18:12:21 razeh Exp $
 * 
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 */


import java.awt.*;
import OpenGL.*;
import java.awt.event.*;
import java.lang.reflect.*;

/** This demonstrates the use of gluScaleImage by displaying a raster
    image on the screen that can be stretched by clicking the mouse on
    different portions of the screen. */
public class Stretch extends OpenGL.Canvas 
  implements GLUConstants, GLConstants, MouseListener, MouseMotionListener, 
	     ComponentListener {

  /** Our own OpenGL context. */
  protected Context context;
 
  GLU glu = new GLU();
  GL  gl  = new GL();

  int [] textureIDs;
  TGAFile image;
  private int imageSizeX, imageSizeY;
  protected int getImageSizeX() { return imageSizeX; }
  protected int getImageSizeY() { return imageSizeY; }
  byte[] imageData;
  boolean dragInProgress;
  Method resizedMethod;

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

  /** Change the size of the image to fit imageSizeX and imageSizeY.
   * Assumes that we currently have aquired an OpenGL context.*/
  protected void rescale() {
    if (imageSizeX < 1)
      imageSizeX = 1;
    if (imageSizeY < 1)
      imageSizeY = 1;

    int imageSize = 4*imageSizeX * imageSizeY;

    imageData = new byte[imageSize];
    glu.gluScaleImage(RGBA, 
		      image.getSize().width, image.getSize().height,
		      GL_UNSIGNED_BYTE, image.getData(),  
		      getImageSizeX(), getImageSizeY(),
		      GL_UNSIGNED_BYTE, imageData);
  }

  /** Construct a Stretch object by making it a Mouse Listener, Mouse
      Motion Listener, and Component Listener. */
  public Stretch()  {
    addMouseListener(this);
    addMouseMotionListener(this);
    addComponentListener(this);
    try {
      Class parameterTypes[] = new Class[1];
      java.lang.Object o = new java.lang.Object();
      parameterTypes[0] = o.getClass();
      
      resizedMethod = getClass().getMethod("lockedComponentResized", 
					   parameterTypes);
    } catch (java.lang.NoSuchMethodException e) {
      System.err.println("Unable to find resize method.");
    }
  }

  /** Create our OpenGL context, setup our display matricies, and read in
      our texture file. */
  public void glInit() {
    super.glInit();

    context = new Context(this);
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
    nativePaint();
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
    nativePaint();
  }
    
  public void lockedComponentResized(Object arg) {
    if (context != null) {
      aquireContext();
      gl.viewport(0, 0, getSize().width, getSize().height);
      releaseContext();
    }
  }

  /** When the window is resized we change our viewport to match the
      new width and height. */
  public void componentResized(ComponentEvent e) {
    lockedMethod(resizedMethod, this, null);
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
  synchronized protected void paint() {
    aquireContext();
    rescale();
    gl.clear(COLOR_BUFFER_BIT);
    gl.rasterPos(0, 0);
    gl.drawPixels(getImageSizeX(), getImageSizeY(), 
		  RGBA, GL_UNSIGNED_BYTE, imageData);
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
