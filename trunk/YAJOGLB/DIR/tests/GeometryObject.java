/*
 * Geometry object.
 *
 * $Id: GeometryObject.java,v 1.3 2001/06/10 19:14:11 razeh Exp $
 * 
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import OpenGL.*;
import GeometryViewer;

/** The interface for objects the Geometry Viewer can render. */
public interface GeometryObject {
  /** Called when the Geometry Object should render itself. */
  public void paint(GeometryViewer viewer, GL gl, GLU glu);
  /** This is called when our geometry viewer receives glInit(). */
  public void glIn(GeometryViewer viewer, GL gl, GLU glu);
}
