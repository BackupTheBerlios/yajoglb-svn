/*
  Error handling for the OpenGL canvas.
 
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
 * OpenGLCanvasSetupFailedException class
 *
 * $Id: CanvasSetupFailedException.java,v 1.4 2002/04/14 18:17:50 razeh Exp $
 *
 */

package OpenGL;

/** This exception is thrown when we have trouble setting up an
 *OpenGL.Canvas.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.4 */

public class CanvasSetupFailedException extends NativeException {
  CanvasSetupFailedException() {
    super();
  }

  CanvasSetupFailedException(String message) {
    super(message);
  }
}
