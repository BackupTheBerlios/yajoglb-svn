/* 
 * Info panel class
 *
 * $Id: InfoPanel.java,v 1.1 1999/05/02 23:31:00 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

import java.util.StringTokenizer;
import java.awt.*;
import OpenGL.*;

/** A simple class that brings up a panel describing what it can about the
 * current OpenGL implementation.
 */
class InfoPanel extends Frame implements GLConstants {
  public InfoPanel(GL gl) {
    super();
    Panel panel = new Panel();
    Panel extensionsPanel = new Panel();
    
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
    setSize(new Dimension(400, 400));
    setVisible(true);
  }
}


