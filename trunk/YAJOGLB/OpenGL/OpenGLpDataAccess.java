/*
  Used to get to the OpenGL canvas accessors.
 
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
 * OpenGLpDataAccess
 * 
 * $Id$
 * 
 */

package OpenGL;

/**
 * Provides a public interface for getting at the native details of an 
 * OpenGL.Canvas.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version 0.4
 */

public interface OpenGLpDataAccess {
  /** X11 accessors */
  public int getDrawable(java.awt.Canvas canvas);
  public int getColormapID(java.awt.Canvas canvas);

  /** Win32 accessors */
  public int getHDC(java.awt.Canvas canvas);
}
