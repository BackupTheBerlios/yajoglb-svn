/*
 * OpenGLNativeException class
 *
 * $Id: NativeException.java,v 1.2 1998/09/10 01:01:59 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/** Signals that something has gone wrong inside of the native portion
  * of our package.
  * 
  * @author Robert Allan Zeh (razeh@balr.com)
  *
  * @version 0.1 
  */

public class OpenGLNativeException extends java.lang.RuntimeException {
  /** Constructs an <code>OpenGLNativeException</code> without a detail message. */
  OpenGLNativeException() {
    super();
  }
  /** Constructs an <code>OpenGLNativeException</code> with a detail message. 
    @param message detail message. */
  OpenGLNativeException(String message) {
    super(message);
  }

}
