/*
 * OpenGLCanvasSetupFailedException class
 *
 * $Id: CanvasSetupFailedException.java,v 1.3 1999/04/29 01:17:14 razeh Exp $
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
 * @version 0.3
*/

public class OpenGLCanvasSetupFailedException extends OpenGLNativeException {
  OpenGLCanvasSetupFailedException() {
    super();
  }

  OpenGLCanvasSetupFailedException(String message) {
    super(message);
  }
}
