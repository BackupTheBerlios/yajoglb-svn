/*
 * Object vertex render class
 *
 * $Id$
 *
 * Copyright 2001
 * Robert Allan Zeh (razeh@yahoo.com)
 */


class ObjVertex {
  /** Our x component. */
  private double x;
  /** Our y component. */
  private double y;
  /** Our z component. */
  private double z;
  /** Our w component. */
  private double w;

  /** Return our x component. 
   * @param our x component. 
   */
  protected double getX() { return x; }
  /** Return our y component. 
   * @param our y component. 
   */
  protected double getY() { return y; }
  /** Return our z component. 
   * @param our z component. 
   */
  protected double getZ() { return z; }
  /** Return our w component. 
   * @param our w component. 
   */
  protected double getW() { return w; }

  /** Construct a vertex.
   * @param nx the x component. 
   * @param ny the y component. 
   * @param nz the z component. 
   * @param nw the w component. 
   */
  ObjVertex(double nx,double ny,double nz,double nw) {
    x = nx;
    y = ny;
    z = nz;
    w = nw;
  }


}
