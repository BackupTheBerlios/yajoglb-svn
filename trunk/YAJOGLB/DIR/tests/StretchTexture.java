/*
 * StetchTexture class
 *
 * $Id: StretchTexture.java,v 1.2 2002/04/06 15:12:59 razeh Exp $
 *
 * Copyright 2001
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 */


import java.awt.*;
import OpenGL.*;
import java.awt.event.*;

/**
 * This acts just like the stretch demo, but with a texture map instead
 * of gluScaleImage.
 */
public class StretchTexture extends Stretch
    implements GLUConstants, GLConstants, MouseListener, MouseMotionListener, ComponentListener {

    int[] textureIDs;

    protected void rescale() {
	// Do nothing, since we let the texture mapping rescale the image
	// for us.
    }

    synchronized public void paint() {
	aquireContext();

	// Instead of flipping the image, we flip the texture coordinates.
	float texScale = 1.f;
	gl.clear(COLOR_BUFFER_BIT);
	gl.bindTexture(TEXTURE_2D, textureIDs[0]);
	gl.begin(QUADS);

	gl.texCoord(0.f, texScale);
	gl.vertex(0, 0);

	gl.texCoord(0.f, 0.f);
	gl.vertex(0, getImageSizeY());

	gl.texCoord(texScale, 0.f);
	gl.vertex(getImageSizeX(), getImageSizeY());

	gl.texCoord(texScale, texScale);
	gl.vertex(getImageSizeX(), 0);
	gl.end();

	System.out.println("x = " + getImageSizeX());
	System.out.println("y = " + getImageSizeY());
	swapBuffers();
	releaseContext();
    }

    /**
     * Resize our component, and reset our project matrix so that we
     * are still directly mapping pixels to coordinates.
     */
    public void lockedComponentResized(ComponentEvent e) {
	super.lockedComponentResized(e);
	if (context != null) {
	    aquireContext();
	    gl.matrixMode(PROJECTION);
	    gl.loadIdentity();
	    glu.gluOrtho2D(0, getSize().width, 0, getSize().height);
	    gl.matrixMode(MODELVIEW);
	    releaseContext();
	}
    }

    public void glInit() {
	super.glInit();
	aquireContext();
	gl.enable(TEXTURE_2D);
	textureIDs = new int[3];
	gl.genTextures(textureIDs);
	TextureHelp.createTextureForTGAFile(gl, glu,
					    textureIDs[0], "ogl.tga");
	releaseContext();
    }

    
    public static void main(String args[]) {
	StretchTexture canvas = new StretchTexture();
	ExitableFrame frame = new ExitableFrame();

	frame.setBackground(java.awt.Color.black);
	frame.setLayout(new GridLayout(1,1));
	frame.add(canvas);
	frame.setSize(new Dimension(100,100));
	frame.setTitle("Stretch texture test");
	frame.setVisible(true);
    }
}
