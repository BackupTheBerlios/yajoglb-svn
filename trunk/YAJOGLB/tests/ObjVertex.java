

class ObjVertex {
  private double x;
  private double y;
  private double z;
  private double w;

  protected double getX() { return x; }
  protected double getY() { return y; }
  protected double getZ() { return z; }
  protected double getW() { return w; }

  ObjVertex(double nx,double ny,double nz,double nw) {
    x = nx;
    y = ny;
    z = nz;
    w = nw;
  }


}
