/*
 * A rotating texture mapped sphere.
 *
 * $Id$
 *
 * Copyright 2002
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import OpenGL.*;
import java.awt.*;

public class TexturedSphere extends Sphere {
  int[] textureIDs;
  double angle, x, y, z;
  String textureFile;

  TexturedSphere(String tf) {
    textureFile = tf;
    setSlices(getSlices() *5);
    setStacks(getStacks() *5);
  }
  void setAngle(double a) { angle = a; }

  public void paint(GeometryViewer viewer, GL gl, GLU glu) {
    gl.pushMatrix();
    gl.bindTexture(TEXTURE_2D, textureIDs[0]);
    gl.rotate(angle, 0.0, 0.0, 1.0);
    super.paint(viewer, gl, glu);
    gl.popMatrix();
  }

  public void glInit(GeometryViewer viewer, GL gl, GLU glu) {
    super.glInit(viewer, gl, glu);
    gl.enable(TEXTURE_2D);
    textureIDs = new int[3];
    gl.genTextures(textureIDs);
    TextureHelp.createTextureForTGAFile(gl, glu,
					textureIDs[0], textureFile);
    texture(true);
  }

  public static void main(String args[]) {
    String filename = "earth.tga";
    if (args.length >= 1) {
      filename = args[0];
    }

    TexturedSphere sphere = new TexturedSphere(filename);
    GeometryViewer viewer = new GeometryViewer();
    ExitableFrame  frame  = new ExitableFrame();

    viewer.addElement(sphere);
    frame.setLayout(new GridLayout(1,1));
    frame.add(viewer);
    frame.setTitle("A textured sphere");
    frame.pack();
    frame.setSize(new Dimension(400,400));
    frame.setBackground(java.awt.Color.black);
    frame.setVisible(true);

    double angle = 0;
    while (true) {
      try {
	Thread.sleep(10);
      } catch (InterruptedException e) {
	;
      }
      sphere.setAngle(angle);
      angle = angle - 1;
      if (angle < -360) {
	angle = 0;
      }
      viewer.nativePaint();
    }
  }
}
