/*
 * OpenGLCanvasSetupFailedException class
 *
 * $Id: CanvasSetupFailedException.java,v 1.2 1998/09/10 01:00:27 razeh Exp $
 *
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/** This exception is thrown when we have trouble setting up an OpenGLCanvas.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1
*/

public class OpenGLCanvasSetupFailedException extends OpenGLNativeException {
  OpenGLCanvasSetupFailedException() {
    super();
  }

  OpenGLCanvasSetupFailedException(String message) {
    super(message);
  }
}
