/*
 * MatrixModifiers
 * 
 * $Id: MatrixModifiers.java,v 1.3 2002/04/06 15:12:30 razeh Exp $
 *
 * Converted into Java from the Mesa source.
 *
 */

/** A class for modifying matricies from the Mesa source code. */
class MatrixModifiers {

  /*
   * Transform a point (column vector) by a 4x4 matrix.  I.e.  out = m * in
   * Input:  m - the 4x4 matrix
   *         in - the 4x1 vector
   * Output:  out - the resulting 4x1 vector.
   */
  static void transform_point( float out[], float m[],
			       float in[] )
  {
   
    out[0] = 
      (m[0+(0*4)] * in[0]) +
      (m[0+(1*4)] * in[1]) +
      (m[0+(2*4)] * in[2]) + 
      (m[0+(3*4)] * in[3]);
    out[1] = 
      (m[1+(0*4)] * in[0]) +
      (m[1+(1*4)] * in[1]) +
      (m[1+(2*4)] * in[2]) +
      (m[1+(3*4)] * in[3]);
    out[2] = 
      (m[2+(0*4)] * in[0]) +
      (m[2+(1*4)] * in[1]) +
      (m[2+(2*4)] * in[2]) +
      (m[2+(3*4)] * in[3]);
    out[3] = 
      (m[3+(0*4)] * in[0]) +
      (m[3+(1*4)] * in[1]) +
      (m[3+(2*4)] * in[2]) +
      (m[3+(3*4)] * in[3]);
  }
  
  
  static void gl_rotation_matrix(float angle, float x, float y, float z,
				 float m[] )
  {
    /* This function contributed by Erich Boleyn (erich@uruk.org) */
    float mag, s, c;
    float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
    
    s = (float) Math.sin( angle * (Math.PI / 180.0) );
    c = (float) Math.cos( angle * (Math.PI / 180.0) );
    
    mag = (float) Math.sqrt( x*x + y*y + z*z );
    
    if (mag == 0.0) {
      /* generate an identity matrix and return */
      m[0] = 1.0f;
      m[0+(1*4)] = 0.0f;
      m[0+(2*4)] = 0.0f;
      m[0+(3*4)] = 0.0f;
      
      m[1+(0*4)] = 0.0f;
      m[1+(1*4)] = 1.0f;
      m[1+(2*4)] = 0.0f;
      m[1+(3*4)] = 0.0F;
      
      m[2+(0*4)] = 0.0f;
      m[2+(1*4)] = 0.0f;
      m[2+(2*4)] = 1.0f;
      m[2+(3*4)] = 0.0F;
      
      m[3+(0*4)] = 0.0F;
      m[3+(1*4)] = 0.0F;
      m[3+(2*4)] = 0.0F;
      m[3+(3*4)] = 1.0F;
      return;
    }
    
    x /= mag;
    y /= mag;
    z /= mag;
    
    /*
     *     Arbitrary axis rotation matrix.
     *
     *  This is composed of 5 matrices, Rz, Ry, T, Ry', Rz', multiplied
     *  like so:  Rz * Ry * T * Ry' * Rz'.  T is the final rotation
     *  (which is about the X-axis), and the two composite transforms
     *  Ry' * Rz' and Rz * Ry are (respectively) the rotations necessary
     *  from the arbitrary axis to the X-axis then back.  They are
     *  all elementary rotations.
     *
     *  Rz' is a rotation about the Z-axis, to bring the axis vector
     *  into the x-z plane.  Then Ry' is applied, rotating about the
     *  Y-axis to bring the axis vector parallel with the X-axis.  The
     *  rotation about the X-axis is then performed.  Ry and Rz are
     *  simply the respective inverse transforms to bring the arbitrary
     *  axis back to it's original orientation.  The first transforms
     *  Rz' and Ry' are considered inverses, since the data from the
     *  arbitrary axis gives you info on how to get to it, not how
     *  to get away from it, and an inverse must be applied.
     *
     *  The basic calculation used is to recognize that the arbitrary
     *  axis vector (x, y, z), since it is of unit length, actually
     *  represents the sines and cosines of the angles to rotate the
     *  X-axis to the same orientation, with theta being the angle about
     *  Z and phi the angle about Y (in the order described above)
     *  as follows:
     *
     *  cos ( theta ) = x / sqrt ( 1 - z^2 )
     *  sin ( theta ) = y / sqrt ( 1 - z^2 )
     *
     *  cos ( phi ) = sqrt ( 1 - z^2 )
     *  sin ( phi ) = z
     *
     *  Note that cos ( phi ) can further be inserted to the above
     *  formulas:
     *
     *  cos ( theta ) = x / cos ( phi )
     *  sin ( theta ) = y / sin ( phi )
     *
     *  ...etc.  Because of those relations and the standard trigonometric
     *  relations, it is pssible to reduce the transforms down to what
     *  is used below.  It may be that any primary axis chosen will give the
     *  same results (modulo a sign convention) using thie method.
     *
     *  Particularly nice is to notice that all divisions that might
     *  have caused trouble when parallel to certain planes or
     *  axis go away with care paid to reducing the expressions.
     *  After checking, it does perform correctly under all cases, since
     *  in all the cases of division where the denominator would have
     *  been zero, the numerator would have been zero as well, giving
     *  the expected result.
     */
    
    xx = x * x;
    yy = y * y;
    zz = z * z;
    xy = x * y;
    yz = y * z;
    zx = z * x;
    xs = x * s;
    ys = y * s;
    zs = z * s;
    one_c = 1.0F - c;
    
    m[0] = (one_c * xx) + c;
    m[0+(1*4)] = (one_c * xy) - zs;
    m[0+(2*4)] = (one_c * zx) + ys;
    m[0+(3*4)] = 0.0F;
    
    m[1+(0*4)] = (one_c * xy) + zs;
    m[1+(1*4)] = (one_c * yy) + c;
    m[1+(2*4)] = (one_c * yz) - xs;
    m[1+(3*4)] = 0.0F;
    
    m[2+(0*4)] = (one_c * zx) - ys;
    m[2+(1*4)] = (one_c * yz) + xs;
    m[2+(2*4)] = (one_c * zz) + c;
    m[2+(3*4)] = 0.0F;
    
    m[3+(0*4)] = 0.0F;
    m[3+(1*4)] = 0.0F;
    m[3+(2*4)] = 0.0F;
    m[3+(3*4)] = 1.0F;
    
    
  }
  
  static float[] rotate_point(float in[],
			   float angle, float r_x, float r_y, float r_z)
  {
    float rotation_matrix[] = new float[16];
    float out[] = new float[4];
    gl_rotation_matrix(angle, r_x, r_y, r_z, rotation_matrix);
    transform_point(out, rotation_matrix, in);
    return out;
  }
}


