/*
 * Material representation for the OBJ format.
 *
 * $Id: ObjMaterial.java,v 1.1 2002/04/06 15:12:40 razeh Exp $
 *
 * Copyright 2002
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import OpenGL.GL;
import OpenGL.GLU;
import OpenGL.GLConstants;

class ObjMaterial implements GLConstants, ObjDrawable {
  //private float ambient_r, ambient_g, ambient_b;
  //private float diffuse_r, diffuse_g, diffuse_b;
  //private float specular_r, specular_g, specular_b;
  private float[] ambient = new float[3];
  private float[] diffuse = new float[3];
  private float[] specular = new float[3];
  private float specularHighlight;
  private String name;
  public String getName() { return name; }
  ObjMaterial(String n,
	      float amb_r, float amb_g, float amb_b,
	      float dif_r, float dif_g, float dif_b,
	      float spec_r, float spec_g, float spec_b,
	      float sh) {
    name = n;
    ambient[0] = amb_r;
    ambient[1] = amb_g;
    ambient[2] = amb_b;
    diffuse[0] = dif_r;
    diffuse[1] = dif_g;
    diffuse[2] = dif_b;
    specular[0] = spec_r;
    specular[1] = spec_g;
    specular[2] = spec_b;
    specularHighlight = sh;
  }
  public void paint(GL gl, GLU glu) {
    gl.material(FRONT_AND_BACK, AMBIENT, ambient);
    gl.material(FRONT_AND_BACK, DIFFUSE, diffuse);
    gl.material(FRONT_AND_BACK, SPECULAR, specular);
    gl.material(FRONT_AND_BACK, SHININESS, specularHighlight);
  }
}
