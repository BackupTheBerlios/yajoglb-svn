/* 
 * Info panel class
 *
 * $Id: InfoPanel.java,v 1.3 2001/06/10 19:14:42 razeh Exp $
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


