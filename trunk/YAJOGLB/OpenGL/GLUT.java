/*
  The base and incomplete interface for GLUT in java.
 
  Copyright 2004, Robert Allan Zeh (razeh@yahoo.com)
  43 Gale
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
 * GLUT.java
 *
 * $Id: $
 *
 * Copyright 2004
 * Robert Allan Zeh (razeh@yahoo.com)
 */

package OpenGL;

/**
 * This is the interface for the GLUT utilities.  Mamy of the GLUT
 * functions don't make sense for Java and are not included.  For
 * example, none of the event handling functions make sense, so they
 * are not included.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com)
 *
 * @version .1
 */
public class GLUT {
    static {
	NativePackageLoader.loadNativeLibrary();
    }

    public native void solidTeapot(double size);
    public native void wireTeapot(double size);
    public native void solidTorus(double innerRadius, double outerRadius, int nsides,
				  int rings);
}
