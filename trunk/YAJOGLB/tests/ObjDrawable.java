/* 
 * Wavefront OBJ drawable.
 *
 * $Id$
 *
 * Copyright 2004
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import OpenGL.GL;
import OpenGL.GLU;

interface ObjDrawable {
  public void paint(GL gl, GLU glu);
}
