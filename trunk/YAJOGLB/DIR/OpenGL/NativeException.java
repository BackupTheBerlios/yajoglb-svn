/*
 * OpenGLNativeException class
 *
 * $Id: NativeException.java,v 1.3 1999/04/29 01:17:14 razeh Exp $
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
  * @version 0.3
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
