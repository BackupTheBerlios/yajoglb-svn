/*
 *
 * OpenGLContextException class
 *
 * $Id: ContextException.java,v 1.1 1998/09/10 01:01:22 razeh Exp $
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
 * @version 0.1
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
