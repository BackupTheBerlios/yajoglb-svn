/*
 * Obj normal.
 *
 * $Id$
 *
 * Copyright 2004
 * Robert Allan Zeh (razeh@yahoo.com)
 */


/** Represents an obj normal. */
class ObjNormal {
  /** The x component of the normal. */
  private double x;
  /** The y component of the normal. */
  private double y;
  /** The z component of the normal. */
  private double z;
  
  /** Construct a normal object. 
   * @param nx the x component. 
   * @param ny the y component. 
   * @param nz the z component. 
   */
  ObjNormal(double nx, double ny, double nz) {
    x = nx;
    y = ny;
    z = nz;
  }

  /** Returns the normal's X component. */
  protected double getX() { return x;}
  /** Returns the normal's Y component. */
  protected double getY() { return y;}
  /** Returns the normal's Z component. */
  protected double getZ() { return z;}
}
