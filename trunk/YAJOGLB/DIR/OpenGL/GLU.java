/* 
 * GLU class
 *
 * $Id: GLU.java,v 1.4 2002/07/21 16:55:42 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@yahoo.com)
 */

package OpenGL;

/** Implements most of the GLU library.  Unlike the core GL methods,
 * the GLU methods have not had their glu prefix removed.  Also, some
 * of the GLU methods have been implemented as instance methods on
 * various classes.  For examples see our "see also" section.
 * 
 * @author Robert Allan Zeh (razeh@yahoo.com)
 * 
 * @version 0.3
 * @serial
 * @see GLUNurbs 
 * @see GLUQuadric
 * @see GLUTesselator 
 */
public class GLU implements GLUConstants {

  /** Make sure that we load in our native library. */
  static {
    NativePackageLoader.loadNativeLibrary();
  }

  public native void gluLookAt(double eyeX,    double eyeY,    double eyeZ,
			       double centerX, double centerY, double centerZ,
			       double upX,     double upY,    double upZ);

  public native void gluOrtho2D(double left, double right,
				double bottom, double top);

  public native void gluPerspective(double fovy, double aspect,
				    double zNear, double zFar);
  
  public native void gluPickMatrix(double x, double y,
				   double width, double height,
				   int viewport[]);

  /** Unlike the native GLUT project function, we return the window
      coordinates in an array of three doubles. */
  public native void gluProject(double objx, double objy, double objz,
				double modelMatrix[],
				double projMatrix[],
				int viewport[],
				double win[]);

  /** Unlike the native GLUT project function, we return the object
      coordinates in an array of three doubles. */
  public native void gluUnProject(double winx, double winy, double winz,
				  double modelMatrix[],
				  double projMatrix[],
				  int viewport[],
				  double obj[]);


  public native String gluErrorString(int errorCode);



  /*
   *
   * Mipmapping and image scaling
   *
   */
  /** The parameters datain and dataout should be arrays pointing to the 
    input image and the output image. */
  public native int gluScaleImage(int format,
				  int widthin, int heightin,
				  int typein, Object datain,
				  int widthout, int heightout,
				  int typeout, Object dataout);

  public native int gluBuild1DMipmaps(int target, int components,
				      int width, int format,
				      int type, byte data[]);

  public native int gluBuild1DMipmaps(int target, int components,
				      int width, int format,
				      int type, short data[]);

  public native int gluBuild1DMipmaps(int target, int components,
				      int width, int format,
				      int type, int data[]);

  public native int gluBuild1DMipmaps(int target, int components,
				      int width, int format,
				      int type, float data[]);

  public native int gluBuild2DMipmaps(int target, int components,
				      int width, int height, int format,
				      int type, byte data[]);

  public native int gluBuild2DMipmaps(int target, int components,
				      int width, int height, int format,
				      int type, short data[]);

  public native int gluBuild2DMipmaps(int target, int components,
				      int width, int height, int format,
				      int type, int data[]);

  public native int gluBuild2DMipmaps(int target, int components,
				      int width, int height, int format,
				      int type, float data[]);

  public native String gluGetString(int name);
}
