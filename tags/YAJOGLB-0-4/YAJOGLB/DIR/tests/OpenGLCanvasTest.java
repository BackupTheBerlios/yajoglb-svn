/*
 * Copyright (c) 1995-1997 Sun Microsystems, Inc. All Rights Reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for NON-COMMERCIAL purposes and without
 * fee is hereby granted provided that this copyright notice
 * appears in all copies. Please refer to the file "copyright.html"
 * for further important copyright and licensing information.
 *
 * SUN MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NON-INFRINGEMENT. SUN SHALL NOT BE LIABLE FOR
 * ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR
 * DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */
import java.awt.*;
import java.awt.event.*;
import OpenGL.*;

/** This is a modified version of the Java tutorial class that
    demonstrates all of the different AWT objects.  We have substitued
    an OpenGLCanvas for the canvas that is normally displayed. */
public class OpenGLCanvasTest extends ExitableFrame {
    boolean inAnApplet = true;
    final String FILEDIALOGMENUITEM = "File dialog...";

    public OpenGLCanvasTest() {
        Panel bottomPanel = new Panel();
        Panel centerPanel = new Panel();
        setLayout(new BorderLayout());

        //Set up the menu bar.
        MenuBar mb = new MenuBar();
        Menu m = new Menu("Menu");
        m.add(new MenuItem("Menu item 1"));
        m.add(new CheckboxMenuItem("Menu item 2"));
        m.add(new MenuItem("Menu item 3"));
        m.add(new MenuItem("-"));
        m.add(new MenuItem(FILEDIALOGMENUITEM));
        mb.add(m);
        setMenuBar(mb);

        //Add small things at the bottom of the window.
        bottomPanel.add(new TextField("TextField"));
        bottomPanel.add(new Button("Button"));
        bottomPanel.add(new Checkbox("Checkbox"));
        Choice c = new Choice();
        c.addItem("Choice Item 1");
        c.addItem("Choice Item 2");
        c.addItem("Choice Item 3");
        bottomPanel.add(c);
        add("South", bottomPanel);

        //Add big things to the center area of the window.
        centerPanel.setLayout(new GridLayout(1,2));
        //Put a canvas in the left column.
        centerPanel.add(new Stretch());
        //Put a label and a text area in the right column.
        Panel p = new Panel();
        p.setLayout(new BorderLayout());
        p.add("North", new Label("Label", Label.CENTER));
        p.add("Center", new TextArea("TextArea", 5, 20));
        centerPanel.add(p);
        add("Center", centerPanel);

        //Put a list on the right side of the window.
        List l = new List(3, false);
        for (int i = 1; i <= 10; i++) {
            l.addItem("List item " + i);
        }
        add("East", l); 
    }

    public boolean action(Event event, Object arg) {
        //The only action event we pay attention to is when the
        //user requests we bring up a FileDialog.
        if (event.target instanceof MenuItem) {
            if (((String)arg).equals(FILEDIALOGMENUITEM)) {
                FileDialog fd = new FileDialog(this, "FileDialog");
                fd.show();
            }
        }
        return true;
    }

    public static void main(String args[]) {
      OpenGLCanvasTest window = new OpenGLCanvasTest();
        window.inAnApplet = false;

        window.setTitle("The AWT Components");
        window.pack();
        window.setVisible(true);
    }
}
