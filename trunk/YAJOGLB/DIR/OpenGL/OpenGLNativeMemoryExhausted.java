/* 
 * OpenGLNativeMemoryExhausted class
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/** This exception is thrown when we exhaust our native memory.

  @author Robert Allan Zeh (razeh@balr.com)
*/
public class OpenGLNativeMemoryExhausted extends OpenGLNativeException {
  OpenGLNativeMemoryExhausted() {
    super();
  }
  OpenGLNativeMemoryExhausted(String message) {
    super(message);
  }
}
