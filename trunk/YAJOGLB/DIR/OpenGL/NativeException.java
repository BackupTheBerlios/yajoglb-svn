/*
 * OpenGLNativeException class
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/** This exception is thrown when something goes wrong with in the
    native portion of our package. */

public class OpenGLNativeException extends java.lang.RuntimeException {
  OpenGLNativeException() {
    super();
  }
  OpenGLNativeException(String message) {
    super(message);
  }

}
