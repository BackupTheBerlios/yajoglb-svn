/*
 * OpenGLTextureHelp.java
 *
 * $Id: TextureHelp.java,v 1.3 1998/10/20 00:56:32 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/**
 * OpenGLTextureHelp.java
 *
 * This defines some methods that make it easier to manage textures.
 *
 * @author Robert Allan Zeh (razeh@balr.com) 
 *
 * @version 0.1
 */

public class OpenGLTextureHelp {

  /** Create a 2D texture from the TGA file for textureID.
   * @param gl the OpenGL GL object to use.
   * @param glu the OpenGL GLU object to use for building the 2D Mipmaps.
   * @param textureID the texture to bind the TGA raster to.
   * @param fileName the TGA filename to read.
   */
  public static void createTextureForTGAFile(GL gl, GLU glu,
					     int textureID,
					     String fileName) {

    gl.bindTexture(gl.TEXTURE_2D, textureID);
    TGAFile tga = new TGAFile(fileName);
    glu.gluBuild2DMipmaps(gl.TEXTURE_2D, 4, tga.getSize().width, tga.getSize().height,
			  gl.RGBA, gl.GL_UNSIGNED_BYTE, tga.getData());

    gl.texParameter(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.REPEAT);
    gl.texParameter(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.REPEAT);
    gl.texParameter(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    gl.texParameter(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, 
		    gl.LINEAR_MIPMAP_NEAREST);
    gl.texEnv(gl.TEXTURE_ENV, gl.TEXTURE_ENV_MODE,
	      gl.MODULATE);
  }
  
}
