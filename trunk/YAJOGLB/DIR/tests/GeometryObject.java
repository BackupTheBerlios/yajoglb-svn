/*
 * Geometry object.
 *
 * $Id: GeometryObject.java,v 1.1 1998/03/30 02:16:19 razeh Exp $
 * 
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

import OpenGL.*;

/** The interface for objects the Geometry Viewer can render. */
public interface GeometryObject {
  /** Called when the Geometry Object should render itself. */
  public void paint(GeometryViewer viewer, GL gl, GLU glu);
  /** This is called when our geometry viewer receives glInit(). */
  public void glIn(GeometryViewer viewer, GL gl, GLU glu);
}