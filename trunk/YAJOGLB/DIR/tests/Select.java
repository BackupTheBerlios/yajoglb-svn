/*
 * Selection test
 *
 * $Id: Select.java,v 1.3 2001/06/10 20:50:43 razeh Exp $
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@yahoo.com)
 */


import OpenGL.*;
import java.awt.*;
import java.awt.event.*;

/** A simple test of the selection buffer derived from SGI's example. */
public class Select extends OpenGLCanvas implements GLConstants, GLUConstants, ComponentListener {

  private GL gl = new GL();
  private GLU glu = new GLU();
  private OpenGLContext context;

  public Select() {
    addComponentListener(this);
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
    
  public void glInit() {
    context = new OpenGLContext(this);
    aquireContext();
    gl.enable(DEPTH_TEST);
    gl.shadeModel(FLAT);
    releaseContext();
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
    if (context != null) {
      aquireContext();
      gl.clearColor(0.0f, 0.0f, 0.0f, 0.0f);
      gl.clear(COLOR_BUFFER_BIT|DEPTH_BUFFER_BIT);
      drawScene();
      selectObjects();
      gl.flush();
      releaseContext();
    }
  }


  /* draw a triangle with vertices at (x1, y1), (x2, y2) 
   * and (x3, y3) at z units away from the origin.
   */
  private void drawTriangle(float x1, float y1, float x2, 
			    float y2, float x3, float y3, float z) {
    gl.begin(TRIANGLES);
    gl.vertex(x1, y1, z);
    gl.vertex(x2, y2, z);
    gl.vertex(x3, y3, z);
    gl.end();
  }

/* draw a rectangular box with these outer x, y, and z values */
  private void drawViewVolume (float x1, float x2, float y1, 
			       float y2, float z1, float z2)
    {
      gl.color (1.0, 1.0, 1.0);
      gl.begin (LINE_LOOP);
      gl.vertex (x1, y1, -z1);
      gl.vertex (x2, y1, -z1);
      gl.vertex (x2, y2, -z1);
      gl.vertex (x1, y2, -z1);
      gl.end ();
      
      gl.begin (LINE_LOOP);
      gl.vertex (x1, y1, -z2);
      gl.vertex (x2, y1, -z2);
      gl.vertex (x2, y2, -z2);
      gl.vertex (x1, y2, -z2);
      gl.end ();
      
      gl.begin (LINES);	/*  4 lines	*/
      gl.vertex (x1, y1, -z1);
      gl.vertex (x1, y1, -z2);
      gl.vertex (x1, y2, -z1);
      gl.vertex (x1, y2, -z2);
      gl.vertex (x2, y1, -z1);
      gl.vertex (x2, y1, -z2);
      gl.vertex (x2, y2, -z1);
      gl.vertex (x2, y2, -z2);
      gl.end ();
    }
  /* drawScene draws 4 triangles and a wire frame
   * which represents the viewing volume.
   */
  private void drawScene ()
    {
      gl.matrixMode (PROJECTION);
      gl.loadIdentity ();
      glu.gluPerspective (40.0, 4.0/3.0, 1.0, 100.0);
      
      gl.matrixMode (MODELVIEW);
      gl.loadIdentity ();
      glu.gluLookAt (7.5, 7.5, 12.5, 2.5, 2.5, -5.0, 0.0, 1.0, 0.0);
      gl.color (0.0f, 1.0f, 0.0f);	/*  green triangle	*/
      drawTriangle (2.0f, 2.0f, 3.0f, 2.0f, 2.5f, 3.0f, -5.0f);
      gl.color (1.0f, 0.0f, 0.0f);	/*  red triangle	*/
      drawTriangle (2.0f, 7.0f, 3.0f, 7.0f, 2.5f, 8.0f, -5.0f);
      gl.color (1.0f, 1.0f, 0.0f);	/*  yellow triangles	*/
      drawTriangle (2.0f, 2.0f, 3.0f, 2.0f, 2.5f, 3.0f, 0.0f);
      drawTriangle (2.0f, 2.0f, 3.0f, 2.0f, 2.5f, 3.0f, -10.0f);
      drawViewVolume (0.0f, 5.0f, 0.0f, 5.0f, 0.0f, 10.0f);
    }
  
/* processHits prints out the contents of the selection array
 */
  private void processHits (int hits, GLSelectionBuffer buffer) {
    System.out.println("hits =  " + hits);
    int i = 0;
    for(int hit = 0; hit < hits; hit++) {
      int names = buffer.elementAt(i);
      System.out.println(" number of names for hit = " + 
			 buffer.elementAt(i++));
      System.out.println("  z1 is " + (float) buffer.elementAt(i++) / 
			 0x7fffffff);
      System.out.println("  z2 is " + (float) buffer.elementAt(i++) / 
			 0x7fffffff);
      System.out.print("    the name is ");
      for(int j = 0; j < names; j++) {
	System.out.println(buffer.elementAt(i++));
      }
      System.out.println();
    }
  }

/* selectObjects "draws" the triangles in selection mode, 
 * assigning names for the triangles.  Note that the third
 * and fourth triangles share one name, so that if either 
 * or both triangles intersects the viewing/clipping volume, 
 * only one hit will be registered.
 */
  static private int BUFSIZE  = 512;

  public void selectObjects() {
    GLSelectionBuffer buffer = new GLSelectionBuffer(BUFSIZE);
    int hits;
    
    buffer.selectBuffer();
    gl.renderMode (SELECT);
    
    gl.initNames();
    gl.pushName(0);
    
    gl.pushMatrix ();
    gl.matrixMode (PROJECTION);
    gl.loadIdentity ();
    gl.ortho (0.0, 5.0, 0.0, 5.0, 0.0, 10.0);
    gl.matrixMode (MODELVIEW);
    gl.loadIdentity ();
    gl.loadName(1);
    drawTriangle (2.0f, 2.0f, 3.0f, 2.0f, 2.5f, 3.0f, -5.0f);
    gl.loadName(2);
    drawTriangle (2.0f, 7.0f, 3.0f, 7.0f, 2.5f, 8.0f, -5.0f);
    gl.loadName(3);
    drawTriangle (2.0f, 2.0f, 3.0f, 2.0f, 2.5f, 3.0f, 0.0f);
    drawTriangle (2.0f, 2.0f, 3.0f, 2.0f, 2.5f, 3.0f, -10.0f);
    gl.popMatrix ();
    gl.flush ();
    
    hits = gl.renderMode (RENDER);
    processHits (hits, buffer);
  } 

  public static void main(String args[]) {
    Select       select   = new Select();
    ExitableFrame  frame  = new ExitableFrame();

    frame.setLayout(new GridLayout(1,1));
    frame.add(select);
    frame.setTitle("A Selection test");
    frame.pack();
    frame.setSize(new Dimension(200,200));
    frame.setBackground(java.awt.Color.black);
    frame.setVisible(true);
  }


  /* Empty methods so that we can be a component listener. */
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
