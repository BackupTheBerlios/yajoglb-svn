/*
 * Object file reader class
 *
 * $Id$
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

