/*
 * OpenGLCanvasTest class
 *
 * $Id: Stretch.java,v 1.2 1998/11/01 02:24:18 razeh Exp $
 * 
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@balr.com)
 */


import java.awt.*;
import OpenGL.*;
import java.awt.event.*;

public class Stretch extends OpenGLCanvas 
  implements GLUConstants, GLConstants, MouseListener, MouseMotionListener {

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
  
  public Stretch()  {
    addMouseListener(this);
    addMouseMotionListener(this);
  }

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

  public void mouseReleased(java.awt.event.MouseEvent e) {
    dragInProgress = false;
  }

  public void mousePressed(java.awt.event.MouseEvent e) {
    dragInProgress = true;

    imageSizeX = e.getX();
    imageSizeY = getSize().height - e.getY() ;
    rescale();
    paint();
  }

  public void mouseMoved(java.awt.event.MouseEvent e) {
    if (dragInProgress)
      mousePressed(e);
  }

  public void mouseClicked(java.awt.event.MouseEvent e) {
    ;
  }

  public void mouseEntered(java.awt.event.MouseEvent e) {
    ;
  }

  public void mouseExited(java.awt.event.MouseEvent e) {
    ;
  }

  public void mouseDragged(java.awt.event.MouseEvent e) {
    imageSizeX = e.getX();
    imageSizeY = getSize().height - e.getY() ;
    rescale();
    paint();
  }
    


  /** When the window is resized we change our viewport to match the
      new width and height. */
  public void componentResized(ComponentEvent e) {
    aquireContext();
    gl.viewport(0, 0, getSize().width, getSize().height);
    //gl.matrixMode(PROJECTION);
    //gl.loadIdentity();
    //glu.gluOrtho2D(0, getSize().width, 0, getSize().height);

    //gl.matrixMode(MODELVIEW);
    releaseContext();
  }
  
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
