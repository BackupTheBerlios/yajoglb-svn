/*
 *
 * OpenGLUConstants
 *
 * $Id: GLUConstants.java,v 1.4 1998/11/01 02:17:03 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/**
 *
 * This defines all of the constants that are used by the GLU library.
 * We have not removed the GLU prepended to all of the constant
 * definitions because of conflicts with some of the GL constants.
 *
 * @author Robert Allan Zeh (razeh@balr.com) 
 *
 * @version 0.1
 */

public interface GLUConstants {
  /* Normal vectors */
  static final int         GLU_SMOOTH      = 100000;
  static final int         GLU_FLAT        = 100001;
  static final int         GLU_NONE        = 100002;

  /* Quadric draw styles */
  static final int         GLU_POINT       = 100010;
  static final int         GLU_LINE        = 100011;
  static final int         GLU_FILL        = 100012;
  static final int         GLU_SILHOUETTE  = 100013;

  /* Quadric orientation */
  static final int         GLU_OUTSIDE     = 100020;
  static final int         GLU_INSIDE      = 100021;

  /* Tesselator */
  static final int         GLU_BEGIN       = 100100;
  static final int         GLU_VERTEX      = 100101;
  static final int         GLU_END         = 100102;
  static final int         GLU_ERROR       = 100103;
  static final int         GLU_EDGE_FLAG   = 100104;

  /* Contour types */
  static final int         GLU_CW          = 100120;
  static final int         GLU_CCW         = 100121;
  static final int         GLU_INTERIOR    = 100122;
  static final int         GLU_EXTERIOR    = 100123;
  static final int         GLU_UNKNOWN     = 100124;

  /* Tesselation errors */
  static final int         GLU_TESS_ERROR1 = 100151;  /* missing gluEndPolygon */
  static final int         GLU_TESS_ERROR2 = 100152;  /* missing gluBeginPolygon */
  static final int         GLU_TESS_ERROR3 = 100153;  /* misoriented contour */
  static final int         GLU_TESS_ERROR4 = 100154;  /* vertex/edge intersection */
  static final int         GLU_TESS_ERROR5 = 100155;  /* misoriented or self-intersecting loops */
  static final int         GLU_TESS_ERROR6 = 100156;  /* coincident vertices */
  static final int         GLU_TESS_ERROR7 = 100157;  /* all vertices collinear */
  static final int         GLU_TESS_ERROR8 = 100158;  /* intersecting edges */
  static final int         GLU_TESS_ERROR9 = 100159;  /* not coplanar contours */

        /* NURBS */
  static final int         GLU_AUTO_LOAD_MATRIX    = 100200;
  static final int         GLU_CULLING             = 100201;
  static final int         GLU_PARAMETRIC_TOLERANCE= 100202;
  static final int         GLU_SAMPLING_TOLERANCE  = 100203;
  static final int         GLU_DISPLAY_MODE        = 100204;
  static final int         GLU_SAMPLING_METHOD     = 100205;
  static final int         GLU_U_STEP              = 100206;
  static final int         GLU_V_STEP              = 100207;

  static final int         GLU_PATH_LENGTH         = 100215;
  static final int         GLU_PARAMETRIC_ERROR    = 100216;
  static final int         GLU_DOMAIN_DISTANCE     = 100217;
  static final int         GLU_MAP1_TRIM_2         = 100210;
  static final int         GLU_MAP1_TRIM_3         = 100211;
  static final int         GLU_OUTLINE_POLYGON     = 100240;
  static final int         GLU_OUTLINE_PATCH       = 100241;
  static final int         GLU_NURBS_ERROR1        = 100251;   /* spline order un-supported */
  static final int GLU_NURBS_ERROR2  = 100252;   /* too few knots */
  static final int         GLU_NURBS_ERROR3  = 100253;   /* valid knot range is empty */
  static final int         GLU_NURBS_ERROR4  = 100254;   /* decreasing knot sequence */
  static final int         GLU_NURBS_ERROR5  = 100255;   /* knot multiplicity > spline order */
  static final int         GLU_NURBS_ERROR6  = 100256;   /* endcurve() must follow bgncurve() */
  static final int         GLU_NURBS_ERROR7  = 100257;   /* bgncurve() must precede endcurve() */
  static final int         GLU_NURBS_ERROR8  = 100258;   /* ctrlarray or knot vector is NULL */
  static final int         GLU_NURBS_ERROR9  = 100259;   /* can't draw pwlcurves */
  static final int         GLU_NURBS_ERROR10 = 100260;   /* missing gluNurbsCurve() */
  static final int         GLU_NURBS_ERROR11 = 100261;   /* missing gluNurbsSurface() */
  static final int         GLU_NURBS_ERROR12 = 100262;   /* endtrim() must precede endsurface() */
  static final int         GLU_NURBS_ERROR13 = 100263;   /* bgnsurface() must precede endsurface() */
  static final int         GLU_NURBS_ERROR14 = 100264;   /* curve of improper type passed as trim curve */
  static final int         GLU_NURBS_ERROR15 = 100265;   /* bgnsurface() must precede bgntrim() */
  static final int         GLU_NURBS_ERROR16 = 100266;   /* endtrim() must follow bgntrim() */
  static final int         GLU_NURBS_ERROR17 = 100267;   /* bgntrim() must precede endtrim()*/
  static final int         GLU_NURBS_ERROR18 = 100268;   /* invalid or missing trim curve*/
  static final int         GLU_NURBS_ERROR19 = 100269;   /* bgntrim() must precede pwlcurve() */
  static final int         GLU_NURBS_ERROR20 = 100270;   /* pwlcurve referenced twice*/
  static final int         GLU_NURBS_ERROR21 = 100271;   /* pwlcurve and nurbscurve mixed */
  static final int         GLU_NURBS_ERROR22 = 100272;   /* improper usage of trim data type */
  static final int         GLU_NURBS_ERROR23 = 100273;   /* nurbscurve referenced twice */
  static final int         GLU_NURBS_ERROR24 = 100274;   /* nurbscurve and pwlcurve mixed */
  static final int         GLU_NURBS_ERROR25 = 100275;   /* nurbssurface referenced twice */
  static final int         GLU_NURBS_ERROR26 = 100276;   /* invalid property */
  static final int         GLU_NURBS_ERROR27 = 100277;   /* endsurface() must follow bgnsurface() */
  static final int         GLU_NURBS_ERROR28 = 100278;   /* intersecting or misoriented trim curves */
  static final int         GLU_NURBS_ERROR29 = 100279;   /* intersecting trim curves */
  static final int         GLU_NURBS_ERROR30 = 100280;   /* UNUSED */
  static final int         GLU_NURBS_ERROR31 = 100281;   /* unconnected trim curves */
  static final int         GLU_NURBS_ERROR32 = 100282;   /* unknown knot error */
  static final int         GLU_NURBS_ERROR33 = 100283;   /* negative vertex count encountered */
  static final int         GLU_NURBS_ERROR34 = 100284;   /* negative byte-stride */
  static final int         GLU_NURBS_ERROR35 = 100285;   /* unknown type descriptor */
  static final int         GLU_NURBS_ERROR36 = 100286;   /* null control point reference */
  static final int         GLU_NURBS_ERROR37 = 100287;   /* duplicate point on pwlcurve */
  
  /* Errors */
  static final int         GLU_INVALID_ENUM                = 100900;
  static final int         GLU_INVALID_VALUE               = 100901;
  static final int         GLU_OUT_OF_MEMORY               = 100902;
  static final int         GLU_INCOMPATIBLE_GL_VERSION     = 100903;

  /* New in GLU 1.1 */
  static final int         GLU_VERSION     = 100800;
  static final int         GLU_EXTENSIONS  = 100801;
}
