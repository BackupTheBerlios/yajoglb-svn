package OpenGL;

/** OpenGLConstants 
 * 
 * This defines all of the constants that the GL library uses.  We
 * have removed all of the GL_ prefixes, in the same manner that we
 * removed all of the gl prefixes for the OpenGL function calls.  
 */

public interface OpenGLConstants {
  static final int CURRENT_BIT		= 0x00000001;
  static final int POINT_BIT		= 0x00000002;
  static final int LINE_BIT		= 0x00000004;
  static final int POLYGON_BIT		= 0x00000008;
  static final int POLYGON_STIPPLE_BIT	= 0x00000010;
  static final int PIXEL_MODE_BIT	= 0x00000020;
  static final int LIGHTING_BIT		= 0x00000040;
  static final int FOG_BIT		= 0x00000080;
  static final int DEPTH_BUFFER_BIT	= 0x00000100;
  static final int ACCUM_BUFFER_BIT	= 0x00000200;
  static final int STENCIL_BUFFER_BIT	= 0x00000400;
  static final int VIEWPORT_BIT		= 0x00000800;
  static final int TRANSFORM_BIT	= 0x00001000;
  static final int ENABLE_BIT		= 0x00002000;
  static final int COLOR_BUFFER_BIT	= 0x00004000;
  static final int HINT_BIT		= 0x00008000;
  static final int EVAL_BIT		= 0x00010000;
  static final int LIST_BIT		= 0x00020000;
  static final int TEXTURE_BIT		= 0x00040000;
  static final int SCISSOR_BIT		= 0x00080000;
  static final int ALL_ATTRIB_BITS	= 0x000fffff;


  /* Boolean values */
  static final int FALSE			= 0;
  static final int TRUE			= 1;

  /* Data types */
  static final int      GL_BYTE				= 0x1400;
  static final int      GL_UNSIGNED_BYTE		= 0x1401;
  static final int 	GL_SHORT			= 0x1402;
  static final int 	GL_UNSIGNED_SHORT		= 0x1403;
  static final int 	GL_INT				= 0x1404;
  static final int 	GL_UNSIGNED_INT			= 0x1405;
  static final int 	GL_FLOAT			= 0x1406;
  static final int 	GL_DOUBLE			= 0x140A;
  static final int 	GL_2_BYTES			= 0x1407;
  static final int 	GL_3_BYTES			= 0x1408;
  static final int 	GL_4_BYTES			= 0x1409;

  /* Primitives */
  static final int      LINES			        = 0x0001;
  static final int 	POINTS			        = 0x0000;
  static final int 	LINE_STRIP			= 0x0003;
  static final int 	LINE_LOOP			= 0x0002;
  static final int 	TRIANGLES			= 0x0004;
  static final int 	TRIANGLE_STRIP		        = 0x0005;
  static final int 	TRIANGLE_FAN			= 0x0006;
  static final int 	QUADS			        = 0x0007;
  static final int 	QUAD_STRIP			= 0x0008;
  static final int 	POLYGON			        = 0x0009;
  static final int 	EDGE_FLAG			= 0x0B43;

  /* Vertex Arrays */
  static final int 	VERTEX_ARRAY			= 0x8074;
  static final int 	NORMAL_ARRAY			= 0x8075;
  static final int 	COLOR_ARRAY			= 0x8076;
  static final int 	INDEX_ARRAY			= 0x8077;
  static final int 	TEXTURE_COORD_ARRAY		= 0x8078;
  static final int 	EDGE_FLAG_ARRAY		= 0x8079;
  static final int 	VERTEX_ARRAY_SIZE		= 0x807A;
  static final int 	VERTEX_ARRAY_TYPE		= 0x807B;
  static final int 	VERTEX_ARRAY_STRIDE		= 0x807C;
  static final int 	VERTEX_ARRAY_COUNT		= 0x807D;
  static final int 	NORMAL_ARRAY_TYPE		= 0x807E;
  static final int 	NORMAL_ARRAY_STRIDE		= 0x807F;
  static final int 	NORMAL_ARRAY_COUNT		= 0x8080;
  static final int 	COLOR_ARRAY_SIZE		= 0x8081;
  static final int 	COLOR_ARRAY_TYPE		= 0x8082;
  static final int 	COLOR_ARRAY_STRIDE		= 0x8083;
  static final int 	COLOR_ARRAY_COUNT		= 0x8084;
  static final int 	INDEX_ARRAY_TYPE		= 0x8085;
  static final int 	INDEX_ARRAY_STRIDE		= 0x8086;
  static final int 	INDEX_ARRAY_COUNT		= 0x8087;
  static final int 	TEXTURE_COORD_ARRAY_SIZE	= 0x8088;
  static final int 	TEXTURE_COORD_ARRAY_TYPE	= 0x8089;
  static final int 	TEXTURE_COORD_ARRAY_STRIDE	= 0x808A;
  static final int 	TEXTURE_COORD_ARRAY_COUNT	= 0x808B;
  static final int 	EDGE_FLAG_ARRAY_STRIDE	= 0x808C;
  static final int 	EDGE_FLAG_ARRAY_COUNT	= 0x808D;
  static final int 	VERTEX_ARRAY_POINTER		= 0x808E;
  static final int 	NORMAL_ARRAY_POINTER		= 0x808F;
  static final int 	COLOR_ARRAY_POINTER		= 0x8090;
  static final int 	INDEX_ARRAY_POINTER		= 0x8091;
  static final int 	TEXTURE_COORD_ARRAY_POINTER	= 0x8092;
  static final int 	EDGE_FLAG_ARRAY_POINTER	= 0x8093;
  static final int      V2F				= 0x2A20;
  static final int 	V3F				= 0x2A21;
  static final int 	C4UB_V2F			= 0x2A22;
  static final int 	C4UB_V3F			= 0x2A23;
  static final int 	C3F_V3F			= 0x2A24;
  static final int 	N3F_V3F			= 0x2A25;
  static final int 	C4F_N3F_V3F			= 0x2A26;
  static final int 	T2F_V3F			= 0x2A27;
  static final int 	T4F_V4F			= 0x2A28;
  static final int 	T2F_C4UB_V3F			= 0x2A29;
  static final int 	T2F_C3F_V3F			= 0x2A2A;
  static final int 	T2F_N3F_V3F			= 0x2A2B;
  static final int 	T2F_C4F_N3F_V3F		= 0x2A2C;
  static final int 	T4F_C4F_N3F_V4F		= 0x2A2D;

  /* Matrix Mode */
  static final int      MATRIX_MODE			= 0x0BA0;
  static final int 	MODELVIEW			= 0x1700;
  static final int 	PROJECTION			= 0x1701;
  static final int 	TEXTURE			= 0x1702;


  /* Points */
  static final int      POINT_SMOOTH			= 0x0B10;
  static final int 	POINT_SIZE			= 0x0B11;
  static final int 	POINT_SIZE_GRANULARITY 	= 0x0B13;
  static final int 	POINT_SIZE_RANGE		= 0x0B12;

  /* Lines */
  static final int      LINE_SMOOTH			= 0x0B20;
  static final int 	LINE_STIPPLE			= 0x0B24;
  static final int 	LINE_STIPPLE_PATTERN		= 0x0B25;
  static final int 	LINE_STIPPLE_REPEAT		= 0x0B26;
  static final int 	LINE_WIDTH			= 0x0B21;
  static final int 	LINE_WIDTH_GRANULARITY	= 0x0B23;
  static final int 	LINE_WIDTH_RANGE		= 0x0B22;

  /* Polygons */
  static final int      POINT			= 0x1B00;
  static final int 	LINE				= 0x1B01;
  static final int 	FILL				= 0x1B02;
  static final int 	CCW				= 0x0901;
  static final int 	CW				= 0x0900;
  static final int 	FRONT			= 0x0404;
  static final int 	BACK				= 0x0405;
  static final int 	CULL_FACE			= 0x0B44;
  static final int 	CULL_FACE_MODE		= 0x0B45;
  static final int 	POLYGON_SMOOTH		= 0x0B41;
  static final int 	POLYGON_STIPPLE		= 0x0B42;
  static final int 	FRONT_FACE			= 0x0B46;
  static final int 	POLYGON_MODE			= 0x0B40;
  static final int 	POLYGON_OFFSET_FACTOR	= 0x3038;
  static final int 	POLYGON_OFFSET_UNITS		= 0x2A00;
  static final int 	POLYGON_OFFSET_POINT		= 0x2A01;
  static final int 	POLYGON_OFFSET_LINE		= 0x2A02;
  static final int 	POLYGON_OFFSET_FILL		= 0x8037;

  /* Display Lists */
  static final int      COMPILE			= 0x1300;
  static final int 	COMPILE_AND_EXECUTE		= 0x1301;
  static final int 	LIST_BASE			= 0x0B32;
  static final int 	LIST_INDEX			= 0x0B33;
  static final int 	LIST_MODE			= 0x0B30;

  /* Depth buffer */
  static final int      NEVER			= 0x0200;
  static final int 	LESS				= 0x0201;
  static final int 	GEQUAL			= 0x0206;
  static final int 	LEQUAL			= 0x0203;
  static final int 	GREATER			= 0x0204;
  static final int 	NOTEQUAL			= 0x0205;
  static final int 	EQUAL			= 0x0202;
  static final int 	ALWAYS			= 0x0207;
  static final int 	DEPTH_TEST			= 0x0B71;
  static final int 	DEPTH_BITS			= 0x0D56;
  static final int 	DEPTH_CLEAR_VALUE		= 0x0B73;
  static final int 	DEPTH_FUNC			= 0x0B74;
  static final int 	DEPTH_RANGE			= 0x0B70;
  static final int 	DEPTH_WRITEMASK		= 0x0B72;
  static final int 	DEPTH_COMPONENT		= 0x1902;

  /* Lighting */
  static final int      LIGHTING			= 0x0B50;
  static final int 	LIGHT0			= 0x4000;
  static final int 	LIGHT1			= 0x4001;
  static final int 	LIGHT2			= 0x4002;
  static final int 	LIGHT3			= 0x4003;
  static final int 	LIGHT4			= 0x4004;
  static final int 	LIGHT5			= 0x4005;
  static final int 	LIGHT6			= 0x4006;
  static final int 	LIGHT7			= 0x4007;
  static final int 	SPOT_EXPONENT		= 0x1205;
  static final int 	SPOT_CUTOFF			= 0x1206;
  static final int 	CONSTANT_ATTENUATION		= 0x1207;
  static final int 	LINEAR_ATTENUATION		= 0x1208;
  static final int 	QUADRATIC_ATTENUATION	= 0x1209;
  static final int 	AMBIENT			= 0x1200;
  static final int 	DIFFUSE			= 0x1201;
  static final int 	SPECULAR			= 0x1202;
  static final int 	SHININESS			= 0x1601;
  static final int 	EMISSION			= 0x1600;
  static final int 	POSITION			= 0x1203;
  static final int 	SPOT_DIRECTION		= 0x1204;
  static final int 	AMBIENT_AND_DIFFUSE		= 0x1602;
  static final int 	COLOR_INDEXES		        = 0x1603;
  static final int 	LIGHT_MODEL_TWO_SIDE		= 0x0B52;
  static final int 	LIGHT_MODEL_LOCAL_VIEWER	= 0x0B51;
  static final int 	LIGHT_MODEL_AMBIENT		= 0x0B53;
  static final int 	FRONT_AND_BACK		        = 0x0408;
  static final int 	SHADE_MODEL			= 0x0B54;
  static final int 	FLAT				= 0x1D00;
  static final int 	SMOOTH			        = 0x1D01;
  static final int 	COLOR_MATERIAL		        = 0x0B57;
  static final int 	COLOR_MATERIAL_FACE		= 0x0B55;
  static final int 	COLOR_MATERIAL_PARAMETER	= 0x0B56;
  static final int 	NORMALIZE			= 0x0BA1;

  /* User clipping planes */
  static final int      CLIP_PLANE0			= 0x3000;
  static final int 	CLIP_PLANE1			= 0x3001;
  static final int 	CLIP_PLANE2			= 0x3002;
  static final int 	CLIP_PLANE3			= 0x3003;
  static final int 	CLIP_PLANE4			= 0x3004;
  static final int 	CLIP_PLANE5			= 0x3005;

  /* Accumulation buffer */
  static final int      ACCUM_RED_BITS		= 0x0D58;
  static final int 	ACCUM_GREEN_BITS		= 0x0D59;
  static final int 	ACCUM_BLUE_BITS		= 0x0D5A;
  static final int 	ACCUM_ALPHA_BITS		= 0x0D5B;
  static final int 	ACCUM_CLEAR_VALUE		= 0x0B80;
  static final int 	ACCUM			= 0x0100;
  static final int 	ADD				= 0x0104;
  static final int 	LOAD				= 0x0101;
  static final int 	MULT				= 0x0103;
  static final int 	RETURN			= 0x0102;

  /* Alpha testing */
  static final int      ALPHA_TEST			= 0x0BC0;
  static final int 	ALPHA_TEST_REF		= 0x0BC2;
  static final int 	ALPHA_TEST_FUNC		= 0x0BC1;

  /* Blending */
  static final int      BLEND			= 0x0BE2;
  static final int 	BLEND_SRC			= 0x0BE1;
  static final int 	BLEND_DST			= 0x0BE0;
  static final int 	ZERO				= 0;
  static final int 	ONE				= 1;
  static final int 	SRC_COLOR			= 0x0300;
  static final int 	ONE_MINUS_SRC_COLOR		= 0x0301;
  static final int 	DST_COLOR			= 0x0306;
  static final int 	ONE_MINUS_DST_COLOR		= 0x0307;
  static final int 	SRC_ALPHA			= 0x0302;
  static final int 	ONE_MINUS_SRC_ALPHA		= 0x0303;
  static final int 	DST_ALPHA			= 0x0304;
  static final int 	ONE_MINUS_DST_ALPHA		= 0x0305;
  static final int 	SRC_ALPHA_SATURATE		= 0x0308;
  static final int 	CONSTANT_COLOR		= 0x8001;
  static final int 	ONE_MINUS_CONSTANT_COLOR	= 0x8002;
  static final int 	CONSTANT_ALPHA		= 0x8003;
  static final int 	ONE_MINUS_CONSTANT_ALPHA	= 0x8004;

  /* Render Mode */
  static final int      FEEDBACK			= 0x1C01;
  static final int 	RENDER			= 0x1C00;
  static final int 	SELECT			= 0x1C02;
  
  /* Feedback */
  static final int      GL_2D				= 0x0600;
  static final int 	GL_3D				= 0x0601;
  static final int 	GL_3D_COLOR			= 0x0602;
  static final int 	GL_3D_COLOR_TEXTURE		= 0x0603;
  static final int 	GL_4D_COLOR_TEXTURE		= 0x0604;
  static final int 	POINT_TOKEN			= 0x0701;
  static final int 	LINE_TOKEN			= 0x0702;
  static final int 	LINE_RESET_TOKEN		= 0x0707;
  static final int 	POLYGON_TOKEN		= 0x0703;
  static final int 	BITMAP_TOKEN			= 0x0704;
  static final int 	DRAW_PIXEL_TOKEN		= 0x0705;
  static final int 	COPY_PIXEL_TOKEN		= 0x0706;
  static final int 	PASS_THROUGH_TOKEN		= 0x0700;

  /* Fog */
  static final int      FOG				= 0x0B60;
  static final int 	FOG_MODE			= 0x0B65;
  static final int 	FOG_DENSITY			= 0x0B62;
  static final int 	FOG_COLOR			= 0x0B66;
  static final int 	FOG_INDEX			= 0x0B61;
  static final int 	FOG_START			= 0x0B63;
  static final int 	FOG_END			= 0x0B64;
  static final int 	LINEAR			= 0x2601;
  static final int 	EXP				= 0x0800;
  static final int 	EXP2				= 0x0801;

	/* Logic Ops */
  static final int      LOGIC_OP			= 0x0BF1;
  static final int 	LOGIC_OP_MODE		= 0x0BF0;
  static final int 	CLEAR			= 0x1500;
  static final int 	SET				= 0x150F;
  static final int 	COPY				= 0x1503;
  static final int 	COPY_INVERTED		= 0x150C;
  static final int 	NOOP				= 0x1505;
  static final int 	INVERT			= 0x150A;
  static final int 	AND				= 0x1501;
  static final int 	NAND				= 0x150E;
  static final int 	OR				= 0x1507;
  static final int 	NOR				= 0x1508;
  static final int 	XOR				= 0x1506;
  static final int 	EQUIV			= 0x1509;
  static final int 	AND_REVERSE			= 0x1502;
  static final int 	AND_INVERTED			= 0x1504;
  static final int 	OR_REVERSE			= 0x150B;
  static final int 	OR_INVERTED			= 0x150D;

  /* Stencil */
  static final int 	STENCIL_TEST			= 0x0B90;
  static final int 	STENCIL_WRITEMASK		= 0x0B98;
  static final int 	STENCIL_BITS			= 0x0D57;
  static final int 	STENCIL_FUNC			= 0x0B92;
  static final int 	STENCIL_VALUE_MASK		= 0x0B93;
  static final int 	STENCIL_REF			= 0x0B97;
  static final int 	STENCIL_FAIL			= 0x0B94;
  static final int 	STENCIL_PASS_DEPTH_PASS	= 0x0B96;
  static final int 	STENCIL_PASS_DEPTH_FAIL	= 0x0B95;
  static final int 	STENCIL_CLEAR_VALUE		= 0x0B91;
  static final int 	STENCIL_INDEX		= 0x1901;
  static final int 	KEEP				= 0x1E00;
  static final int 	REPLACE			= 0x1E01;
  static final int 	INCR				= 0x1E02;
  static final int 	DECR				= 0x1E03;

  /* Buffers; Pixel Drawing/Reading */
  static final int 	NONE				= 0;
  static final int 	LEFT				= 0x0406;
  static final int 	RIGHT			= 0x0407;
  static final int      FRONT_LEFT			= 0x0400;
  static final int 	FRONT_RIGHT			= 0x0401;
  static final int 	BACK_LEFT			= 0x0402;
  static final int 	BACK_RIGHT			= 0x0403;
  static final int 	AUX0				= 0x0409;
  static final int 	AUX1				= 0x040A;
  static final int 	AUX2				= 0x040B;
  static final int 	AUX3				= 0x040C;
  static final int 	COLOR_INDEX			= 0x1900;
  static final int 	RED				= 0x1903;
  static final int 	GREEN			= 0x1904;
  static final int 	BLUE				= 0x1905;
  static final int 	ALPHA			= 0x1906;
  static final int 	LUMINANCE			= 0x1909;
  static final int 	LUMINANCE_ALPHA		= 0x190A;
  static final int 	ALPHA_BITS			= 0x0D55;
  static final int 	RED_BITS			= 0x0D52;
  static final int 	GREEN_BITS			= 0x0D53;
  static final int 	BLUE_BITS			= 0x0D54;
  static final int 	INDEX_BITS			= 0x0D51;
  static final int 	SUBPIXEL_BITS		= 0x0D50;
  static final int 	AUX_BUFFERS			= 0x0C00;
  static final int 	READ_BUFFER			= 0x0C02;
  static final int 	DRAW_BUFFER			= 0x0C01;
  static final int 	DOUBLEBUFFER			= 0x0C32;
  static final int 	STEREO			= 0x0C33;
  static final int 	BITMAP			= 0x1A00;
  static final int 	COLOR			= 0x1800;
  static final int 	DEPTH			= 0x1801;
  static final int 	STENCIL			= 0x1802;
  static final int 	DITHER			= 0x0BD0;
  static final int 	RGB				= 0x1907;
  static final int 	RGBA				= 0x1908;

  /* Implementation limits */
  static final int      MAX_LIST_NESTING		= 0x0B31;
  static final int 	MAX_ATTRIB_STACK_DEPTH	= 0x0D35;
  static final int 	MAX_MODELVIEW_STACK_DEPTH	= 0x0D36;
  static final int 	MAX_NAME_STACK_DEPTH		= 0x0D37;
  static final int 	MAX_PROJECTION_STACK_DEPTH	= 0x0D38;
  static final int 	MAX_TEXTURE_STACK_DEPTH	= 0x0D39;
  static final int 	MAX_EVAL_ORDER		= 0x0D30;
  static final int 	MAX_LIGHTS			= 0x0D31;
  static final int 	MAX_CLIP_PLANES		= 0x0D32;
  static final int 	MAX_TEXTURE_SIZE		= 0x0D33;
  static final int 	MAX_PIXEL_MAP_TABLE		= 0x0D34;
  static final int 	MAX_VIEWPORT_DIMS		= 0x0D3A;
  static final int 	MAX_CLIENT_ATTRIB_STACK_DEPTH= 0x0D3B;

  /* Gets */
  static final int 	ATTRIB_STACK_DEPTH		= 0x0BB0;
  static final int 	COLOR_CLEAR_VALUE		= 0x0C22;
  static final int 	COLOR_WRITEMASK		= 0x0C23;
  static final int 	CURRENT_INDEX		= 0x0B01;
  static final int 	CURRENT_COLOR		= 0x0B00;
  static final int 	CURRENT_NORMAL		= 0x0B02;
  static final int 	CURRENT_RASTER_COLOR		= 0x0B04;
  static final int 	CURRENT_RASTER_DISTANCE	= 0x0B09;
  static final int 	CURRENT_RASTER_INDEX		= 0x0B05;
  static final int 	CURRENT_RASTER_POSITION	= 0x0B07;
  static final int 	CURRENT_RASTER_TEXTURE_COORDS = 0x0B06;
  static final int 	CURRENT_RASTER_POSITION_VALID = 0x0B08;
  static final int 	CURRENT_TEXTURE_COORDS	= 0x0B03;
  static final int 	INDEX_CLEAR_VALUE		= 0x0C20;
  static final int 	INDEX_MODE			= 0x0C30;
  static final int 	INDEX_WRITEMASK		= 0x0C21;
  static final int 	MODELVIEW_MATRIX		= 0x0BA6;
  static final int 	MODELVIEW_STACK_DEPTH	= 0x0BA3;
  static final int 	NAME_STACK_DEPTH		= 0x0D70;
  static final int 	PROJECTION_MATRIX		= 0x0BA7;
  static final int 	PROJECTION_STACK_DEPTH	= 0x0BA4;
  static final int 	RENDER_MODE			= 0x0C40;
  static final int 	RGBA_MODE			= 0x0C31;
  static final int 	TEXTURE_MATRIX		= 0x0BA8;
  static final int 	TEXTURE_STACK_DEPTH		= 0x0BA5;
  static final int 	VIEWPORT			= 0x0BA2;


  /* Evaluators */
  static final int 	AUTO_NORMAL			= 0x0D80;
  static final int 	MAP1_COLOR_4			= 0x0D90;
  static final int 	MAP1_GRID_DOMAIN		= 0x0DD0;
  static final int 	MAP1_GRID_SEGMENTS		= 0x0DD1;
  static final int 	MAP1_INDEX			= 0x0D91;
  static final int 	MAP1_NORMAL			= 0x0D92;
  static final int 	MAP1_TEXTURE_COORD_1		= 0x0D93;
  static final int 	MAP1_TEXTURE_COORD_2		= 0x0D94;
  static final int 	MAP1_TEXTURE_COORD_3		= 0x0D95;
  static final int 	MAP1_TEXTURE_COORD_4		= 0x0D96;
  static final int 	MAP1_VERTEX_3		= 0x0D97;
  static final int 	MAP1_VERTEX_4		= 0x0D98;
  static final int 	MAP2_COLOR_4			= 0x0DB0;
  static final int 	MAP2_GRID_DOMAIN		= 0x0DD2;
  static final int 	MAP2_GRID_SEGMENTS		= 0x0DD3;
  static final int 	MAP2_INDEX			= 0x0DB1;
  static final int 	MAP2_NORMAL			= 0x0DB2;
  static final int 	MAP2_TEXTURE_COORD_1		= 0x0DB3;
  static final int 	MAP2_TEXTURE_COORD_2		= 0x0DB4;
  static final int 	MAP2_TEXTURE_COORD_3		= 0x0DB5;
  static final int 	MAP2_TEXTURE_COORD_4		= 0x0DB6;
  static final int 	MAP2_VERTEX_3		= 0x0DB7;
  static final int 	MAP2_VERTEX_4		= 0x0DB8;
  static final int 	COEFF			= 0x0A00;
  static final int 	DOMAIN			= 0x0A02;
  static final int 	ORDER			= 0x0A01;

  /* Hints */
  static final int 	FOG_HINT			= 0x0C54;
  static final int 	LINE_SMOOTH_HINT		= 0x0C52;
  static final int 	PERSPECTIVE_CORRECTION_HINT	= 0x0C50;
  static final int 	POINT_SMOOTH_HINT		= 0x0C51;
  static final int 	POLYGON_SMOOTH_HINT		= 0x0C53;
  static final int 	DONT_CARE			= 0x1100;
  static final int 	FASTEST			= 0x1101;
  static final int 	NICEST			= 0x1102;

  /* Scissor box */
  static final int   	SCISSOR_TEST			= 0x0C11;
  static final int 	SCISSOR_BOX			= 0x0C10;

  /* Pixel Mode / Transfer */
  static final int 	MAP_COLOR			= 0x0D10;
  static final int 	MAP_STENCIL			= 0x0D11;
  static final int 	INDEX_SHIFT			= 0x0D12;
  static final int 	INDEX_OFFSET			= 0x0D13;
  static final int 	RED_SCALE			= 0x0D14;
  static final int 	RED_BIAS			= 0x0D15;
  static final int 	GREEN_SCALE			= 0x0D18;
  static final int 	GREEN_BIAS			= 0x0D19;
  static final int 	BLUE_SCALE			= 0x0D1A;
  static final int 	BLUE_BIAS			= 0x0D1B;
  static final int 	ALPHA_SCALE			= 0x0D1C;
  static final int 	ALPHA_BIAS			= 0x0D1D;
  static final int 	DEPTH_SCALE			= 0x0D1E;
  static final int 	DEPTH_BIAS			= 0x0D1F;
  static final int 	PIXEL_MAP_S_TO_S_SIZE	= 0x0CB1;
  static final int 	PIXEL_MAP_I_TO_I_SIZE	= 0x0CB0;
  static final int 	PIXEL_MAP_I_TO_R_SIZE	= 0x0CB2;
  static final int 	PIXEL_MAP_I_TO_G_SIZE	= 0x0CB3;
  static final int 	PIXEL_MAP_I_TO_B_SIZE	= 0x0CB4;
  static final int 	PIXEL_MAP_I_TO_A_SIZE	= 0x0CB5;
  static final int 	PIXEL_MAP_R_TO_R_SIZE	= 0x0CB6;
  static final int 	PIXEL_MAP_G_TO_G_SIZE	= 0x0CB7;
  static final int 	PIXEL_MAP_B_TO_B_SIZE	= 0x0CB8;
  static final int 	PIXEL_MAP_A_TO_A_SIZE	= 0x0CB9;
  static final int 	PIXEL_MAP_S_TO_S		= 0x0C71;
  static final int 	PIXEL_MAP_I_TO_I		= 0x0C70;
  static final int 	PIXEL_MAP_I_TO_R		= 0x0C72;
  static final int 	PIXEL_MAP_I_TO_G		= 0x0C73;
  static final int 	PIXEL_MAP_I_TO_B		= 0x0C74;
  static final int 	PIXEL_MAP_I_TO_A		= 0x0C75;
  static final int 	PIXEL_MAP_R_TO_R		= 0x0C76;
  static final int 	PIXEL_MAP_G_TO_G		= 0x0C77;
  static final int 	PIXEL_MAP_B_TO_B		= 0x0C78;
  static final int 	PIXEL_MAP_A_TO_A		= 0x0C79;
  static final int 	PACK_ALIGNMENT		= 0x0D05;
  static final int 	PACK_LSB_FIRST		= 0x0D01;
  static final int 	PACK_ROW_LENGTH		= 0x0D02;
  static final int 	PACK_SKIP_PIXELS		= 0x0D04;
  static final int 	PACK_SKIP_ROWS		= 0x0D03;
  static final int 	PACK_SWAP_BYTES		= 0x0D00;
  static final int 	UNPACK_ALIGNMENT		= 0x0CF5;
  static final int 	UNPACK_LSB_FIRST		= 0x0CF1;
  static final int 	UNPACK_ROW_LENGTH		= 0x0CF2;
  static final int 	UNPACK_SKIP_PIXELS		= 0x0CF4;
  static final int 	UNPACK_SKIP_ROWS		= 0x0CF3;
  static final int 	UNPACK_SWAP_BYTES		= 0x0CF0;
  static final int 	ZOOM_X			= 0x0D16;
  static final int 	ZOOM_Y			= 0x0D17;

  /* Texture mapping */	
  static final int      TEXTURE_ENV			= 0x2300;
  static final int 	TEXTURE_ENV_MODE		= 0x2200;
  static final int 	TEXTURE_1D			= 0x0DE0;
  static final int 	TEXTURE_2D			= 0x0DE1;
  static final int 	TEXTURE_WRAP_S		= 0x2802;
  static final int 	TEXTURE_WRAP_T		= 0x2803;
  static final int 	TEXTURE_MAG_FILTER		= 0x2800;
  static final int 	TEXTURE_MIN_FILTER		= 0x2801;
  static final int 	TEXTURE_ENV_COLOR		= 0x2201;
  static final int 	TEXTURE_GEN_S		= 0x0C60;
  static final int 	TEXTURE_GEN_T		= 0x0C61;
  static final int 	TEXTURE_GEN_MODE		= 0x2500;
  static final int 	TEXTURE_BORDER_COLOR		= 0x1004;
  static final int 	TEXTURE_WIDTH		= 0x1000;
  static final int 	TEXTURE_HEIGHT		= 0x1001;
  static final int 	TEXTURE_BORDER		= 0x1005;
  static final int 	TEXTURE_COMPONENTS		= 0x1003;
  static final int 	NEAREST_MIPMAP_NEAREST	= 0x2700;
  static final int 	NEAREST_MIPMAP_LINEAR	= 0x2702;
  static final int 	LINEAR_MIPMAP_NEAREST	= 0x2701;
  static final int 	LINEAR_MIPMAP_LINEAR		= 0x2703;
  static final int 	OBJECT_LINEAR		= 0x2401;
  static final int 	OBJECT_PLANE			= 0x2501;
  static final int 	EYE_LINEAR			= 0x2400;
  static final int 	EYE_PLANE			= 0x2502;
  static final int 	SPHERE_MAP			= 0x2402;
  static final int 	DECAL			= 0x2101;
  static final int 	MODULATE			= 0x2100;
  static final int 	NEAREST			= 0x2600;
  static final int 	REPEAT			= 0x2901;
  static final int 	CLAMP			= 0x2900;
  static final int 	S				= 0x2000;
  static final int 	T				= 0x2001;
  static final int 	R				= 0x2002;
  static final int 	Q				= 0x2003;
  static final int 	TEXTURE_GEN_R		= 0x0C62;
  static final int 	TEXTURE_GEN_Q		= 0x0C63;
  static final int      PROXY_TEXTURE_1D		= 0x8063;
  static final int 	PROXY_TEXTURE_2D		= 0x8064;
  static final int 	TEXTURE_PRIORITY		= 0x8066;
  static final int 	TEXTURE_RESIDENT		= 0x8067;
  static final int 	TEXTURE_1D_BINDING		= 0x8068;
  static final int 	TEXTURE_2D_BINDING		= 0x8069;

  /* Internal texture formats */
  static final int 	ALPHA4			= 0x803B;
  static final int 	ALPHA8			= 0x803C;
  static final int 	ALPHA12			= 0x803D;
  static final int 	ALPHA16			= 0x803E;
  static final int 	LUMINANCE4			= 0x803F;
  static final int 	LUMINANCE8			= 0x8040;
  static final int 	LUMINANCE12			= 0x8041;
  static final int 	LUMINANCE16			= 0x8042;
  static final int 	LUMINANCE4_ALPHA4		= 0x8043;
  static final int 	LUMINANCE6_ALPHA2		= 0x8044;
  static final int 	LUMINANCE8_ALPHA8		= 0x8045;
  static final int 	LUMINANCE12_ALPHA4		= 0x8046;
  static final int 	LUMINANCE12_ALPHA12		= 0x8047;
  static final int 	LUMINANCE16_ALPHA16		= 0x8048;
  static final int 	INTENSITY			= 0x8049;
  static final int 	INTENSITY4			= 0x804A;
  static final int 	INTENSITY8			= 0x804B;
  static final int 	INTENSITY12			= 0x804C;
  static final int 	INTENSITY16			= 0x804D;
  static final int 	R3_G3_B2			= 0x2A10;
  static final int 	RGB4				= 0x804F;
  static final int 	RGB5				= 0x8050;
  static final int 	RGB8				= 0x8051;
  static final int 	RGB10			= 0x8052;
  static final int 	RGB12			= 0x8053;
  static final int 	RGB16			= 0x8054;
  static final int 	RGBA2			= 0x8055;
  static final int 	RGBA4			= 0x8056;
  static final int 	RGB5_A1			= 0x8057;
  static final int 	RGBA8			= 0x8058;
  static final int 	RGB10_A2			= 0x8059;
  static final int 	RGBA12			= 0x805A;
  static final int 	RGBA16			= 0x805B;

  
  /* Utility */
  static final int 	VENDOR			= 0x1F00;
  static final int 	RENDERER			= 0x1F01;
  static final int 	VERSION			= 0x1F02;
  static final int 	EXTENSIONS			= 0x1F03;

  /* Errors */
  static final int 	INVALID_VALUE		= 0x0501;
  static final int 	INVALID_ENUM			= 0x0500;
  static final int 	INVALID_OPERATION		= 0x0502;
  static final int 	STACK_OVERFLOW		= 0x0503;
  static final int 	STACK_UNDERFLOW		= 0x0504;
  static final int 	OUT_OF_MEMORY		= 0x0505;

  /*
   * 1.0 Extensions
   */
  /* EXT_blend_minmax and EXT_blend_color */
  static final int 	CONSTANT_COLOR_EXT		= 0x8001;
  static final int 	ONE_MINUS_CONSTANT_COLOR_EXT	= 0x8002;
  static final int 	CONSTANT_ALPHA_EXT		= 0x8003;
  static final int 	ONE_MINUS_CONSTANT_ALPHA_EXT	= 0x8004;
  static final int 	BLEND_EQUATION_EXT		= 0x8009;
  static final int 	MIN_EXT			= 0x8007;
  static final int 	MAX_EXT			= 0x8008;
  static final int 	FUNC_ADD_EXT			= 0x8006;
  static final int 	FUNC_SUBTRACT_EXT		= 0x800A;
  static final int 	FUNC_REVERSE_SUBTRACT_EXT	= 0x800B;
  static final int 	BLEND_COLOR_EXT		= 0x8005;

  /* EXT_polygon_offset */
  static final int      POLYGON_OFFSET_EXT           = 0x8037;
  static final int      POLYGON_OFFSET_FACTOR_EXT    = 0x8038;
  static final int      POLYGON_OFFSET_BIAS_EXT      = 0x8039;
  
  /* EXT_vertex_array */
  static final int 	VERTEX_ARRAY_EXT		= 0x8074;
  static final int 	NORMAL_ARRAY_EXT		= 0x8075;
  static final int 	COLOR_ARRAY_EXT		= 0x8076;
  static final int 	INDEX_ARRAY_EXT		= 0x8077;
  static final int 	TEXTURE_COORD_ARRAY_EXT	= 0x8078;
  static final int 	EDGE_FLAG_ARRAY_EXT		= 0x8079;
  static final int 	VERTEX_ARRAY_SIZE_EXT	= 0x807A;
  static final int 	VERTEX_ARRAY_TYPE_EXT	= 0x807B;
  static final int 	VERTEX_ARRAY_STRIDE_EXT	= 0x807C;
  static final int 	VERTEX_ARRAY_COUNT_EXT	= 0x807D;
  static final int 	NORMAL_ARRAY_TYPE_EXT	= 0x807E;
  static final int 	NORMAL_ARRAY_STRIDE_EXT	= 0x807F;
  static final int 	NORMAL_ARRAY_COUNT_EXT	= 0x8080;
  static final int 	COLOR_ARRAY_SIZE_EXT		= 0x8081;
  static final int 	COLOR_ARRAY_TYPE_EXT		= 0x8082;
  static final int 	COLOR_ARRAY_STRIDE_EXT	= 0x8083;
  static final int 	COLOR_ARRAY_COUNT_EXT	= 0x8084;
  static final int 	INDEX_ARRAY_TYPE_EXT		= 0x8085;
  static final int 	INDEX_ARRAY_STRIDE_EXT	= 0x8086;
  static final int 	INDEX_ARRAY_COUNT_EXT	= 0x8087;
  static final int 	TEXTURE_COORD_ARRAY_SIZE_EXT	= 0x8088;
  static final int 	TEXTURE_COORD_ARRAY_TYPE_EXT	= 0x8089;
  static final int 	TEXTURE_COORD_ARRAY_STRIDE_EXT= 0x808A;
  static final int 	TEXTURE_COORD_ARRAY_COUNT_EXT= 0x808B;
  static final int 	EDGE_FLAG_ARRAY_STRIDE_EXT	= 0x808C;
  static final int 	EDGE_FLAG_ARRAY_COUNT_EXT	= 0x808D;
  static final int 	VERTEX_ARRAY_POINTER_EXT	= 0x808E;
  static final int 	NORMAL_ARRAY_POINTER_EXT	= 0x808F;
  static final int 	COLOR_ARRAY_POINTER_EXT	= 0x8090;
  static final int 	INDEX_ARRAY_POINTER_EXT	= 0x8091;
  static final int 	TEXTURE_COORD_ARRAY_POINTER_EXT= 0x8092;
  static final int 	EDGE_FLAG_ARRAY_POINTER_EXT	= 0x8093;
}

