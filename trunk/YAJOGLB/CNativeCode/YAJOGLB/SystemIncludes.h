/*
 * SystemIncludes.h
 * 
 * $Id$
 *
 * Some systems need to always include headers, like <windows.h>.  These
 * are handled here.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

/* Make sure that we are only included once. */
#ifndef _SYSTEMINCLUDES_H
#define _SYSTEMINCLUDES_H


/* If we are in Windows include <windows.h> */
#ifdef WIN32
#include <windows.h>
/* I'd prefer variable length arrays to alloca, but
   visual C++ doesn't support variable length arrays. */
#define alloca _alloca
#endif

/* We might need to redefine the quadrics, tesselators and nurbs. */
#ifdef __APPLE__
 #include <OpenGL/GLU.h>
 #include <JavaVM/jawt.h>
 #define _GLUfuncptr GLvoid (*)()
#else
 #include <GL/glu.h> // does glu.h include glu.h?
 #include <GL/gl.h>
#endif
#ifndef GLU_VERSION_1_2
typedef struct GLUquadricObj GLUquadric;
typedef struct GLUtriangulatorObj GLUtesselator;
typedef struct GLUnurbsObj GLUnurbs;
#endif /* GLU_VERSION_1_2 */

#endif /* _SYSTEMINCLUDES_H */
