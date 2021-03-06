/*
 * Frame rate panel class
 *
 * $Id$
 *
 * Copyright 2001
 * Robert Allan Zeh (razeh@yahoo.com)
 */

import java.awt.event.*;
import java.awt.*;
import java.awt.Frame;

/*
 * A simple class that brings up a panel displaying a frame rate.
 * The frame rate is set by calling the setFrameRate method.
 */
class FrameRatePanel extends Frame {
  /// Used to display our frameRate.
  Button frameRate;

  class WindowListener extends java.awt.event.WindowAdapter {
    public void windowClosing(WindowEvent e) {
      dispose();
    }
  }
 
  public FrameRatePanel() {
    super();
    addWindowListener(new WindowListener());
    

    setLayout(new GridLayout(1,1));
    frameRate = new Button("Frame rate");
    add(frameRate);

    setTitle("Frame rate");
    setSize(new Dimension(300, 200));
    setVisible(true);
  }

  /** Update the displayed frame rate.
   * @param rate the new rate. 
   */
  public void setFrameRate(double rate) {
    frameRate.setLabel("Frame rate: " + rate + " / second");
  }

}
