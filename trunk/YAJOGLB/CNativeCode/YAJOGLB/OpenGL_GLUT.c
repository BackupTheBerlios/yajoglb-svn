/*
  Implements the GLUT basic functions.
 
  Copyright 2004, Robert Allan Zeh (razeh@yahoo.com)
  43 Gale
  River Forest, IL 60305
 
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA

*/

/*
 * OpenGL_GLUT.c
 *
 * $Id: $
 *
 * This implements the generic GLU methods.
 *
 */

#include <glut.h>
#include "OpenGL_GLUT.h"

/*
 * Class:     OpenGL_GLUT
 * Method:    solidTeapot
 * Signature: (D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUT_solidTeapot(JNIEnv *env, jobject glut, jdouble size)  
{
  glutSolidTeapot(size);
}



/*
 * Class:     OpenGL_GLUT
 * Method:    wireTeapot
 * Signature: (D)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUT_wireTeapot(JNIEnv *env, jobject glut, jdouble size) 
{
  glutWireTeapot(size);
}



/*
 * Class:     OpenGL_GLUT
 * Method:    solidTorus
 * Signature: (DDII)V
 */
JNIEXPORT void JNICALL Java_OpenGL_GLUT_solidTorus(JNIEnv *env, jobject glut, 
												   jdouble innerRadius, 
												   jdouble outerRadius, 
												   jint nsides, jint rings)
{
  glutSolidTorus(innerRadius, outerRadius, nsides, rings);
}
