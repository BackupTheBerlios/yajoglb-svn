/*
 * Vec 
 *
 * $Id: Vec.java,v 1.2 2002/04/06 15:13:05 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh
 */

public class Vec {
  static public float[] crossProduct(float vector1[], float vector2[]) {
    float result[] = new float[4];

    result[0] = 
      (vector1[1]*vector2[2]) - (vector1[2]*vector2[1]);
    result[1] = 
      (vector1[2]*vector2[0]) - (vector1[0]*vector2[2]);
    result[2] = 
      (vector1[0]*vector2[1]) - (vector1[1]*vector2[0]);
    return result;
  }
}
