/* 
 * Wavefront OBJ representation.
 *
 * $Id$
 *
 * Copyright 2004
 * Robert Allan Zeh (razeh@yahoo.com)
 */


import java.util.*;

/** Represents a Wavefront OBJ file.  This is an incomplete specification;
 * there are a lot of features that are not supported.
 */
class OBJ {
  /** Our list of vericies. */
  private Vector verticies = new Vector();
  /** The drawables (things that respond to a paint method). */
  private Vector drawables = new Vector();
  /** A map of materials, from names to ObjMaterial objects. */
  private HashMap materials = new HashMap();
  /** A map of normals for our verticies. */
  private Vector normals = new Vector();

  /** Get the ith vertex in the obj.
   * @return the ith vertx. 
   */
  public ObjVertex getVertex(int i) { 
    return (ObjVertex)verticies.elementAt(i - 1);
  }
  /** Get the ith normal in the obj.
   * @return the ith normal. 
   */
  public ObjNormal getNormal(int i) { 
    return (ObjNormal)normals.elementAt(i - 1);
  }
  public Iterator getDrawables() { return drawables.iterator(); }
  /** Return the material for name.
   * @return the material for name. 
   */
  public ObjMaterial getMaterial(String name) {
    return (ObjMaterial) materials.get(name);
  }
  /** Add a vertex to our list of verticies.
   * @param v the vertex to add. 
   */
  public void addElement(ObjVertex v) {
    verticies.addElement(v);
  }
  /** Add a drawable to our list.
   * @param d the drawable to add.
   */
  public void addElement(ObjDrawable d) {
    drawables.addElement(d);
  }
  /** Add a material. 
   * @param m the material to add.
   */
  public void addElement(ObjMaterial m) {
    materials.put(m.getName(), m);
  }
  /** Add a normal to our list.
   * @param n the normal to add.
   */
  public void addElement(ObjNormal n) {
    normals.addElement(n);
  }
}
