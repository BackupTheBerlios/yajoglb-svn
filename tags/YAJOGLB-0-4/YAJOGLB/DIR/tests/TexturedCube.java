/*
 * Textured cube
 *
 * $Id: TexturedCube.java,v 1.5 2002/07/21 16:56:50 razeh Exp $
 * 
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import OpenGL.*;
import java.awt.*;

/** This draws a simple textured cube, rotate 30 degress from each
    axis, with normal pointers. */

public class TexturedCube implements GeometryObject, GLConstants {
  float[] material = { 0.0f, 0.5f, 0.5f, 0.5f };
  int[] textureIDs;

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    gl.pushMatrix();

    gl.enable(LIGHT0);
    gl.enable(LIGHTING);
    gl.rotate(30.0f, 1.0f, 1.0f, 1.0f);
    gl.material(FRONT_AND_BACK, AMBIENT_AND_DIFFUSE, material);

    float texScale = 1.f;
    gl.color(0.0, 1.0, 0.0);
    gl.bindTexture(TEXTURE_2D, textureIDs[0]);
    gl.begin(QUADS);

    gl.normal( 0.0F, 0.0F, 1.0F);
    gl.texCoord(0.f, 0.f);
    gl.vertex( 0.5F, 0.5F, 0.5F); 
    gl.texCoord(0.f, texScale);
    gl.vertex(-0.5F, 0.5F, 0.5F);
    gl.texCoord(texScale, texScale);
    gl.vertex(-0.5F,-0.5F, 0.5F); 
    gl.texCoord(texScale, 0.f);
    gl.vertex( 0.5F,-0.5F, 0.5F);
    
    texScale = 0.5f;
    gl.normal( 0.0F, 0.0F,-1.0F);
    gl.texCoord(0.f, 0.f);
    gl.vertex(-0.5F,-0.5F,-0.5F);
    gl.texCoord(0.f, texScale);
    gl.vertex(-0.5F, 0.5F,-0.5F);
    gl.texCoord(texScale, texScale);
    gl.vertex( 0.5F, 0.5F,-0.5F); 
    gl.texCoord(texScale, 0.f);
    gl.vertex( 0.5F,-0.5F,-0.5F);

    texScale = 2.0f;
    gl.normal( 0.0F, 1.0F, 0.0F);
    gl.texCoord(0.f, 0.f);
    gl.vertex( 0.5F, 0.5F, 0.5F); 
    gl.texCoord(0.f, texScale);
    gl.vertex( 0.5F, 0.5F,-0.5F);
    gl.texCoord(texScale, texScale);
    gl.vertex(-0.5F, 0.5F,-0.5F); 
    gl.texCoord(texScale, 0.f);
    gl.vertex(-0.5F, 0.5F, 0.5F);

    gl.normal( 0.0F,-1.0F, 0.0F);
    gl.vertex(-0.5F,-0.5F,-0.5F); gl.vertex( 0.5F,-0.5F,-0.5F);
    gl.vertex( 0.5F,-0.5F, 0.5F); gl.vertex(-0.5F,-0.5F, 0.5F);

    gl.normal( 1.0F, 0.0F, 0.0F);
    gl.vertex( 0.5F, 0.5F, 0.5F); gl.vertex( 0.5F,-0.5F, 0.5F);
    gl.vertex( 0.5F,-0.5F,-0.5F); gl.vertex( 0.5F, 0.5F,-0.5F);

    gl.normal(-1.0F, 0.0F, 0.0F);
    gl.vertex(-0.5F,-0.5F,-0.5F); gl.vertex(-0.5F,-0.5F, 0.5F);
    gl.vertex(-0.5F, 0.5F, 0.5F); gl.vertex(-0.5F, 0.5F,-0.5F);
    gl.end();
  
    gl.popMatrix();
  }

  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    gl.enable(TEXTURE_2D);
    textureIDs = new int[3];
    gl.genTextures(textureIDs);
    TextureHelp.createTextureForTGAFile(gl, glu,
					textureIDs[0], "ogl.tga");
  }
  

  public static void main(String args[]) {
    TexturedCube cube     = new TexturedCube();
    GeometryViewer viewer = new GeometryViewer();
    ExitableFrame  frame  = new ExitableFrame();
    
    viewer.addElement(cube);
    viewer.addElement(new Axis());
    frame.setLayout(new GridLayout(1,1));
    frame.add(viewer);
    frame.setTitle("A textured cube");
    frame.pack();
    frame.setSize(new Dimension(400,400));
    frame.setBackground(java.awt.Color.black);
    frame.setVisible(true);
  }
}

