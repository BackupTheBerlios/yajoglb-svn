/*
  This exception is thrown when the native OpenGL library doesn't support
  a called function.
 
  Copyright 2001, Robert Allan Zeh (razeh@yahoo.com)
  7346 Lake Street #3W
  River Forest, IL 60305
 
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA

*/
/*
 *
 * UnsupportedMethodException class
 *
 * $Id: UnsupportedMethodException.java,v 1.2 2002/04/14 18:17:52 razeh Exp $
 *
 */

package OpenGL;

/** Thrown when we tried to call an OpenGL or GLU function that isn't
 * supported by our native OpenGL implementation.  For example, Mesa 3.0
 * only implements GLU 1.1, so the NURBS callback functions are not
 * implemented.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com)
 * 
 * @version 0.4
 */


public class UnsupportedMethodException extends NativeException {

  /** Constructs an <code> UnsupportedMethodException </code>
      with no message. */
  UnsupportedMethodException() {
    super();
  }
  
  /** Constructs an <code> UnsupportedMethodException
   </code> with the specified detail message.  
   @param message message the detail message.*/
  UnsupportedMethodException(String message) {
    super(message);
  }
}
