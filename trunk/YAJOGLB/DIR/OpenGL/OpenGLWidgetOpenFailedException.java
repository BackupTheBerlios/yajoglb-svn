/* 
 * OpenGLWidgetOpenFailedException class
 *
 * $Id: OpenGLWidgetOpenFailedException.java,v 1.3 1998/09/10 01:05:53 razeh Exp $
 *
 * Copyright 1997
 *
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/** This exception is thrown when we are unable to open up the widget. 
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1
*/

public class OpenGLWidgetOpenFailedException extends OpenGLNativeException {
  OpenGLWidgetOpenFailedException() {
    super();
  }
  OpenGLWidgetOpenFailedException(String message) {
    super(message);
  }
}
