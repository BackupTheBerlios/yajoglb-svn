package OpenGL;

/** OpenGLTextureHelp
 *
 * This defines some methods that make it easier to manage textures.
 *
 * @author Robert Allan Zeh (razeh@balr.com) 
 */

public class OpenGLTextureHelp {

  public static void createTextureForTGAFile(OpenGL.OpenGLWidget gl, int textureID,
				      String fileName) {

    gl.bindTexture(gl.TEXTURE_2D, textureID);
    TGAFile tga = new TGAFile(fileName, 128, 128);
    gl.build2DMipmaps(gl.TEXTURE_2D, 4, tga.width(), tga.height(),
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
