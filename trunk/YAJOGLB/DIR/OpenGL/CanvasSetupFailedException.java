/*
 * OpenGLCanvasSetupFailedException class
 *
 * $Id: CanvasSetupFailedException.java,v 1.1 1998/03/16 00:00:59 razeh Exp $
 *
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/** This exception is thrown when we have trouble setting up an OpenGLCanvas.
 
    @author Robert Allan Zeh (razeh@balr.com)
*/

public class OpenGLCanvasSetupFailedException extends OpenGLNativeException {
  OpenGLCanvasSetupFailedException() {
    super();
  }

  OpenGLCanvasSetupFailedException(String message) {
    super(message);
  }
}
