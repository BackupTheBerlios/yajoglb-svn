/*
 * Material file reader class
 *
 * $Id$
 *
 * Copyright 2002
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import java.lang.String;
import java.lang.Float;
import java.lang.Integer;
import java.io.*;
import java.util.*;
import java.io.IOException;
import java.io.IOException.*;

/** This reads in material files.
 */
class ObjMaterialReader {
  /** The line number in the file we are on. */
  private LineNumberReader reader;
  /** Where the materials are stored. */
  private OBJ obj;
  /** The file we are reading. */
  private String filename;

  /** Construct a material reader. 
   * @param fn the filename to read.
   * @param o the OBJ to store the materials.
   */
  ObjMaterialReader(String fn, OBJ o) throws IOException, 
					     FileNotFoundException {
    filename = fn;
    obj = o;
    reader = new LineNumberReader(new InputStreamReader(new FileInputStream(fn)));
    readFile();
  }

  /** 
   * Read in a material. 
   * @param materialTokenizer the tokenizer for the material.
   */
  protected void readMaterial(StringTokenizer materialTokenizer) throws 
    ObjFormatException, IOException {
    String name;
    float ambient_r = 0.0f, ambient_g = 0.0f, ambient_b = 0.0f;
    float diffuse_r = 0.0f, diffuse_g = 0.0f, diffuse_b = 0.0f;
    float specular_r = 0.0f, specular_g = 0.0f, specular_b = 0.0f;
    float specularHighlight = 0.0f;      
    
    if (materialTokenizer.hasMoreTokens()) {
      name = materialTokenizer.nextToken();
    } else {
      throw new ObjFormatException("Missing material name at line "
				    + reader.getLineNumber()
				    + "in " + filename);
    }
    
    for(;;) {
      String line = reader.readLine();
      if (line == null) {
	obj.addElement(new ObjMaterial(name, 
				       ambient_r, ambient_g, ambient_b,
				       diffuse_r, diffuse_g, diffuse_b,
				       specular_r, specular_g, specular_b,
				       specularHighlight));
	return;
      }
      StringTokenizer tokenizer = new StringTokenizer(line);
      if (tokenizer.hasMoreTokens()) {
	String command = tokenizer.nextToken();
	if (command.compareTo("#") == 0) {
	  continue;
	}
	if (command.compareTo("Ka") == 0) {
	  if (tokenizer.hasMoreTokens())
	    ambient_r = Float.parseFloat(tokenizer.nextToken());
	  else {
	    throw new ObjFormatException("Missing token at line " 
					 + reader.getLineNumber()
					 + "in " + filename);
	  }
	  if (tokenizer.hasMoreTokens())
	    ambient_g = Float.parseFloat(tokenizer.nextToken());
	  else {
	    throw new ObjFormatException("Missing token at line " 
					 + reader.getLineNumber()
					 + "in " + filename);
	  }
	  if (tokenizer.hasMoreTokens())
	    ambient_b = Float.parseFloat(tokenizer.nextToken());
	  else {
	    throw new ObjFormatException("Missing token at line " 
					 + reader.getLineNumber()
					 + "in " + filename);
	  }
	}
	if (command.compareTo("Kd") == 0) {
	  if (tokenizer.hasMoreTokens())
	    diffuse_r = Float.parseFloat(tokenizer.nextToken());
	  else {
	    throw new ObjFormatException("Missing token at line " 
					 + reader.getLineNumber()
					 + "in " + filename);
	  }
	  if (tokenizer.hasMoreTokens())
	    diffuse_g = Float.parseFloat(tokenizer.nextToken());
	  else {
	    throw new ObjFormatException("Missing token at line " 
					 + reader.getLineNumber()
					 + "in " + filename);
	  }
	  if (tokenizer.hasMoreTokens())
	    diffuse_b = Float.parseFloat(tokenizer.nextToken());
	  else {
	    throw new ObjFormatException("Missing token at line " 
					 + reader.getLineNumber()
					 + "in " + filename);
	  }
	}
	if (command.compareTo("Ks") == 0) {
	  if (tokenizer.hasMoreTokens())
	    specular_r = Float.parseFloat(tokenizer.nextToken());
	  else {
	    throw new ObjFormatException("Missing token at line " 
					 + reader.getLineNumber()
					 + "in " + filename);
	  }
	  if (tokenizer.hasMoreTokens())
	    specular_g = Float.parseFloat(tokenizer.nextToken());
	  else {
	    throw new ObjFormatException("Missing token at line " 
					 + reader.getLineNumber()
					 + "in " + filename);
	  }
	  if (tokenizer.hasMoreTokens())
	    specular_b = Float.parseFloat(tokenizer.nextToken());
	  else {
	    throw new ObjFormatException("Missing token at line " 
					 + reader.getLineNumber()
					 + "in " + filename);
	  }
	}
	if (command.compareTo("Ns") == 0) {
	  if (tokenizer.hasMoreTokens())
	    specularHighlight = Float.parseFloat(tokenizer.nextToken());
	  else {
	    throw new ObjFormatException("Missing token at line " 
					 + reader.getLineNumber()
					 + "in " + filename);
	  }
	}
	if (command.compareTo("newmtl") == 0) {
	  obj.addElement(new ObjMaterial(name, 
					 ambient_r, ambient_g, ambient_b,
					 diffuse_r, diffuse_g, diffuse_b,
					 specular_r, specular_g, specular_b,
					 specularHighlight));
	  // Package up the material we've read so far.
	  readMaterial(tokenizer);
	}
      }
    }
  }

  /** Go through all of the lines in a file and parse out any
   * Wavefront newmtl commands.
   */
  protected void readFile() throws IOException {
    String line;

    for(;;) {
      line = reader.readLine();
      if (line == null)
	break;
      StringTokenizer tokenizer = new StringTokenizer(line);
      
      if (tokenizer.hasMoreTokens()) {
	String command = tokenizer.nextToken();
	if (command.compareTo("#") == 0) {
	  continue;
	}
	
	if (command.compareTo("newmtl") == 0) {
	  readMaterial(tokenizer);
	}
      }
    }
  }

  public static void main(String args[]) {
    try {
      OBJ obj = new OBJ();
      ObjMaterialReader rdr = new ObjMaterialReader(args[0], obj);
    } catch (FileNotFoundException ex) {
      System.err.println("Unable to find " + args[0]);
    } catch (IOException ex) {
      System.err.println(ex);
    }
  }

}
