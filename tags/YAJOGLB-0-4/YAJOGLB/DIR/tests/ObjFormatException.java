/*
 * Object file reader class
 *
 * $Id: ObjFormatException.java,v 1.1 2002/04/06 15:12:39 razeh Exp $
 *
 * Copyright 2001
 * Robert Allan Zeh (razeh@yahoo.com)
 */

/**
 * Thrown when the input OBJ file or material file is not in the
 * expected format.
 */
class ObjFormatException extends java.io.IOException {
  ObjFormatException(String in) {
    super(in);
  }
}

