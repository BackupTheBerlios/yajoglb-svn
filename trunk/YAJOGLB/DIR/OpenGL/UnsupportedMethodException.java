/*
 *
 * OpenGLUnsupportedMethodException class
 *
 * $Id: UnsupportedMethodException.java,v 1.1 1999/04/29 01:17:39 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 */

package OpenGL;

/** Thrown when we tried to call an OpenGL or GLU function that isn't
 * supported by our native OpenGL implementation.  For example, Mesa 3.0
 * only implements GLU 1.1, so the NURBS callback functions are not
 * implemented.
 * @author Robert Allan Zeh (razeh@balr.com)
 * 
 * @version 0.3
 */


public class OpenGLUnsupportedMethodException extends OpenGLNativeException {

  /** Constructs an <code> OpenGLUnsupportedMethodException </code>
      with no message. */
  OpenGLUnsupportedMethodException() {
    super();
  }
  
  /** Constructs an <code> OpenGLUnsupportedMethodException
   </code> with the specified detail message.  
   @param message message the detail message.*/
  OpenGLUnsupportedMethodException(String message) {
    super(message);
  }
}
