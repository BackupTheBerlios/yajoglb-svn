
import java.util.*;

class OBJ {
  private Vector verticies = new Vector();
  private Vector drawables = new Vector();
  private HashMap materials = new HashMap();
  private Vector normals = new Vector();

  public ObjVertex getVertex(int i) { 
    return (ObjVertex)verticies.elementAt(i - 1);
  }
  public ObjNormal getNormal(int i) { 
    return (ObjNormal)normals.elementAt(i - 1);
  }
  public Iterator getDrawables() { return drawables.iterator(); }
  public ObjMaterial getMaterial(String name) {
    return (ObjMaterial) materials.get(name);
  }
  public void addElement(ObjVertex v) {
    verticies.addElement(v);
  }
  public void addElement(ObjDrawable d) {
    drawables.addElement(d);
  }
  public void addElement(ObjMaterial m) {
    materials.put(m.getName(), m);
  }
  public void addElement(ObjNormal n) {
    normals.addElement(n);
  }
}
