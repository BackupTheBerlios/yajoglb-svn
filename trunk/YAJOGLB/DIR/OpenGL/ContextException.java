/*
 *
 * OpenGLContextException class
 *
 * $Id: ContextException.java,v 1.2 1999/04/29 01:17:14 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 */

package OpenGL;

/** Signals an error with our OpenGL context.  The most common error is attempting to make a context current while it is being used by another thread.
 * 
 * @author Robert Allan Zeh (razeh@balr.com)
 * 
 * @version 0.3
 */

class OpenGLContextException extends OpenGLNativeException {
  /** Constructs an <code>OpenGLContextException</code> with no message. */
  public OpenGLContextException() {
    super();
  }

  /** Constructs an <code>OpenGLContextException</code> with a detail message. 
   *  @param message the detail message
   */
  public OpenGLContextException(String message) {
    super(message);
  }
}
