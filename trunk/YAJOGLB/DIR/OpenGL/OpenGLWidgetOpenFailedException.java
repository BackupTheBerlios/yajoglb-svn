/* 
 * OpenGLWidgetOpenFailedException class
 *
 * $Id: OpenGLWidgetOpenFailedException.java,v 1.2 1998/03/16 00:00:57 razeh Exp $
 *
 * Copyright 1997
 *
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/** This exception is thrown when we are unable to open up the widget. 

  @author Robert Allan Zeh (razeh@balr.com)
*/
public class OpenGLWidgetOpenFailedException extends OpenGLNativeException {
  OpenGLWidgetOpenFailedException() {
    super();
  }
  OpenGLWidgetOpenFailedException(String message) {
    super(message);
  }
}
