/*
 * Simplest possible OpenGL demo
 *
 * $Id: Simplest.java,v 1.1 1999/01/27 00:02:07 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

import java.awt.*;
import OpenGL.*;

class Simplest extends OpenGLCanvas implements GLConstants {

  private OpenGLContext context;
  private GL            gl = new GL();
  private GLU           glu = new GLU();

  /** glInit is called to create our OpenGLContext and setup our model
      view and projection matricies. */
  public void glInixt = new OpenGLContext(this);
    context.makeCurrent(this);
    
    /* Make sure that we use our depth buffer. */
    gl.enable(DEPTH_TEST);

    /* Position our viewer. */
    gl.matrixMode(MODELVIEW);
    gl.translate(0.0f, 0.0f, 0.5f);
    
    /* Set up the viewing projection. */
    gl.matrixMode(PROJECTION);
    gl.frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.5f, 12.0f);

    gl.matrixMode(MODELVIEW);

    glu.gluLookAt(0.0f, 0.0f, -4.0f,
		  0.0f, 0.0f, -3.0f,
		  0.0f, 1.0f,  0.0f);
    gl.color(0.0, 1.0, 0.0);
  }

  /** Render our little triangle. */
  public void paint() {
    /* Clear our display. */
    gl.clear(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT);

    /* Draw a single triangle. */
    gl.begin(TRIANGLES);
    gl.vertex(0.0, 0.0, 0.0);
    gl.vertex(1.0, 0.0, 0.0);
    gl.vertex(0.0, 1.0, 0.0);
    gl.end();

    /* By default, we will be using double buffering, which means we
       need to call swapBuffers() if we want the user to see our
       rendering. */
    swapBuffers();
  }

  /** Brings up a frame that displays an empty window. */
  public static void main(String args[]) {
    Simplest      simplest = new Simplest();
    Frame         frame    = new Frame();

    frame.setLayout(new GridLayout(1,1));
    frame.add(simplest);
    frame.setTitle("The simplest possible OpenGL binding demo.");
    frame.pack();
    frame.setSize(new Dimension(400,400));
    frame.setBackground(java.awt.Color.black);
    frame.setVisible(true);
  }

}
