/* 
 * OpenGLNativeMemoryExhaustedException class
 *
 * $Id: NativeMemoryExhaustedException.java,v 1.3 1999/04/29 01:17:14 razeh Exp $ 
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/** Thrown when we exhaust our native memory.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.3
 */

public class OpenGLNativeMemoryExhaustedException extends OpenGLNativeException {
  /** Constructs an <code> OpenGLNativeMemoryExhaustedException
      </code> with no message. */
  OpenGLNativeMemoryExhaustedException() {
    super();
  }

  /** Constructs an <code> OpenGLNativeMemoryExhaustedException
   </code> with the specified detail message.  
   @param message message the detail message.*/
  OpenGLNativeMemoryExhaustedException(String message) {
    super(message);
  }
}
