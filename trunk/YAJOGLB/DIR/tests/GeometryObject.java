/*
 * Geometry object.
 *
 * $Id: GeometryObject.java,v 1.6 2002/11/23 14:29:26 razeh Exp $
 * 
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import OpenGL.*;

/** The interface for objects the Geometry Viewer can render. */
public interface GeometryObject {
  /** Called when the Geometry Object should render itself. */
  public void paint(GeometryViewer viewer, GL gl, GLU glu);
  /** This is called when our geometry viewer receives glInit(). */
  public void glInit(GeometryViewer viewer, GL gl, GLU glu);
}
