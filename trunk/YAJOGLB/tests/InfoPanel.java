/* 
 * Info panel class
 *
 * $Id$
 *
 * Copyright 2001
 * Robert Allan Zeh (razeh@yahoo.com)
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
  
  /** Brings up a panel and populates it with information from gl.
   * @param gl the OpenGL object to extract information from.
   */
  public InfoPanel(GL gl) {
    super();
    addWindowListener(new WindowListener());

    // Get all of our gl information.
    String vendor = gl.getString(VENDOR);
    String renderer = gl.getString(RENDERER);
    String version = gl.getString(VERSION);
    String extensions = gl.getString(EXTENSIONS);

    TextArea textArea = new TextArea();
    textArea.setEditable(false);
    setLayout(new GridLayout(1,1));
    add(textArea);
    
    textArea.append("Vendor: " + vendor + "\n");
    textArea.append("Renderer: " + renderer + "\n");
    textArea.append("Version: " + version + "\n");
    textArea.append("Extensions:\n");

    StringTokenizer st = new StringTokenizer(extensions);
    while (st.hasMoreTokens()) {
	textArea.append(st.nextToken() + "\n");
    }
    setTitle("OpenGL driver information");
    setSize(new Dimension(400, 300));
    setVisible(true);
  }
}


