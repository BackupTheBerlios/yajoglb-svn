/*
 * ExitableFrame class
 *
 * $Id: ExitableFrame.java,v 1.2 2001/06/10 19:13:34 razeh Exp $
 *
 * Copyright 1998
 *
 * Robert Allan Zeh (razeh@yahoo.com)
 *
 */

import java.awt.Frame;
import java.awt.event.*;

/** This extends the Frame class so that we can put up a window that
    can be exited. */
class ExitableFrame extends Frame {

  class WindowListener extends java.awt.event.WindowAdapter {
    public void windowClosing(WindowEvent e) {
      System.exit(0);
    }
  }

  public ExitableFrame() {
    addWindowListener(new WindowListener());
  }
  
  public ExitableFrame(String title) {
    addWindowListener(new WindowListener());
  }
}
