
import OpenGL.GL;
import OpenGL.GLU;
import OpenGL.GLConstants;
import java.util.*;

class VertexInfo {
  private int v;   // The vertex
  private int vt;  // The texture vertex.
  private int vn;  // The normal for the vertex.
  public int getV() { return v; }
  public int getVT() { return vt; }
  public int getVN() { return vn; }
  VertexInfo(int nv, int nvt, int nvn) {
    v = nv;
    vt = nvt;
    vn = nvn;
  }
}

class ObjFace implements GLConstants, ObjDrawable {
  LinkedList verticies = new LinkedList();
  OBJ obj;

  ObjFace(OBJ o) { obj = o; } 
  public Iterator getVerticies() { return verticies.iterator(); }
  
  public int size() { return verticies.size(); }
  public void add(int v, int vt, int vn) {
    verticies.addLast(new VertexInfo(v, vt, vn));
  }
  public void paint(GL gl, GLU glu) {
    if (size() == 3) {
	gl.begin(TRIANGLES);
    }
    Iterator i = getVerticies();
    while (i.hasNext()) {
      VertexInfo v = (VertexInfo) i.next();
      ObjVertex vertex = obj.getVertex(v.getV());
      ObjNormal normal = obj.getNormal(v.getVN());
      
      gl.normal(normal.getX(), normal.getY(), normal.getZ());
      gl.vertex(vertex.getX(), vertex.getY(), vertex.getZ());
    }
    gl.end();
  }
}
