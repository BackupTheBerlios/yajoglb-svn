/*
 * OpenGLCanvasTest class
 *
 * $Id: Stretch.java,v 1.1 1998/03/30 01:53:17 razeh Exp $
 * 
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@balr.com)
 */


import java.awt.*;
import OpenGL.*;
import java.awt.event.*;

public class OpenGLCanvasTest extends OpenGLCanvas 
  implements OpenGLUConstants, OpenGLConstants, MouseListener, MouseMotionListener {

  private OpenGLContext context;
 
  GLU glu = new GLU();
  GL  gl  = new GL();

  int [] textureIDs;
  TGAFile image;
  private int imageSizeX, imageSizeY;
  byte[] imageData;
  boolean dragInProgress;

  private void rescale() {
    if (imageSizeX < 1)
      imageSizeX = 1;
    if (imageSizeY < 1)
      imageSizeY = 1;

    int imageSize = 4*imageSizeX * imageSizeY;

    imageData = new byte[imageSize];
    glu.gluScaleImage(RGBA, 
		      image.width(), image.height(), GL_UNSIGNED_BYTE,
		      image.getData(),
		      imageSizeX, imageSizeY, GL_UNSIGNED_BYTE, imageData);
  }
  
  public OpenGLCanvasTest()  {
    addMouseListener(this);
    addMouseMotionListener(this);
  }

  public void glInit() {
    super.glInit();

    context = new OpenGLContext(this);
    context.makeCurrent(this);

    glu.gluOrtho2D(0, getSize().width, 0, getSize().height);

    imageSizeX = getSize().width/2;
    imageSizeY = getSize().height/2;
    
    textureIDs = new int[3];
    gl.genTextures(textureIDs);
    
    image = new TGAFile("coins.tga", 128, 128);
    rescale();
    dragInProgress = false;
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
    gl.viewport(0, 0, getSize().width, getSize().height);
  }
  
  public void paint() {
    gl.clear(COLOR_BUFFER_BIT);
    gl.rasterPos(0, 0);
    gl.drawPixels(imageSizeX, imageSizeY, RGBA, GL_UNSIGNED_BYTE,
		  imageData);
    swapBuffers();
  }

  public static void main(String args[]) {
    OpenGLCanvas  canvas = new OpenGLCanvasTest();
    ExitableFrame frame  = new ExitableFrame();

    frame.setBackground(java.awt.Color.black);
    frame.setLayout(new GridLayout(1,1));
    frame.add(canvas);
    frame.setSize(new Dimension(100,100));
    frame.setVisible(true);
  }
}
