/*
  Describes an OpenGL context.
 
  Copyright 2001, Robert Allan Zeh (razeh@yahoo.com)
  7346 Lake Street #3W
  River Forest, IL 60305
 
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA

*/

/*
 * OpenGL.Context
 *
 * $Id$
 *
 */

package OpenGL;

import java.util.Hashtable;

/**
 *
 * This is used to control and represent the state of our OpenGL
 * context.  An OpenGL context is automatically created when we create
 * an OpenGL.Context object and automatically destroyed when the object
 * is finalized. <P>
 * 
 * Things aren't as clean as I would like because OpenGL contexts need
 * to be associated with particular windows, which requires a bit of
 * contortion when we try to create an OpenGL.Context. <P>
 *
 * OpenGL contexts may not be shared across threads.  You can enforce
 * this requirement by always locking an OpenGL before making it the
 * current context and unlocking it when you are done with it. <P>
 * 
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.4
 */

public class Context extends CHeapItem
{
    /** Make sure that we load in our native library. */
    static {
	NativePackageLoader.loadNativeLibrary();
    }

    /* These strings are used as keys inside of the hash table we pass
     around our constructors. */
    private static final String WIDGET  = "OpenGLWidget";
    private static final String CONTEXT = "Context";
    private static final String CANVAS  = "Canvas";

    /** This private routine is used to pass a constructed hash table 
      to our super construction method. */
    static private Hashtable startingArgs(Canvas canvas) {
	Hashtable optionalArguments = new Hashtable();
	optionalArguments.put(CANVAS, canvas);
	return optionalArguments;
    }
  
    /** This private routine is used so that we can pass a constructed
      hash table to our super construction method. */
    static private Hashtable startingArgs(Canvas canvas, 
					  Context context) {
	Hashtable optionalArguments = new Hashtable();
	optionalArguments.put(CANVAS, canvas);
	optionalArguments.put(CONTEXT, context);
	return optionalArguments;
    }

    /** Constructs a Context that will draw into an OpenGL.Canvas.
   * @param canvas the canvas to draw into.
   */
    public Context(Canvas canvas) {
	super(startingArgs(canvas));
    }

    /** Constructs a Context that will draw into an OpenGL.Canvas
   * and share its display list with context.
   *
   * @param canvas the canvas to draw into.
   * @param context the OpenGL.Context to share display lists with. */
    public Context(Canvas canvas,
		   Context context) {
	super(startingArgs(canvas, context));
    }

    /** This method should release the current context, setting
      things up so that we no longer have an OpenGL context. */
    static private native void nativeReleaseCurrentContext();

    /** This releases the current context, leaving us without a context. */
    static public void releaseCurrentContext() {
	nativeReleaseCurrentContext();
    }

    /** Make the supplied context pointer the current context for canvas. */
    private native void makeCanvasCurrent(long context, Canvas canvas);

    /** Makes this context the current context for the supplied
   * canvas. All future OpenGL rendering will be done inside of
   * canvas, and with this context's state.  
   * 
   * @param canvas the OpenGL.Canvas we should start drawing into.*/
    public void makeCurrent(Canvas canvas) {
	makeCanvasCurrent(getHeapPointer(), canvas);
    }



    /** This creates an OpenGL context for the given canvas. */
    private native long createCanvasContext(Canvas canvas, long context);


    /** This is used to allocate our OpenGL context. */
    protected long obtainCHeapItem(Hashtable optionalArguments) {
	Context context = (Context) optionalArguments.get(CONTEXT);
	Canvas  canvas  = (Canvas)  optionalArguments.get(CANVAS);
    
	if ((context != null) && (canvas != null)) 
	    return createCanvasContext(canvas, context.getHeapPointer());

	if (canvas != null)
	    return createCanvasContext(canvas, 0);

	return 0;
    }


    /** This deletes the supplied context. */
    private native void deleteContext(long context);
  
    /** This is used to free our OpenGL context. */
    protected void freeCHeapItem(long heapItem) {
	deleteContext(getHeapPointer());
    }

    /** The contextLockCount holds the number of unlock requests that
      need to be made before the current OpenGL.Context is unlocked.  */
    private int contextLockCount = 0;
    /** The thread that has this OpenGL.Context locked is stored in
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
		IllegalStateException("Attempting to unlock an unlocked OpenGL.Context.");
	}

	if (contextLocker != java.lang.Thread.currentThread()) {
	    throw new 
		IllegalThreadStateException("Attempting to unlock an OpenGL.Context locked by another thread.");
	}

	contextLockCount--;

	if (contextLockCount == 0) {
	    Context.releaseCurrentContext();
	    notify();
	    contextLocker = null;
	}
    }

	/*
	 switches sync to vertical blank on/off
	 */
	private native void nativeSyncToVBL(long context, boolean aFlag);
	public void syncToVBL(boolean aFlag) {
		nativeSyncToVBL(getHeapPointer(), aFlag);
	}
	
	/*
	 swap or flush the backbuffer to front
	 */
	private native void nativeFlushBuffer(long context);
    public void flushBuffer() {
		nativeFlushBuffer(getHeapPointer());
    }
}



