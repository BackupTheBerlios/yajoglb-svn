/*
 * Object file reader class
 *
 * $Id$
 *
 * Copyright 2001
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import java.lang.String;
import java.lang.Double;
import java.lang.Integer;
import java.io.*;
import java.util.*;

/**
 * This reads in OBJ files.
 */
class ObjReader {
  /** Used to read in the file. */
  private LineNumberReader reader;
  /** Where the obj is stored. */
  private OBJ obj = new OBJ();
  /** The name of the file we are reading. */
  private String filename;

  /** Read in a obj file.
   * @param fn the name of the file to read in.
   */
  ObjReader(String fn) throws FileNotFoundException, IOException {
    filename = fn;
    reader = new LineNumberReader(new InputStreamReader(new FileInputStream(filename)));
    readFile();
  }

  /** Read a vertex and add it to our obj.
   * @param tokenzier our tokenizer. 
   */
  protected void readVertex(StringTokenizer tokenizer) {
    double x = 0.0, y = 0.0, z = 0.0, w = 0.0;
    if (tokenizer.hasMoreTokens())
      x = Double.parseDouble(tokenizer.nextToken());

    if (tokenizer.hasMoreTokens()) 
      y = Double.parseDouble(tokenizer.nextToken());

    if (tokenizer.hasMoreTokens()) 
      z = Double.parseDouble(tokenizer.nextToken());

    if (tokenizer.hasMoreTokens()) 
      w = Double.parseDouble(tokenizer.nextToken());

    obj.addElement(new ObjVertex(x, y, z, w));
  }

  /** Read a normal and add it to our obj.
   * @param tokenzier our tokenizer. 
   */
  protected void readNormal(StringTokenizer tokenizer) {
    double x = 0.0, y = 0.0, z = 0.0;
    if (tokenizer.hasMoreTokens())
      x = Double.parseDouble(tokenizer.nextToken());

    if (tokenizer.hasMoreTokens()) 
      y = Double.parseDouble(tokenizer.nextToken());

    if (tokenizer.hasMoreTokens()) 
      z = Double.parseDouble(tokenizer.nextToken());

    obj.addElement(new ObjNormal(x, y, z));
  }

  /** Read a face and add it to our obj.
   * @param tokenzier our tokenizer. 
   */
  protected void readFace(StringTokenizer tokenizer) 
    throws ObjFormatException {
    ObjFace face = new ObjFace(obj);
    while (tokenizer.hasMoreTokens()) {
      StringTokenizer t = new StringTokenizer(tokenizer.nextToken(),
					      "/", true);
      int v = -1, vt = -1, vn = -1;
      if (t.hasMoreTokens()) {
	v = Integer.parseInt(t.nextToken());
      }
      
      // The next token must be a slash.
      if (t.hasMoreTokens()) {
	String next = t.nextToken();
	if (next.compareTo("/") != 0) {
	  throw new ObjFormatException("Expected a slash at line "
				       + reader.getLineNumber());
	}
      }
      
      // If the next token is a number, then we have a
      // texture vertex to read.  If it is a slash, then
      // we should skip ahead to the normal.
      if (t.hasMoreTokens()) {
	String next = t.nextToken();
	if (next.compareTo("/") != 0)
	  vt = Integer.parseInt(next);
      }
      
      if (t.hasMoreTokens()) {
	vn = Integer.parseInt(t.nextToken());
      }
      face.add(v, vt, vn);
    }
    obj.addElement(face);
  }

  /** Read a material file and add it to our obj.
   * @param tokenzier our tokenizer. 
   */
  protected void readMaterialLibrary(StringTokenizer tokenizer) 
    throws IOException, ObjFormatException {
    String libraryName;
    if (tokenizer.hasMoreTokens())
      libraryName = tokenizer.nextToken();
    else {
      throw new ObjFormatException("Missing material library name at line "
				   + reader.getLineNumber());
    }
    // Now we need to make sure that libraryName is in the
    // same directory as the filename we were supplied with.
    File objfile = new File(filename);
    if (objfile.getParentFile() != null) {
      File mtlfile = new File(objfile.getParentFile(), libraryName);
      System.out.println("parent file = " + objfile.getParentFile());
      libraryName = mtlfile.getPath();
    }
    new ObjMaterialReader(libraryName, obj);
  }

  /** Read in an actual material usage (which is different from
   * the definition) and add it to our obj.
   * @param tokenizer our tokenizer. 
   */
  protected void readUseMaterial(StringTokenizer tokenizer) {
    String material = null;
    if (tokenizer.hasMoreTokens()) {
      material = tokenizer.nextToken();
      obj.addElement((ObjDrawable)obj.getMaterial(material));
    }
  }

  /** Read in our file and add all of the OBJ objects to our
   * obj. 
   */
  protected OBJ readFile() throws IOException {
    String line;

    for(;;) {
      line = reader.readLine();
      if (line == null)
	break;
      StringTokenizer tokenizer = new StringTokenizer(line);
      
      // Figure out what the command is.
      if (tokenizer.hasMoreTokens()) {
	String command = tokenizer.nextToken();
	if (command.compareTo("#") == 0) {
	  continue;
	}
	if (command.compareTo("v") == 0) {
	  readVertex(tokenizer);
	}
	if (command.compareTo("f") == 0) {
	  readFace(tokenizer);
	}
	if (command.compareTo("vn") == 0) {
	  readNormal(tokenizer);
	}
	if (command.compareTo("mtllib") == 0) {
	  readMaterialLibrary(tokenizer);
	}
	if (command.compareTo("usemtl") == 0) {
	  readUseMaterial(tokenizer);
	}
      }
    }
    return obj; 
  }
    
  public static void main(String args[]) {
    try {
      ObjReader obj = new ObjReader(args[0]);
    } catch (FileNotFoundException ex) {
      System.err.println("Unable to find " + args[0]);
    } catch (IOException ex) {
      System.err.println(ex);
    }
  }

}
