/* 
 * OpenGLWidget class
 *
 * $Id: OpenGLWidget.java,v 1.4 1998/09/10 01:05:00 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */


package OpenGL;

import java.awt.Frame;
import java.util.EventObject;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.AWTEvent;

/** This implements a frame that OpenGL can draw onto.
 *
 * We implement the MouseListener, MouseMotionListener,
 * WindowListener, ComponentListener, and KeyListener interfaces as
 * empty functions. <P>
 *
 * Although OpenGLWidget is subclassed from Frame don't count on any
 * of the Frame methods working!  We implement our own window
 * functionality, so methods like setSize() will have no effect.
 * Additionally, don't expect to get events other than the ones we
 * implement listener interfaces for.
 *
 *
 * @author Robert Allan Zeh (razeh@balr.com) 
 *
 * @version 0.1
 *
 */

public class OpenGLWidget extends Frame implements OpenGLConstants,
OpenGLUConstants, Runnable, MouseListener, MouseMotionListener,
WindowListener, ComponentListener, KeyListener {

  static {
    System.load("OpenGL4java");
  }
  
  
  /** Our initial X position, in pixels. */
  protected int x = 0;
  /** Our initial Y position, in pixels. */
  protected int y = 0;

  static int initialWidth  = 400;
  static int initialHeight = 400;

  private OpenGLCapabilities capabilities = null;

  /** This is called to add in the standard listeners at startup.  We
      express interest in window and component events here to make
      sure that we properly handle resize and repaint events. */
  protected void addListeners() {
    addWindowListener(this);
    addComponentListener(this);
  }

  /** This performs setup work that has to be done in all of our
    constructors. */
  private void OpenGLWidgetSetup() {
    setSize(initialWidth, initialHeight);
    addListeners();
    setCapabilities(defaultCapabilities());
  }

  /** This is a stub for any initialization we will have to do.  It
      does not instantiate the widget; that actually happens in our
      run method.  It happens in our run method because we want to
      setup all of our platform dependent context in the proper
      thread. */
  public OpenGLWidget() {
    OpenGLWidgetSetup();
  }

  /** This sets our title, but does not instantiate the widget; that
      actually happens in our run method. It happens in our run
      method because we want to setup all of our platform dependent
      context in the proper thread. */
  public OpenGLWidget(String title) {
    System.out.println("OpenGLWidget about to be created");
    OpenGLWidgetSetup();
    setTitle(title);
  }

  /** This performs our platform dependent startup by calling
    openOpenGLWidget() and then starts out event loop. */
  public void run()  throws OpenGLWidgetOpenFailedException {
    if (openOpenGLWidget(x, y, getSize().width, getSize().height, 
			 getTitle()) == false) {
      throw new OpenGLWidgetOpenFailedException ();
    }
    System.out.println("Starting event loop " + this);
    eventLoop();
  }  

  /** Native C function to open the OpenGLwidget.   */
  private native boolean openOpenGLWidget(int x, int y, int width, int height,
					  String title);
  
  /** Native method to loop through events.  This will invoke
      handleEvent for each of the events that we are interested in. */
  private native void eventLoop(); 

  /** The native method that actually changes the window title on screen. */
  private native void setNativeTitle(String title);

  /** We override the normal setTitle method here to make sure that
      our own private window implementation has a chance to change the
      actual window title. */
  public void setTitle(String title) {
    super.setTitle(title);
    setNativeTitle(title);
  }

  /** Sets the capabilities that this widget will use when it is opened
     up.  This has no effect once the widget has been displayed on
     screen. */
  protected void setCapabilities(OpenGLCapabilities newCapabilities) {
    capabilities = newCapabilities;
  }

  /** Returns the capabilities object that was used when we started
      our display. */
  protected OpenGLCapabilities capabilities() {
    return capabilities;
  }

  /*
   * Setup methods
   */

  /** The default OpenGLCapabilities object that we return at startup
      for our display. */
  private OpenGLCapabilities defaultCapabilities() {
    return OpenGLCapabilities.defaultCapabilities();
  }

  /*
   * Event handling methods
   */

  /** This is called when ever we receive an event from the window
      system.  Based on the event type it will in turn call glInit(),
      resize(), paint(), or keyDown().  It will return TRUE if the
      event was handled and false if it was not.  Normally this is
      called by the native platform code, and you should not need to
      call it yourself. */
  public boolean handleEvent(AWTEvent event) {
    
    /* The processEvent method won't invoke paint for us, even if we
       hand it a UPDATE event. */
    switch(event.getID()) {
      case java.awt.event.PaintEvent.PAINT:
	paint();
	break;
    }
    
    processEvent(event);

    return true;
  }
       

  /* Convenience event handling routines */
  /** This should repaint the screen.  It is called as needed. */
  public void paint() {
    ;
  }

  private OpenGLContext context;

  /** This is called right after our window is activated.  By default
    we create an OpenGL context here --- so you will not get any
    output if you override this method but don't invoke it. */
  public void glInit() {
    context = new OpenGLContext(this);
    context.makeCurrent(this);
  }


  /** Called when we get a key press. */
  public void keyPressed(KeyEvent event) {
    ;
  }

  /** Called when the key is released. */ 
  public void keyReleased(KeyEvent event) {
    ;
  }

  /** Called when a key has been typed. */
  public void keyTyped(KeyEvent event) {
    ;
  }
  
  /* Our implementation of WindowListener. */

  /** This is called when the window is opened and does nothing.  It
      is part of our Window Listener implementation.  Our init method
      sets us up as a window listener. */
  public void windowOpened(WindowEvent e) {
    ;
  }    

  /** This is called when the window is closing and currently does
      nothing.  It is part of our Window Listener implementation.  Our
      init method sets us up as a window listener. */
  public void windowClosing(WindowEvent e) {
    ;
  }


  /** This is called when the window has been closed and currently does
      nothing.  It is part of our Window Listener implementation.  Our
      init method sets us up as a window listener. */
  public void windowClosed(WindowEvent e) {
    ;
  }

  /** This is called when the window is iconified and currently does
      nothing.  It is part of our Window Listener implementation.  Our
      init method sets us up as a window listener. */
  public void windowIconified(WindowEvent e) {
    ;
  }

  /** This is called when the window is deiconified and currently does
      nothing.  It is part of our Window Listener implementation.  Our
      init method sets us up as a window listener. */
  public void windowDeiconified(WindowEvent e) {
    ;
  }

  /** This is called when the window is activated and currently calls
      glInit().  It is part of our Window Listener implementation.
      Our init method sets us up as a window listener. */
  public void windowActivated(WindowEvent e) {
    glInit();
  }

  /** This is called when the window is deactivated and currently does
      nothing.  It is part of our Window Listener implementation.  Our
      init method sets us up as a window listener. */
  public void windowDeactivated(WindowEvent e) {
    ;
  }

  /* Our implementation of ComponentListener. */
  /** This is called when we are hidden as part of our Component
      Listener implementation and currently does nothing. */
  public void componentHidden(ComponentEvent e) {
    ;
  }

  /** This is called when we are moved as part of our Component
      Listener implementation and currently does nothing. */
  public void componentMoved(ComponentEvent e) {
    ;
  }

  /** This is called when we are resized as part of our Component
      Listener implementation and currently does nothing.  */
  public void componentResized(ComponentEvent e) {
    ;
  }

  /** This is invoked when we are shown on screen.  It currently does
      nothing. */
  public void componentShown(ComponentEvent e) {
    ;
  }

  /* Our implementation of MouseListener. */

  /** This is called when the mouse is clicked and we have been
      registered for mouse events.  This method does nothing and is
      here as part of our MouseListener implementation. */
  public void mouseClicked(MouseEvent e) {
    ;
  }

  /** This is called when the mouse enters our widget and we have been
      registered for mouse events.  This method does nothing and is
      here as part of our MouseListener implementation. */
  public void mouseEntered(MouseEvent e) {
    ;
  }

  /** This is called when the mouse leaves our widget and we have been
      registered for mouse events.  This method does nothing and is
      here as part of our MouseListener implementation. */
  public void mouseExited(MouseEvent e) {
    ;
  }

  /** This is called when one of the mouse buttons goes down and we
      have been registered for mouse events.  This method does nothing
      and is here as part of our MouseListener implementation. */
  public void mousePressed(MouseEvent e) {
    ;
  }


  /** This is called when a mouse button goes up and we have been
      registered for mouse events.  This method does nothing, and is
      here only as part of our MouseListener implementation. */
  public void mouseReleased(MouseEvent e) {
    ;
  }

  /* Our Mouse Motion Listener implementation */
  /** This is called only when the mouse is dragged and we have been
      registered for mouse motion events.  This method does nothing,
      and is here only as part of our Mouse Motion Listener
      implementation. */
  public void mouseDragged(MouseEvent e) {
    ;
  }

  /** This is called when the mouse is moved and we have been
    registered for mouse motion events.  This method does nothing, and
    is here only as part of our Mouse Motion Listener
    implementation. */
  public void mouseMoved(MouseEvent e) {
    ;
  }
  

  /** This swaps in the double buffer that we've been using.  If you
      don't call this after you draw, nothing will be displayed on the
      screen. */
  public native void swapBuffers();
}



