/* 
 * Info panel class
 *
 * $Id: InfoPanel.java,v 1.2 1999/05/08 19:17:53 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

import java.util.StringTokenizer;
import java.awt.event.*;
import java.awt.*;
import OpenGL.*;
import java.awt.Frame;

/** A simple class that brings up a panel describing what it can about the
 * current OpenGL implementation.
 */
class InfoPanel extends Frame implements GLConstants {


  class WindowListener extends java.awt.event.WindowAdapter {
    public void windowClosing(WindowEvent e) {
      dispose();
    }
  }
  
  public InfoPanel(GL gl) {
    super();
    Panel panel = new Panel();
    Panel extensionsPanel = new Panel();

    addWindowListener(new WindowListener());
    add(panel);
    add(extensionsPanel);

    // Get all of our gl information.
    String vendor = gl.getString(VENDOR);
    String renderer = gl.getString(RENDERER);
    String version = gl.getString(VERSION);
    String extensions = gl.getString(EXTENSIONS);

    setLayout(new GridLayout(2,1));
    panel.setLayout(new GridLayout(4,1));
    panel.add(new Label("Vendor: " + vendor));
    panel.add(new Label("Renderer: " + renderer));
    panel.add(new Label("Version: " + version));
    panel.add(new Label("Extensions: "));

    StringTokenizer st = new StringTokenizer(extensions);
    while (st.hasMoreTokens()) {
      extensionsPanel.add(new Label(st.nextToken()));
    }

    setTitle("OpenGL driver information");
    setSize(new Dimension(400, 300));
    setVisible(true);
  }
}


