/*
 * OpenGLContext
 *
 * $Id: Context.java,v 1.1 1998/09/10 01:01:14 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

import java.util.Hashtable;

/**
 *
 * This is used to control and represent the state of our OpenGL
 * context.  An OpenGL context is automatically created when we create
 * an OpenGLContext object and automatically destroyed when the object
 * is finalized. <P>
 * 
 * Things aren't as clean as I would like because OpenGL contexts need
 * to be associated with particular windows, which requires a bit of
 * contortion when we try to create an OpenGLContext. <P>
 *
 * OpenGL contexts may not be shared across threads.  You can enforce
 * this requirement by always locking an OpenGL before making it the
 * current context and unlocking it when you are done with it. <P>
 * 
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1 */

public class OpenGLContext extends CHeapItem
{
  /* These strings are used as keys inside of the hash table we pass
     around our constructors. */
  static final String WIDGET  = "OpenGLWidget";
  static final String CONTEXT = "OpenGLContext";
  static final String CANVAS  = "OpenGLCanvas";

  /** This private routine is used so that we can pass a constructed
      hash table to our super construction method. */
  static private Hashtable startingArgs(OpenGLWidget widget) {
    Hashtable optionalArguments = new Hashtable();
    optionalArguments.put(WIDGET, widget);
    return optionalArguments;
  }

  /** This private routine is used to pass a constructed hash table 
      to our super construction method. */
  static private Hashtable startingArgs(OpenGLCanvas canvas) {
    Hashtable optionalArguments = new Hashtable();
    optionalArguments.put(CANVAS, canvas);
    return optionalArguments;
  }
  
  /** This private routine is used so that we can pass a constructed
      hash table to our super construction method. */
  static private Hashtable startingArgs(OpenGLWidget widget, 
					OpenGLContext context) {
    Hashtable optionalArguments = new Hashtable();
    optionalArguments.put(WIDGET, widget);
    optionalArguments.put(CONTEXT, context);
    return optionalArguments;
  }

  /** This private routine is used so that we can pass a constructed
      hash table to our super construction method. */
  static private Hashtable startingArgs(OpenGLCanvas widget, 
					OpenGLContext context) {
    Hashtable optionalArguments = new Hashtable();
    optionalArguments.put(CANVAS, widget);
    optionalArguments.put(CONTEXT, context);
    return optionalArguments;
  }

  /** Constructs an OpenGLContext that will draw into widget. 
   * @param widget the OpenGLWidget to draw into. */
  public OpenGLContext(OpenGLWidget widget) {
    super(startingArgs(widget));
  }

  /** This creates an OpenGLContext attached to widget that shares its
   * display lists with context.
   * 
   * @param widget the widget to draw into.  
   * @param context the OpenGLContext to share display lists with. */
  public OpenGLContext(OpenGLWidget widget, OpenGLContext context) {
    super(startingArgs(widget, context));
  }

  /** Constructs an OpenGLContext that will draw into an OpenGLCanvas.
   * @param canvas the canvas to draw into.
   */
  public OpenGLContext(OpenGLCanvas canvas) {
    super(startingArgs(canvas));
  }

  /** Constructs an OpenGLContext that will draw into an OpenGLCanvas
   * and share its display list with context.
   *
   * @param canvas the canvas to draw into.
   * @param context the OpenGLContext to share display lists with. */
  public OpenGLContext(OpenGLCanvas canvas,
		       OpenGLContext context) {
    super(startingArgs(canvas, context));
  }

  /** This method should release the current context, setting
      things up so that we no longer have an OpenGL context. */
  static private native void nativeReleaseCurrentContext();

  /** This releases the current context, leaving us without a context. */
  static public void releaseCurrentContext() {
    nativeReleaseCurrentContext();
  }

  /** Make the supplied context pointer the current context for
      widget. */
  private native void makeCurrent(int context, OpenGLWidget widget);

  /** Makes this context the current context for the supplied
   * widget. All future OpenGL rendering will be done inside of
   * widget, and with this context's state.  
   * 
   * @param widget the OpenGLWidget we should start drawing into.*/
  public void makeCurrent(OpenGLWidget widget) {
    makeCurrent(heapPointer(), widget);
  }



  /** Make the supplied context pointer the current context for canvas. */
  private native void makeCanvasCurrent(int context, OpenGLCanvas canvas);

  /** Makes this context the current context for the supplied
   * canvas. All future OpenGL rendering will be done inside of
   * canvas, and with this context's state.  
   * 
   * @param canvas the OpenGLCanvas we should start drawing into.*/
  public void makeCurrent(OpenGLCanvas canvas) {
    makeCanvasCurrent(heapPointer(), canvas);
  }



  /** This creates an OpenGL context for the given canvas. */
  private native int createCanvasContext(OpenGLCanvas canvas, int context);


  /** This creates an OpenGL Context for the given widget. */
  private native int createContext(OpenGLWidget widget, int context);

  /** This is used to allocate our OpenGL context. */
  protected int obtainCHeapItem(Hashtable optionalArguments) {
    OpenGLWidget  widget  = (OpenGLWidget)  optionalArguments.get(WIDGET);
    OpenGLContext context = (OpenGLContext) optionalArguments.get(CONTEXT);
    OpenGLCanvas  canvas  = (OpenGLCanvas)  optionalArguments.get(CANVAS);
    
    if ((context != null) && (widget != null))
      return createContext(widget, context.heapPointer());
    
    if ((context != null) && (canvas != null))
      return createCanvasContext(canvas, context.heapPointer());

    if (widget != null) 
      return createContext(widget, 0);

    if (canvas != null)
      return createCanvasContext(canvas, 0);

    return 0;
  }



  /** This deletes the supplied context. */
  private native void deleteContext(int context);
  
  /** This is used to free our OpenGL context. */
  protected void freeCHeapItem(int heapItem) {
    deleteContext(heapPointer());
  }

  /** The contextLockCount holds the number of unlock requests that
      need to be made before the current OpenGLContext is unlocked.  */
  private int contextLockCount = 0;
  /** The thread that has this OpenGLContext locked is stored in
      contextLocker. */
  private Thread contextLocker = null;

  /** This method obtains a blocking lock on the context.  If our
   * wait() for the unlock is interrupted (with an
   * InterruptedException) we just keep waiting.  If a single thread
   * locks a context multiple times, it must unlock the context the
   * same number of times to really unlock it. */
  synchronized public void lock() {
    Thread currentThread = java.lang.Thread.currentThread();

    while((contextLockCount > 0) && (contextLocker != currentThread)) {
      try {
	wait();
      } catch (InterruptedException e) {
      }
    }

    contextLocker = currentThread;
    contextLockCount++;
  }

  /** This attempts to unlock and release the context.  If another
   * thread has the context locked we will wait until it releases the
   * lock.  If the context has been locked by the current thread
   * multiple times unlock must be called once for each lock before
   * taking effect. */
  synchronized public void unlock() {
    Thread currentThread = java.lang.Thread.currentThread();

    if (contextLockCount == 0) {
      throw new 
	IllegalStateException("Attempting to unlock an unlocked OpenGLContext");
    }

    if (contextLocker != java.lang.Thread.currentThread()) {
      throw new 
	IllegalThreadStateException("Attempting to unlock an OpenGLContext locked by another thread");
    }

    contextLockCount--;

    if (contextLockCount == 0) {
      OpenGLContext.releaseCurrentContext();
      notify();
      contextLocker = null;
    }
  }
}



