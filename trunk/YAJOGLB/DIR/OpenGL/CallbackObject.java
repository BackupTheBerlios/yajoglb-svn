/*
 * CallbackObject
 *
 * $Id: CallbackObject.java,v 1.3 2002/07/21 16:55:16 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

package OpenGL;

import java.util.Hashtable;
import java.lang.reflect.*;

/*
 * CallbackObject is the base class for classes that need to support
 * the C callbacks in the GLU library.  It allows the native to obtain
 * the environment pointer for a given thread, provided that some
 * of our functions are called.
 *
 * The CHeapObject is extended to provide this functionality because
 * all the classes that need to use it are also objects on the C heap.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.3
 */
 
abstract class CallbackObject extends CHeapItem {
  /** Allow the native library to record the current environment pointer
      so that it can use it in the tesselator call back methods. */
  synchronized static native void setEnvironmentPointer();
  /** Allow the native library to release its environment pointer. */
  synchronized static native void unsetEnvironmentPointer();

  /** Get the callback hash table.  This should be overridden by our
   subclasses to return a hash table for each subclass.  For example,
   <code>GLUTesselators</code> should return one hash table and
   <code>GLUQuadrics</code> another. 
   @return always returns null.  */
  static protected Hashtable getActiveCallbackDictionary() {
    return null;
  }
  
  /** This attempts to get the static callback dictionary method for
      ourClass.  It does this by searching through ourClass and its
      super classes for a method name getActiveCallbackDictionary.  If the
      method can not be found null is returned.
      @param ourClass the class to start searching for <code>getActiveCallbackDictionary</code>.
      @return the active callback dictionary method for this. */
  static private Method getActiveCallbackDictionaryMethod(Class ourClass) {
    Method activeCallbackDictionaryMethod = null;

    /* Loop through all of our super classes, looking for the
	<code>getActiveCallbackDictionary</code> method.  The
	<code>getDeclaredMethod</code> method only returns methods
	actually declared in the class it is invoked from, which is
	why we need to loop. */
    while((null == activeCallbackDictionaryMethod) && 
	  (null != ourClass)) {
      try {
	activeCallbackDictionaryMethod = 
	  ourClass.getDeclaredMethod("getActiveCallbackDictionary",
				     new Class[0]);
      } catch (java.lang.NoSuchMethodException exception) {
	ourClass = ourClass.getSuperclass();
      }
    }
    
    return activeCallbackDictionaryMethod;
  }

  /** Set this tesselator as the active tesselator for the current
      thread, and call <code>setEnvironmentPointer</code> It should be
      called after every native method returns.  This prevents the
      native library from getting the wrong idea about what the
      current tesselator is, and from dangling references. */
  protected void setActiveCallbackObject() {
    setEnvironmentPointer();
    Hashtable activeCallbackDictionary = null;

    try {
      Method getActiveCallbackDictionary;

      getActiveCallbackDictionary = getActiveCallbackDictionaryMethod(getClass());
      activeCallbackDictionary = (Hashtable)
	getActiveCallbackDictionary.invoke(null, new Object[0]);
    } catch (java.lang.IllegalAccessException exception) {
      throw new IllegalStateException("Unable to invoke the getActiveCallbackDictionary method because of the following exception: " + exception);
    } catch (java.lang.reflect.InvocationTargetException exception) {
      throw new IllegalStateException("Unable to invoke getActiveCallbackDictionary method because of the following exception: " + exception);
    }
    activeCallbackDictionary.put(Thread.currentThread(), this);
  }

  /** Remove this object as the active callback object for the current
      thread. */
  protected void unsetActiveCallbackObject() {
    Hashtable activeCallbackDictionary = null;
    try {
      Method getActiveCallbackDictionary;

      getActiveCallbackDictionary = getActiveCallbackDictionaryMethod(getClass());
      activeCallbackDictionary = (Hashtable)
	getActiveCallbackDictionary.invoke(null, new Object[0]);
    } catch (java.lang.IllegalAccessException exception) {
      throw new IllegalStateException("Unable to invoke the getActiveCallbackDictionary method because of the following exception: " + exception);
    } catch (java.lang.reflect.InvocationTargetException exception) {
      throw new IllegalStateException("Unable to invoke getActiveCallbackDictionary method because of the following exception: " + exception);
    }
      
    activeCallbackDictionary.remove(Thread.currentThread());
    // If we do not care about the active callback we do not need
    // the environment for it either.
    unsetEnvironmentPointer();
  }


  /** Returns the active object for the current thread.  This is
      used by the native library.
      @param ourClass the class of callback object we should search for.
      @throws OpenGLNativeException if className does not exist.
      @return the active object for the current thread. */
  static protected CallbackObject activeCallbackObjectForThread(Class ourClass) {
    CallbackObject activeObject;

    Hashtable activeCallbackDictionary = null;
    try {
      Method getActiveCallbackDictionary;
      getActiveCallbackDictionary = getActiveCallbackDictionaryMethod(ourClass);
      activeCallbackDictionary = (Hashtable) getActiveCallbackDictionary.invoke(null, new Object[0]);
    } catch (java.lang.IllegalAccessException exception) {
      throw new IllegalStateException("Unable to invoke the getActiveCallbackDictionary method because of the following exception: " + exception);
    } catch (java.lang.reflect.InvocationTargetException exception) {
      throw new IllegalStateException("Unable to invoke getActiveCallbackDictionary method because of the following exception: " + exception);
    }
    
    activeObject = (CallbackObject) activeCallbackDictionary.get(Thread.currentThread());
    if (null == activeObject) {
      throw new IllegalStateException("Unable to obtain an active callback object for this thread.");
    }
    return activeObject;
 }
}
