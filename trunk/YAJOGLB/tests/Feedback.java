/*
 * Feedback test
 *
 * $Id$
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import java.io.*;
import java.awt.*;
import java.awt.event.*;
import OpenGL.*;

/** A simple test of the feedback buffer derived from SGI's example. */
public class Feedback extends OpenGL.Canvas implements GLConstants, 
						       GLUConstants, 
						       ComponentListener {
  /** Where the feedback is store. */
  private GLFeedbackBuffer feedbackBuffer = new GLFeedbackBuffer(1024);
  /** Our OpenGL context. */
  private Context context;
  /** Our drawing object. */
  private GL gl = new GL();

  public Feedback() {
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

  /** Unlock our context. */
  protected void releaseContext() {
    context.unlock();
  }
    
  synchronized public void glInit() {
    context = new Context(this);

    aquireContext();
    gl.matrixMode(PROJECTION);
    gl.loadIdentity();
    gl.ortho(0.0, 100.0, 0.0, 100.0, 0.0, 1.0);
    gl.clearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gl.clear(COLOR_BUFFER_BIT);
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

  /** Our rending method. */
  public void paint() {
    int size;

    if (context != null) {
      aquireContext();
      drawGeometry(RENDER, gl);

      feedbackBuffer.feedbackBuffer(GL_3D_COLOR);
      gl.renderMode(FEEDBACK);
      drawGeometry(FEEDBACK, gl);
      size = gl.renderMode(RENDER);
      
      printFeedbackBuffer(java.lang.System.out, size);
      
      System.out.println(size);
      swapBuffers();
      releaseContext();
    }
  }

  /** Do some drawing so something goes into the feedback buffer. */
  private void drawGeometry(int mode, GL gl) {
    gl.begin (LINE_STRIP);
    gl.normal (0.0, 0.0, 1.0);
    gl.vertex (30.0, 30.0, 0.0);
    gl.vertex (50.0, 60.0, 0.0);
    gl.vertex (70.0, 40.0, 0.0);
    gl.end ();
    if (mode == FEEDBACK)
	gl.passThrough (1.0f);
    gl.begin (POINTS);
    gl.vertex (-100.0, -100.0, -100.0);    /*  will be clipped  */
    gl.end ();
    if (mode == FEEDBACK)
	gl.passThrough (2.0f);
    gl.begin (POINTS);
    gl.normal (0.0, 0.0, 1.0);
    gl.vertex (50.0, 50.0, 0.0);

    gl.end ();
  }

  /** Prints a single 3D Color vertex to out.  It returns the next
      feedback buffer element's index to parse.*/
  private int print3DColorVertex(PrintStream out, int count, int size) {
    int i;
    out.print(" ");
    for(i = 0; i < 7; i++) {
      out.print(feedbackBuffer.elementAt(size - count));
      out.print(" ");
      count--;
    }
    System.out.println();
    return count;
  }

  /** Send the feedback buffer to out. 
   * 
   * @param out the PrintStream to send output to.
   * @param size the size of the buffer.
   */
  public void printFeedbackBuffer(PrintStream out, int size) {
    int count;

    count = size;
    while(count > 0) {
      float token;
      token = feedbackBuffer.elementAt(size-count); count--;

      if (PASS_THROUGH_TOKEN == token) {
	out.println("GL_PASS_THROUGH_TOKEN");
	out.println(feedbackBuffer.elementAt(size - count));
	count--;
      }

      if (POINT_TOKEN == token) {
	out.println("GL_POINT_TOKEN");
	count = print3DColorVertex(out, count, size);
      }

      if (LINE_TOKEN == token) {
	out.println("GL_LINE_TOKEN");
	count = print3DColorVertex(out, count, size);
	count = print3DColorVertex(out, count, size);
      }

      if (LINE_RESET_TOKEN == token) {
	out.println("GL_LINE_RESET_TOKEN");
	count = print3DColorVertex(out, count, size);
	count = print3DColorVertex(out, count, size);
      }
    }
  }

  public static void main(String args[]) {
    Feedback       feedback = new Feedback();
    ExitableFrame  frame  = new ExitableFrame();

    frame.setLayout(new GridLayout(1,1));
    frame.add(feedback);
    frame.setTitle("A Feedback test");
    frame.pack();
    frame.setSize(new Dimension(400,400));
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
