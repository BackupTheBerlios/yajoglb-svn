/* 
 * Wavefront OBJ face.
 *
 * $Id$
 *
 * Copyright 2004
 * Robert Allan Zeh (razeh@yahoo.com)
 */


import OpenGL.GL;
import OpenGL.GLU;
import OpenGL.GLConstants;
import java.util.*;

/** Contains indicies for all of the information we need for a vertex 
 * in one place.  It is expected the the indicies are really being
 * stored in an OBJ object.
 */
class VertexInfo {
  /** The vertex. */
  private int v;   
  /** The texture vertex. */
  private int vt;  
  /** The normal for the vertex. */
  private int vn; 
  /** Returns our vertex. 
   * @return our vertex number.
   */
  public int getV() { return v; }
  public int getVT() { return vt; }
  public int getVN() { return vn; }
  /** Construct a vertex info.
   * @param nv the vertex number. 
   * @param nvt the texture vertex. 
   * @param nvn the vertex normal. 
   */
  VertexInfo(int nv, int nvt, int nvn) {
    v = nv;
    vt = nvt;
    vn = nvn;
  }
}

/** 
 * Represents an OBJ face, which is a list of verticies, a normal,
 * and possible textures verticies as well.
 *
 * @bug Currently we only implement triangular faces properly.
 * @bug we ignore the vertex texture.
 */
class ObjFace implements GLConstants, ObjDrawable {
  /** Our list of verticies. */
  LinkedList verticies = new LinkedList();
  /** The obj that our vertex indicies reference. */
  OBJ obj;

  /** Construct a face where 
   * @param o the OBJ that holds onto all of the information about
   * our verticies. 
   */
  ObjFace(OBJ o) { obj = o; } 

  /** An iterator to our verticies.  
   * @return an iterator to our verticies.
   */
  public Iterator getVerticies() { return verticies.iterator(); }

  /** Returns the number of verticies. 
   * @return the number of verticies in our face. 
   */
  public int size() { return verticies.size(); }

  /** Add a vertex to our list. 
   * @param v the vertex index.
   * @param vt vertex texture index.
   * @param vn the vertex normal index.
   */
  public void add(int v, int vt, int vn) {
    verticies.addLast(new VertexInfo(v, vt, vn));
  }

  /** Render our face using gl and glu.
   * @param gl the OpenGL instance for rendering.
   * @param glu the GLU instance for rendering.
   */
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
