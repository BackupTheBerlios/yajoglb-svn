/*
  Helper routines for texture methods.
 
  Copyright 2001, Robert Allan Zeh (razeh@yahoo.com)
  7346 Lake Street #3W
  River Forest, IL 60305
 
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA

*/

/*
 * TextureHelp.java
 *
 * $Id$
 *
 */

package OpenGL;

/**
 * TextureHelp.java
 *
 * This defines some methods that make it easier to manage textures.
 *
 * @author Robert Allan Zeh (razeh@yahoo.com) 
 *
 * @version 0.4
 */

public class TextureHelp {

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
