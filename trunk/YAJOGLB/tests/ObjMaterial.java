/*
 * Material representation for the OBJ format.
 *
 * $Id$
 *
 * Copyright 2002
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import OpenGL.GL;
import OpenGL.GLU;
import OpenGL.GLConstants;

/** This represent a OBJ material, which basically means that it sets
 * a color.
 */
class ObjMaterial implements GLConstants, ObjDrawable {
  /** The ambient color component. */
  private float[] ambient = new float[3];
  /** The diffuse color component. */
  private float[] diffuse = new float[3];
  /** The specular color component. */
  private float[] specular = new float[3];
  private float specularHighlight;
  /** The name assigned to the material. */
  private String name;
  public String getName() { return name; }
  /** Construct a material.
   * @param n the name of the material.
   * @param amb_r the ambient component's red value.
   * @param amb_g the ambient component's green value.
   * @param amb_b the ambient component's blue value.
   * @param dif_r the diffuse component's red value.
   * @param dif_g the diffuse component's green value.
   * @param dif_b the diffuse component's blue value.
   * @param spec_r the specular component's red value.
   * @param spec_g the specular component's green value.
   * @param spec_b the specular component's blue value.
   * @param sh the specular highlight.
   */
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
  /** Change OpenGL's material settings to match this material. */
  public void paint(GL gl, GLU glu) {
    gl.material(FRONT_AND_BACK, AMBIENT, ambient);
    gl.material(FRONT_AND_BACK, DIFFUSE, diffuse);
    gl.material(FRONT_AND_BACK, SPECULAR, specular);
    gl.material(FRONT_AND_BACK, SHININESS, specularHighlight);
  }
}
