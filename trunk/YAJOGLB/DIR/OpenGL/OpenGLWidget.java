/* 
 * OpenGLWidget class
 *
 * $Id: OpenGLWidget.java,v 1.3 1998/03/05 23:56:42 razeh Exp $
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

/**
 * 
 * 
 * This defines a class, OpenGLWidget, which uses native methods
 * to implement Java bindings for OpenGL. <P>
 *
 * The Java bindings use slightly different function names than the
 * OpenGL C API.  OpenGL's "gl" prefix has been removed from the
 * function names, because it is not needed to prevent name space
 * pollution.  The trailing argument descriptions (such as "3d" and
 * "2i") have also been removed, as Java has function overloading.
 * For example, "glVertex3d" has become "vertex(double, double,
 * double)".  When the C API called for an array length it has been
 * omitted from the Java bindings, as the array length can be
 * determined from the array. <P>
 *
 * With the exception of gluErrorString, which remains gluErrorString,
 * the glu functions have undergone the same transformation as the
 * OpenGL functions. <P>
 *
 * Some OpenGL methods that take void pointer arguments as buffers for
 * return data have been changed to return arrays containing the data. <P>
 *
 * Routines that accept void pointers in the C API, such as
 * drawPixels, have an instance for each pointer type in the Java
 * binding.  For example, drawPixels expands into 4 different methods:

<ul>
<li>
  drawPixels(int width, int height,
	     int format, int type, byte pixels[]);
</li>
<li>
  drawPixels(int width, int height,
	     int format, int type, short pixels[]);
</li>
<li>
  drawPixels(int width, int height,
	     int format, int type, int pixels[]);
</li>
<li>
  drawPixels(int width, int height,
             int format, int type, float pixels[]);
</li>
</ul>
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

  /*
   * GL Methods
   */


  /*
   * Misc. OpenGL functions
   */
  public native void clearIndex(float c);
  public native void clearColor(float red, float green, float blue, 
				float alpha);
  public native void clear(int mask);
  public native void indexMask(int mask);
  public native void colorMask(boolean red, boolean green, boolean blue, 
			       boolean alpha);
  public native void alphaFunc(int func, float ref);
  public native void blendFunc(int sfactor, int dfactor);
  public native void logicOp(int opcode);
  public native void cullFace(int mode);
  public native void frontFace(int mode);
  public native void pointSize(float size);
  public native void lineWidth(float width);
  public native void lineStipple(int factor, short pattern);
  public native void polygonMode(int face, int mode);
  public native void polygonOffset(float factor, float units);
  public native void polygonStipple(byte mask[]);
  public native void getPolygonStipple(byte mask[]);
  public native void edgeFlag(boolean flag);
  public native void scissor(int x, int y, int width, int height);
  public native void clipPlane(int plane, double equation[]);
  public native void getClipPlane(int plane, double equation[]);
  public native void drawBuffer(int mode);
  public native void readBuffer(int mode);
  public native void enable(int capability);
  public native void disable(int capability);
  public native boolean isEnabled(int capability);
  public native void get(int pname, boolean params[]);
  public native void get(int pname, double params[]);
  public native void get(int pname, float params[]);
  public native void get(int pname, int params[]);
  public native void pushAttrib(int mask);
  public native void popAttrib();
  public native void pushClientAttrib(int mask);
  public native void popClientAttrib();
  public native int renderMode(int mode);
  public native int getError();
  public native String getString(int name);
  public native void finish();
  public native void flush();
  public native void hint(int target, int mode);

  /* 
   * Depth buffer 
   */
  public native void clearDepth(double depth);
  public native void depthFunc(int func);
  public native void depthMask(boolean flag);
  public native void depthRange(double near_val, double far_val);
  
  /*
   * Accumulation buffer
   */
  public native void clearAccum(float red, float green, float blue, 
				float alpha);
  public native void accum(int op, float value);
  
  /*
   * Transformation
   */
  public native void matrixMode(int mode);
  public native void ortho(double left, double right,
			   double botton, double top,
			   double near_val, double far_val);


  public native void frustum(double left, double right, 
			     double bottom, double top, 
			     double near_val, double far_val);

  public native void viewport(int x, int y, int width, int height);
  public native void pushMatrix();
  public native void popMatrix();
  public native void loadIdentity();
  private native void loadMatrixd(double darr[]);
  private native void loadMatrixf(float farr[]);

  public void loadMatrix(double darr[]) {
    if (darr.length == 16) {
      loadMatrixd(darr); 
    }else {
      throw new 
          IllegalArgumentException("Expected a double array of length 16");
    }
  }

  public void loadMatrix(float darr[]) {
    if (darr.length == 16) {
      loadMatrixf(darr);
    } else {
      throw new 
          IllegalArgumentException("Expected a double array of length 16");
    }
  }
  
  private native void multMatrixd(double M[]);
  private native void multMatrixf(float M[]);

  public void multMatrix(double M[]) {
    if (M.length == 16) {
      multMatrixd(M);
    } else {
      throw new 
          IllegalArgumentException("Expected a double array of length 16");
   }
  }
  public void multMatrix(float M[]) {
    if (M.length == 16) {
      multMatrixf(M);
    } else {
      throw new 
          IllegalArgumentException("Expected a double array of length 16");
   }
  }
  private native void rotated(double angle, double x, double y, double z);
  private native void rotatef(float angle,  float x,  float y,  float z);
  
  public void rotate(double angle, double x, double y, double z) {
    rotated(angle, x, y, z);
  }
  public void rotate(float angle, float x, float y, float z) {
    rotatef(angle, x, y, z);
  }

  private native void scaled(double x, double y, double z);
  private native void scalef(float x,  float y,  float z);

  public void scale(double x, double y, double z) {
    scaled(x, y, z);
  }
  public void scale(float x, float y, float z) {
    scalef(x, y, z);
  }

  private native void translated(double x, double y, double z);
  private native void translatef(float x,  float y,  float z);

  public void translate(double x, double y, double z) {
    translated(x, y, z);
  }
  public void translate(float x,  float y,  float z) {
    translatef(x, y, z);
  }

  /*
   * Display Lists
   */
  public native boolean isList(int list);
  public native void deleteLists(int list, int range);
  public native int genLists(int range);
  public native void newList(int list, int mode);
  public native void endList();
  public native void callList(int list);

  public native void callLists(int n, int type, byte lists[]);
  public native void callLists(int n, int type, short lists[]);
  public native void callLists(int n, int type, float lists[]);





  public native void listBase(int base);
  
  /*
   * Drawing Functions
   */
  public native void begin(int mode);
  public native void end();

  private native void vertex2d(double x, double y);
  private native void vertex2f(float x,  float y);
  private native void vertex2i(int x,    int y);
  private native void vertex2s(short x,  short y);
  
  public void vertex(double x, double y) {
    vertex2d(x, y);
  }
  public void vertex(float x, float y) {
    vertex2f(x, y);
  }
  public void vertex(int x, int y) {
    vertex2i(x, y);
  }
  public void vertex(short x, short y) {
    vertex2s(x, y);
  }

  private native void vertex3d(double x, double y, double z);
  private native void vertex3f(float x,  float y,  float z);
  private native void vertex3i(int x,    int y,    int z);
  private native void vertex3s(short x,  short y,   short z);

  public void vertex(double x, double y, double z) {
    vertex3d(x, y, z);
  }
  public void vertex(float x, float y, float z) {
    vertex3f(x, y, z);
  }
  public void vertex(int x, int y, int z) {
    vertex3i(x, y, z);
  }
  public void vertex(short x, short y, short z) {
    vertex3s(x, y, z);
  }

  private native void vertex4d(double x, double y, double z, double w);
  private native void vertex4f(float x,  float y,  float z,  float w);
  private native void vertex4i(int x,    int y,    int z,    int w);
  private native void vertex4s(short x,  short y,  short z,  short w);

  public void vertex(double x, double y, double z, double w) {
    vertex4d(x, y, z, w);
  }
  public void vertex(float x, float y, float z, float w) {
    vertex4f(x, y, z, w);
  }
  public void vertex(int x, int y, int z, int w) {
    vertex4i(x, y, z, w);
  }
  public void vertex(short x, short y, short z, short w) {
    vertex4s(x, y, z, w);
  }

  private native void normal3b(byte   nx, byte ny,   byte nz);
  private native void normal3d(double nx, double ny, double nz);
  private native void normal3f(float  nx, float ny,  float nz);
  private native void normal3i(int nx,    int ny,    int nz);
  private native void normal3s(short nx,  short ny,  short nz);

  public void normal(byte nx, byte ny, byte nz) {
    normal3b(nx, ny, nz);
  }
  public void normal(double nx, double ny, double nz) {
    normal3d(nx, ny, nz);
  }
  public void normal(float nx, float ny, float nz) {
    normal3f(nx, ny, nz);
  }
  public void normal(int nx, int ny, int nz) {
    normal3i(nx, ny, nz);
  }
  public void normal(short nx, short ny, short nz) {
    normal3s(nx, ny, nz);
  }

  private native void indexd(double c);
  private native void indexf(float c);
  private native void indexi(int c);
  private native void indexs(short c);

  public void index(double c) {
    indexd(c);
  }
  public void index(float c) {
    indexf(c);
  }
  public void index(int c) {
    indexi(c);
  }
  public void index(short c) {
    indexs(c);
  }

  private native void color3b(byte red,   byte green,   byte blue);
  private native void color3d(double red, double green, double blue);
  private native void color3f(float red,  float green,  float blue);
  private native void color3i(int red,    int green,    int blue);
  private native void color3s(short red,  short green,  short blue);

  public void color(byte red, byte green, byte blue) {
    color3b(red, green, blue);
  }
  public void color(double red, double green, double blue) {
    color3d(red, green, blue);
  }
  public void color(float red, float green, float blue) {
    color3f(red, green, blue);
  }
  public void color(int red, int green, int blue) {
    color3i(red, green, blue);
  }
  public void color(short red, short green, short blue) {
    color3s(red, green, blue);
  }


  private native void color4b(byte red,   byte green,   byte blue,   
			      byte alpha);
  private native void color4d(double red, double green, double blue, 
			      double alpha);
  private native void color4f(float red,  float green,  float blue,  
			      float alpha);
  private native void color4i(int red,    int green,    int blue,    
			      int alpha);
  private native void color4s(short red,  short green,  short blue,  
			      short alpha);

  public void color(byte red, byte green, byte blue, byte alpha) {
    color4b(red, green, blue, alpha);
  }
  public void color(double red, double green, double blue, double alpha) {
    color4d(red, green, blue, alpha);
  }
  public void color(float red, float green, float blue, float alpha) {
    color4f(red, green, blue, alpha);
  }
  public void color(int red, int green, int blue, int alpha) {
    color4i(red, green, blue, alpha);
  }
  public void color(short red, short green, short blue, short alpha) {
    color4s(red, green, blue, alpha);
  }

  private native void texCoord1d(double s);
  private native void texCoord1f(float s);
  private native void texCoord1i(int s);
  private native void texCoord1s(short s);
  
  public void texCoord(double s) {
    texCoord1d(s);
  }
  public void texCoord(float s) {
    texCoord1f(s);
  }
  public void texCoord(int s) {
    texCoord1i(s);
  }
  public void texCoord(short s) {
    texCoord1s(s);
  }

  private native void texCoord2d(double s, double t);
  private native void texCoord2f(float s, float t);
  private native void texCoord2i(int s, int t);
  private native void texCoord2s(short s, short t);

  public void texCoord(double s, double t) {
    texCoord2d(s, t);
  }
  public void texCoord(float s, float t) {
    texCoord2f(s, t);
  }
  public void texCoord(int s, int t) {
    texCoord2i(s, t);
  }
  public void texCoord(short s, short t) {
    texCoord2s(s, t);
  }

  private native void texCoord3d(double s, double t, double r);
  private native void texCoord3f(float s, float t, float r);
  private native void texCoord3i(int s, int t, int r);
  private native void texCoord3s(short s, short t, short r);

  public void texCoord(double s, double t, double r) {
    texCoord3d(s, t, r);
  }
  public void texCoord(float s, float t, float r) {
    texCoord3f(s, t, r);
  }
  public void texCoord(int s, int t, int r) {
    texCoord3i(s, t, r);
  }
  public void texCoord(short s, short t, short r) {
    texCoord3s(s, t, r);
  }

  private native void texCoord4d(double s, double t, double r, double q);
  private native void texCoord4f(float s, float t, float r, float q);
  private native void texCoord4i(int s, int t, int r, int q);
  private native void texCoord4s(short s, short t, short r, short q);

  public void texCoord(double s, double t, double r, double q) {
    texCoord4d(s, t, r, q);
  }
  public void texCoord(float s, float t, float r, float q) {
    texCoord4f(s, t, r, q);
  }
  public void texCoord(int s, int t, int r, int q) {
    texCoord4i(s, t, r, q);
  }
  public void texCoord(short s, short t, short r, short q) {
    texCoord4s(s, t, r, q);
  }

  private native void rasterPos2d(double x, double y);
  private native void rasterPos2f(float x, float y);
  private native void rasterPos2i(int x, int y);
  private native void rasterPos2s(short x, short y);
  
  public void rasterPos(double x, double y) {
    rasterPos2d(x, y);
  }
  public void rasterPos(float x, float y) {
    rasterPos2f(x, y);
  }
  public void rasterPos(int x, int y) {
    rasterPos2i(x, y);
  }
  public void rasterPos(short x, short y) {
    rasterPos2s(x, y);
  }

  private native void rasterPos3d(double x, double y, double z);
  private native void rasterPos3f(float x, float y, float z);
  private native void rasterPos3i(int x, int y, int z);
  private native void rasterPos3s(short x, short y, short z);

  public void rasterPos(double x, double y, double z) {
    rasterPos3d(x, y, z);
  }
  public void rasterPos(float x, float y, float z) {
    rasterPos3f(x, y, z);
  }
  public void rasterPos(int x, int y, int z) {
    rasterPos3i(x, y, z);
  }
  public void rasterPos(short x, short y, short z) {
    rasterPos3s(x, y, z);
  }


  private native void rasterPos4d(double x, double y, double z, double w);
  private native void rasterPos4f(float x, float y, float z, float w);
  private native void rasterPos4i(int x, int y, int z, int w);
  private native void rasterPos4s(short x, short y, short z, short w);
  
  public void rasterPos(double x, double y, double z, double w) {
    rasterPos4d(x, y, z, w);
  }
  public void rasterPos(float x, float y, float z, float w) {
    rasterPos4f(x, y, z, w);
  }
  public void rasterPos(int x, int y, int z, int w) {
    rasterPos4i(x, y, z, w);
  }
  public void rasterPos(short x, short y, short z, short w) {
    rasterPos4s(x, y, z, w);
  }

  
  private native void rectd(double x1, double y1, double x2, double y2);
  private native void rectf(float x1, float y1, float x2, float y2);
  private native void recti(int x1, int y1, int x2, int y2);
  private native void rects(short x1, short y1, short x2, short y2);
  
  public void rect(double x1, double y1, double x2, double y2) {
    rectd(x1, y1, x2, y2);
  }
  public void rect(float x1, float y1, float x2, float y2) {
    rectf(x1, y1, x2, y2);
  }
  public void rect(int x1, int y1, int x2, int y2) {
    recti(x1, y1, x2, y2);
  }
  public void rect(short x1, short y1, short x2, short y2) {
    rects(x1, y1, x2, y2);
  }


  /*
   * Vertex Arrays
   */ 

  /** This is going to need some work translating the object arrays
    into the void pointers that GL expects. */

  public native void vertexPointer(int size, int stride,
				   float ptr[]);
  public native void vertexPointer(int size, int stride,
				   double ptr[]);
  public native void vertexPointer(int size, int stride,
				   int ptr[]);
  public native void vertexPointer(int size, int stride,
				   short ptr[]);
  
  public native void normalPointer(int stride,
				   float ptr[]);
  public native void normalPointer(int stride,
				   double ptr[]);
  public native void normalPointer(int stride,
				   int ptr[]);
  public native void normalPointer(int stride,
				   short ptr[]);
  
  public native void colorPointer(int size, int type, int stride,
				  byte ptr[]);
  public native void colorPointer(int size, int type, int stride,
				   short ptr[]);
  public native void colorPointer(int size, int type, int stride,
				   int ptr[]);
  public native void colorPointer(int size, int type, int stride,
				   float ptr[]);
  public native void colorPointer(int size, int type, int stride,
				   double ptr[]);

  
  public native void indexPointer(int stride, byte ptr[]);
  public native void indexPointer(int stride, short ptr[]);
  public native void indexPointer(int stride, int ptr[]);
  public native void indexPointer(int stride, float ptr[]);
  public native void indexPointer(int stride, double ptr[]);
  
  public native void texCoordPointer(int size, int stride,
				     byte ptr[]);
  public native void texCoordPointer(int size, int stride,
				      short ptr[]);
  public native void texCoordPointer(int size, int stride,
				      int ptr[]);
  public native void texCoordPointer(int size, int stride,
				      float ptr[]);
  public native void texCoordPointer(int size, int stride,
				     double ptr[]);
  
  public native void edgeFlagPointer(int stride, boolean ptr[]);
  
  public native void getPointerv(int pname, Object params[][]);
  
  public native void arrayElement(int i);
  
  public native void drawArrays(int mode, int first, int count);
  
  public native void drawElements(int mode, int count,
				  byte indices[]);
  public native void drawElements(int mode, int count,
				  short indices[]);
  public native void drawElements(int mode, int count,
				  int indices[]);
  
  public native void interleavedArrays(int format, int stride,
				       Object pointer[]);

  /*
   * Lighting
   */


  public native void shadeModel(int mode);
  
  private native void lightf(int light, int pname, float param);
  private native void lighti(int light, int pname, int param);
  private native void lightfv(int light, int pname, float params[]);
  private native void lightiv(int light, int pname, int params[]);

  public void light(int light, int pname, float param) {
    lightf(light, pname, param);
  }
  public void light(int light, int pname, int param) {
    lighti(light, pname, param);
  }
  public void light(int light, int pname, float params[]) {
    lightfv(light, pname, params);
  }
  public void light(int light, int pname, int params[]) {
    lightiv(light, pname, params);
  }



  private native void getLightfv(int light, int pname, float params[]);
  private native void getLightiv(int light, int pname, int params[]);
  
  public void getLight(int light, int pname, float params[]) {
    getLightfv(light, pname, params);
  }
  public void getLight(int light, int pname, int params[]) {
    getLightiv(light, pname, params);
  }

  private native void lightModelf(int pname, float param);
  private native void lightModeli(int pname, int param);
  private native void lightModelfv(int pname, float params[]);
  private native void lightModeliv(int pname, int params[]);

  public void lightModel(int pname, float param) {
    lightModelf(pname, param);
  }
  public void lightModel(int pname, int param) {
    lightModel(pname, param);
  }
  public void lightModel(int pname, float params[]) {
    lightModelfv(pname, params);
  }
  public void lightModel(int pname, int params[]) {
    lightModeliv(pname, params);
  }

  private native void materialf(int face, int pname, float param);
  private native void materiali(int face, int pname, int param);
  private native void materialiv(int face, int pname, int params[]);
  private native void materialfv(int face, int pname, float params[]);

  public void material(int face, int pname, float param) {
    materialf(face, pname, param);
  }
  public void material(int face, int pname, int param) {
    materiali(face, pname, param);
  }
  public void material(int face, int pname, int params[]) {
    materialiv(face, pname, params);
  }
  public void material(int face, int pname, float params[]) {
    materialfv(face, pname, params);
  }

  
  private native void getMaterialfv( int face, int pname, float params[]);
  private native void getMaterialiv( int face, int pname, int params[]);
  
  public void getMaterial(int face, int pname, float params[]) {
    getMaterialfv(face, pname, params);
  }
  public void getMaterial(int face, int pname, int params[]) {
    getMaterialiv(face, pname, params);
  }

  public native void colorMaterial(int face, int mode );

/*
 * Raster functions
 */

  public native void pixelZoom(float xfactor, float yfactor);

  private native void pixelStoref(int pname, float param);
  private native void pixelStorei(int pname, int param);
  
  public void pixelStore(int pname, float param) {
    pixelStoref(pname, param);
  }
  public void pixelStore(int pname, int param) {
    pixelStorei(pname, param);
  }


  private native void pixelTransferf(int pname, float param);
  private native void pixelTransferi(int pname, int param);

  public void pixelTransfer(int pname, float param) {
    pixelTransferf(pname, param);
  }
  public void pixelTransfer(int pname, int param) {
    pixelTransferi(pname, param);
  }


  private native void pixelMapfv(int map, int mapsize, float values[]);
  public void pixelMap(int map, float values[]) {
    pixelMapfv(map, values.length, values);
  }
  private native void pixelMapuiv(int map, int mapsize, int values[]);
  private native void pixelMapusv(int map, int mapsize, short values[]);

  public void pixelMap(int map, int values[]) {
    pixelMapuiv(map, values.length, values);
  }
  public void pixelMap(int map, short values[]) {
    pixelMapusv(map, values.length, values);
  }

  private native void getPixelMapfv(int map, float values[]);
  private native void getPixelMapuiv(int map, int values[]);
  private native void getPixelMapusv(int map, short values[]);
    
  public void getPixelMap(int map, float values[]) {
      getPixelMapfv(map, values);
    }
  public void getPixelMap(int map, int values[]) {
    getPixelMapuiv(map, values);
  }
  public void getPixelMap(int map, short values[]) {
    getPixelMapusv(map, values);
  }

    

  public native void bitmap(int width, int height,
			    float xorig, float yorig,
			    float xmove, float ymove,
			    byte bitmap[]);
  
  public native Object readPixels(int x, int y, int width, int height,
				    int format, int type);
  
  public native void drawPixels(int width, int height,
				int format, int type, byte pixels[]);
  public native void drawPixels(int width, int height,
				int format, int type, short pixels[]);
  public native void drawPixels(int width, int height,
				int format, int type, int pixels[]);
  public native void drawPixels(int width, int height,
				int format, int type, float pixels[]);

  public native void copyPixels(int x, int y, int width, int height,
				int type);
  
  
  
  /*
   * Stenciling
   */
  
  public native void stencilFunc(int func, int ref, int mask);
  
  public native void stencilMask(int mask);
  
  public native void stencilOp(int fail, int zfail, int zpass);
  
  public native void clearStencil(int s);
  
  
  
  /*
   * Texture mapping
   */
  
  private native void texGend(int coord, int pname, double param);
  private native void texGenf(int coord, int pname, float param);
  private native void texGeni(int coord, int pname, int param);
  
  public void texGen(int coord, int pname, double param) {
    texGend(coord, pname, param);
  }
  public void texGen(int coord, int pname, float param) {
    texGenf(coord, pname, param);
  }
  public void texGen(int coord, int pname, int param) {
    texGeni(coord, pname, param);
  }
  
  private native void texGendv(int coord, int pname, double params[]);
  private native void texGenfv(int coord, int pname, float params[]);
  private native void texGeniv(int coord, int pname, int params[]);
  
  public void texGen(int coord, int pname, double params[]) {
    texGendv(coord, pname, params);
  }
  public void texGen(int coord, int pname, float params[]) {
    texGenfv(coord, pname, params);
  }
  public void texGen(int coord, int pname, int params[]) {
    texGeniv(coord, pname, params);
  }
  
  private native void getTexGendv(int coord, int pname, double params[]);
  private native void getTexGenfv(int coord, int pname, float params[]);
  private native void getTexGeniv(int coord, int pname, int params[]);
  
  public void getTexGen(int coord, int pname, double params[]) {
    getTexGendv(coord, pname, params);
  }
  public void getTexGen(int coord, int pname, float params[]) {
    getTexGenfv(coord, pname, params);
  }
  public void getTexGen(int coord, int pname, int params[]) {
    getTexGeniv(coord, pname, params);
  }

  /* TexEnv */
  private native void texEnvf(int target, int pname, float param);
  private native void texEnvi(int target, int pname, int param);
  private native void texEnvfv(int target, int pname, float params[]);
  private native void texEnviv(int target, int pname, int params[]);
  
  public void texEnv(int target, int pname, float param) {
    texEnvf(target, pname, param);
    }
  public void texEnv(int target, int pname, int param) {
    texEnvi(target, pname, param);
  }
  public void texEnv(int target, int pname, float params[]) {
    texEnvfv(target, pname, params);
  }
  public void texEnv(int target, int pname, int params[]) {
    texEnviv(target, pname, params);
  }
  
  /* GetTexEnv */
  private native void getTexEnvfv(int target, int pname, float params[]);
  private native void getTexEnviv(int target, int pname, int params[]);
  
  public void getTexEnv(int target, int pname, float params[]) {
    getTexEnvfv(target, pname, params);
  }
  public void getTexEnv(int target, int pname, int params[]) {
    getTexEnviv(target, pname, params);
  }

  /* TexParameter */
  private native void texParameterf(int target, int pname, float param);
  private native void texParameteri(int target, int pname, int param);
  private native void texParameterfv(int target, int pname,
				     float params[]);
  private native void texParameteriv(int target, int pname,
				     int params[]);
  public void texParameter(int target, int pname, float param) {
    texParameterf(target, pname, param);
  }
  public void texParameter(int target, int pname, int param) {
    texParameteri(target, pname, param);
  }
  public void texParameter(int target, int pname, float params[]) {
    texParameterfv(target, pname, params);
  }
  public void texParameter(int target, int pname, int params[]) {
    texParameteriv(target, pname, params);
  }

  /* GetTexParameter */
  private native void getTexParameterfv(int target, int pname, 
					float params[]);
  private native void getTexParameteriv(int target, int pname, 
					int params[]);

  public void getTexParameter(int target, int pname, float params[]) {
    getTexParameterfv(target, pname, params);
  }
  public void getTexParameter(int target, int pname, int params[]) {
    getTexParameteriv(target, pname, params);
  }

  private native void getTexLevelParameterfv(int target, int level,
					     int pname, float params[]);
  private native void getTexLevelParameteriv(int target, int level,
					     int pname, int params[]);

  public void getTexLevelParameter(int target, int level,
				   int pname, float params[]) {
    getTexLevelParameterfv(target, level, pname, params);
  }
  public void getTexLevelParameter(int target, int level,
				   int pname, int params[]) {
    getTexLevelParameteriv(target, level, pname, params);
  }

  /* TexImage1D */
  public native void texImage1D(int target, int level, int components,
				int width, int border,
				int format, int type, byte pixels[]);
  public native void texImage1D(int target, int level, int components,
				int width, int border,
				int format, int type, short pixels[]);
  public native void texImage1D(int target, int level, int components,
				int width, int border,
				int format, int type, int pixels[]);
  public native void texImage1D(int target, int level, int components,
				int width, int border,
				int format, int type, float pixels[]);

  /* TexImage2D */
  public native void texImage2D(int target, int level, int components,
				int width, int height, int border,
				int format, int type, byte pixels[]);
  public native void texImage2D(int target, int level, int components,
				int width, int height, int border,
				int format, int type, short pixels[]);
  public native void texImage2D(int target, int level, int components,
				int width, int height, int border,
				int format, int type, int pixels[]);
  public native void texImage2D(int target, int level, int components,
				int width, int height, int border,
				int format, int type, float pixels[]);

  /* GetTexImage */
  public native void getTexImage(int target, int level, int format,
				 int type, byte pixels[]);
  public native void getTexImage(int target, int level, int format,
				 int type, short pixels[]);
  public native void getTexImage(int target, int level, int format,
				 int type, int pixels[]);
  public native void getTexImage(int target, int level, int format,
				 int type, float pixels[]);
  


  /* 1.1 functions */

  public native void genTextures(int textures[]);

  public native void deleteTextures(int textures[]);
  
  public native void bindTexture(int target, int texture);
  
  public native void prioritizeTextures(int textures[],
					float priorities[]);
  
  public native boolean areTexturesResident(int textures[],
					    boolean residences[]);
  
  public native boolean isTexture(int texture);
  

  /* TexSubImage1D */
  public native void texSubImage1D(int target, int level, int xoffset,
				   int width, int format,
				   int type, byte pixels[]);
  public native void texSubImage1D(int target, int level, int xoffset,
				   int width, int format,
				   int type, short pixels[]);
  public native void texSubImage1D(int target, int level, int xoffset,
				   int width, int format,
				   int type, int pixels[]);
  public native void texSubImage1D(int target, int level, int xoffset,
				   int width, int format,
				   int type, float pixels[]);

  /* TexSubImage2D */
  public native void texSubImage2D(int target, int level,
				   int xoffset, int yoffset,
				   int width, int height,
				   int format, int type,
				   byte pixels[]);
  public native void texSubImage2D(int target, int level,
				   int xoffset, int yoffset,
				   int width, int height,
				   int format, int type,
				   short pixels[]);
  public native void texSubImage2D(int target, int level,
				   int xoffset, int yoffset,
				   int width, int height,
				   int format, int type,
				   int pixels[]);
  public native void texSubImage2D(int target, int level,
				   int xoffset, int yoffset,
				   int width, int height,
				   int format, int type,
				   float pixels[]);

  /* CopyTexImage1D */
  public native void copyTexImage1D(int target, int level,
				    int internalformat,
				    int x, int y,
				    int width, int border);
  
  
  public native void copyTexImage2D(int target, int level,
				    int internalformat,
				    int x, int y,
				    int width, int height, int border);
  
  
  public native void copyTexSubImage1D(int target, int level,
				       int xoffset, int x, int y,
				       int width);
  

  public native void copyTexSubImage2D(int target, int level,
				       int xoffset, int yoffset,
				       int x, int y,
				       int width, int height);




  /*
   * Evaluators
   */

  private native void map1d(int target, double u1, double u2, int stride,
			    int order, double points[]);
  private native void map1f(int target, float u1, float u2, int stride,
			    int order, float points[]);
  
  public void map1(int target, double u1, double u2, int stride,
		   int order, double points[]) {
    map1d(target, u1, u2, stride, order, points);
  }
  public void map1(int target, float u1, float u2, int stride,
		   int order, float points[]) {
    map1f(target, u1, u2, stride, order, points);
  }
  
  private native void map2d(int target,
			    double u1, double u2, int ustride, int uorder,
			    double v1, double v2, int vstride, int vorder,
			    double points[]);
  private native void map2f(int target,
			    float u1, float u2, int ustride, int uorder,
			    float v1, float v2, int vstride, int vorder,
			    float points[]);
  
  public void map2(int target,
		   float u1, float u2, int ustride, int uorder,
		   float v1, float v2, int vstride, int vorder,
		   float points[]) {
    map2f(target, u1, u2, ustride, uorder, 
	  v1, v2, vstride, vorder, points);
  }
  public void map2(int target,
		   float u1, float u2, int ustride, int uorder,
		   float v1, float v2, int vstride, int vorder,
		   double points[]) {
    map2d(target, u1, u2, ustride, uorder, 
	  v1, v2, vstride, vorder, points);
  }
  
  
  private native void getMapdv(int target, int query, double v[]);
  private native void getMapfv(int target, int query, float v[]);
  private native void getMapiv(int target, int query, int v[]);
  
  public void getMap(int target, int query, double v[]) {
    getMapdv(target, query, v);
  }
  public void getMap(int target, int query, float v[]) {
    getMapfv(target, query, v);
  }
  public void getMap(int target, int query, int v[]) {
    getMapiv(target, query, v);
  }
  
  
  private native void evalCoord1d(double u);
  private native void evalCoord1f(float u);
  private native void evalCoord2d(double u, double v);
  private native void evalCoord2f(float u, float v);
  
  public void evalCoord(double u) {
    evalCoord1d(u);
  }
  public void evalCoord(float u) {
    evalCoord1f(u);
  }
  public void evalCoord(double u, double v) {
    evalCoord2d(u, v);
  }
  public void evalCoord(float u, float v) {
    evalCoord2f(u, v);
  }
  
  private native void mapGrid1d(int un, double u1, double u2);
  private native void mapGrid1f(int un, float u1, float u2);
  private native void mapGrid2d(int un, double u1, double u2,
				int vn, double v1, double v2);
  private native void mapGrid2f(int un, float u1, float u2,
				int vn, float v1, float v2);
  
  public void mapGrid(int un, double u1, double u2) {
    mapGrid1d(un, u1, u2);
  }
  public void mapGrid(int un, float u1, float u2) {
    mapGrid1f(un, u1, u2);
  }
  public void mapGrid(int un, double u1, double u2,
		      int vn, double v1, double v2) {
    mapGrid2d(un, u1, u2, vn, v1, v2);
  }
  public void mapGrid(int un, float u1, float u2,
		      int vn, float v1, float v2) {
    mapGrid2f(un, u1, u2, vn, v1, v2);
  }
  
  private native void evalPoint1(int i);
  private native void evalPoint2(int i, int j);
  
  public void evalPoint(int i) {
    evalPoint1(i);
  }
  public void evalPoint(int i, int j) {
    evalPoint2(i, j);
  }
  
  private native void evalMesh1(int mode, int i1, int i2);
  private native void evalMesh2(int mode, int i1, int i2, int j1, int j2);
  
  public void evalMesh(int mode, int i1, int i2) {
    evalMesh1(mode, i1, i2);
  }
  public void evalMesh(int mode, int i1, int i2, int j1, int j2) {
    evalMesh2(mode, i1, i2, j1, j2);
  }
  
  
  /*
   * Fog
   */
  private native void fogf(int pname, float param);
  private native void fogi(int pname, int param);
  private native void fogfv(int pname, float params[]);
  private native void fogiv(int pname, int params[]);
  
  
  public void fog(int pname, float param) {
    fogf(pname, param);
  }
  public void fog(int pname, int param) {
    fogi(pname, param);
  }
  public void fog(int pname, float params[]) {
    fogfv(pname, params);
  }
  public void fog(int pname, int params[]) {
    fogiv(pname, params);
  }



  /*
   * Selection and Feedback
   */

  /* The normal GL size parameter is derived from buffer.size */
  public native void feedbackBuffer(int type, float buffer[]);

  public native void passThrough(float token);

  public native void selectBuffer(int buffer[]);

  public native void initNames();

  public native void loadName(int name);

  public native void pushName(int name);

  public native void popName();



  /** 1.0 Extensions. These extension functions are here for reference
   * only right now --- they are not implemented.  */

  /* GL_EXT_blend_minmax */
  public native void blendEquationEXT(int mode);



  /* GL_EXT_blend_color */
  public native void blendColorEXT(float red, float green,
				   float blue, float alpha);
  
  
  
  /* GL_EXT_polygon_offset */
  public native void polygonOffsetEXT(float factor, float bias);
  


  /* GL_EXT_vertex_array */
  
  public native void vertexPointerEXT(int size, int type, int stride,
				      int count, Object ptr[]);
  
  public native void normalPointerEXT(int type, int stride,
				      int count, Object ptr[]);
  
  public native void colorPointerEXT(int size, int type, int stride,
				     int count, Object ptr[]);
  
  public native void indexPointerEXT(int type, int stride,
				     int count, Object ptr[]);
  
  public native void texCoordPointerEXT(int size, int type, int stride,
					int count, Object ptr[]);
  
  public native void edgeFlagPointerEXT(int stride,
					int count,  boolean ptr[]);
  
  public native void getPointervEXT(int pname, Object params[][]);
  
  public native void arrayElementEXT(int i);
  
  public native void drawArraysEXT(int mode, int first, int count);


  /*
   * GLU methods
   * 
   */

  public native void gluLookAt(double eyeX,    double eyeY,    double eyeZ,
			       double centerX, double centerY, double centerZ,
			       double upX,     double upY,    double upZ);

  public native void gluOrtho2D(double left, double right,
				double bottom, double top);

  public native void gluPerspective(double fovy, double aspect,
				 double zNear, double zFar);

  public native void gluPickMatrix(double x, double y,
				   double width, double height,
				   int viewport[]);

  /** Unlike the native GLUT project function, we return the window
      coordinates in an array of three doubles. */
  public native void gluProject(double objx, double objy, double objz,
				double modelMatrix[],
				double projMatrix[],
				int viewport[],
				double win[]);

  /** Unlike the native GLUT project function, we return the object
      coordinates in an array of three doubles. */
  public native void gluUnProject(double winx, double winy, double winz,
				  double modelMatrix[],
				  double projMatrix[],
				  int viewport[],
				  double obj[]);


  public native String gluErrorString(int errorCode);



/*
 *
 * Mipmapping and image scaling
 *
 */
  /** The parameters datain and dataout should be arrays pointing to the 
    input image and the output image. */
  public native int gluScaleImage(int format,
				  int widthin, int heightin,
				  int typein, Object datain,
				  int widthout, int heightout,
				  int typeout, Object dataout);

  public native int gluBuild1DMipmaps(int target, int components,
				      int width, int format,
				      int type, byte data[]);

  public native int gluBuild1DMipmaps(int target, int components,
				      int width, int format,
				      int type, short data[]);

  public native int gluBuild1DMipmaps(int target, int components,
				      int width, int format,
				      int type, int data[]);

  public native int gluBuild1DMipmaps(int target, int components,
				      int width, int format,
				      int type, float data[]);

  public native int gluBuild2DMipmaps(int target, int components,
				      int width, int height, int format,
				      int type, byte data[]);

  public native int gluBuild2DMipmaps(int target, int components,
				      int width, int height, int format,
				      int type, short data[]);

  public native int gluBuild2DMipmaps(int target, int components,
				      int width, int height, int format,
				      int type, int data[]);

  public native int gluBuild2DMipmaps(int target, int components,
				      int width, int height, int format,
				      int type, float data[]);


/*
 *
 * New functions in GLU 1.1
 *
 */

  public native String gluGetString( int name );

}



