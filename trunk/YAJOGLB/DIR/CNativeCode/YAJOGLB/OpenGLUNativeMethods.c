/*
 * OpenGLUNativeMethods.c
 *
 * $Id: OpenGLUNativeMethods.c,v 1.2 1998/11/01 21:42:58 razeh Exp $
 *
 * This implements the native method portions of the GLU library.
 * Quadrics are handled by the java CHeapItem class, which stores each
 * quadric as an integer.  When we receive a quadric for these native
 * methods we simply cast the integer into a void pointer.
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com) 
*/


