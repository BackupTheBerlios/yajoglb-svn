/*
 * NativePackageLoader class
 *
 * $Id: NativePackageLoader.java,v 1.1 1999/04/29 01:17:14 razeh Exp $
 *
 * Copyright 1999
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/** Handles loading the native library into memory.  Our single method is
 * called by all of our class files when they are loaded to make sure that
 * our native library is loaded.
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 * 
 * @version 0.3
 */

class NativePackageLoader {

  /** Loads the native library. */
  static void loadNativeLibrary() {
    System.load("YAJOGLB");
  }
}
