/*
 * OpenGLEvent class
 */


package OpenGL;

import java.awt.AWTEvent;

/**
 * OpenGLEvent
 *
 * This class really shouldn't be here. Ideally we would be able to
 * use the AWT event class, but we can't because it makes some
 * assumptions that are not true when we go off on our own and create
 * our windows and what not.
 */

public class OpenGLEvent extends AWTEvent {
  /**
   * The x coordinate of the event. 
   */
  public int x;
  
  /**
   * The y coordinate of the event.
   */
  public int y;

  /**
   * The type of this event.
   */
  public int id;

  /** 
   * The window opened for the very first time.
   */
  public final static int GLWINDOW_OPENED  = 1;
  /**
   * The window's size has changed. 
   */
  public final static int GLWINDOW_RESIZED = 2;
  /**
   * The window needs to be repainted. 
   */
  public final static int GLWINDOW_EXPOSED = 3;
  /**
   * A key is being held down.
   */
  public final static int GLWINDOW_KEYDOWN = 4;
  /**
   * The mouse has moved. 
   */
  public final static int GLWINDOW_MOUSEMOVE = 5;
  /**
   * The mouse button has gone down.
   */
  public final static int GLWINDOW_MOUSEDOWN = 6;
  /*
   * The mouse button has gone up.
   */
  public final static int GLWINDOW_MOUSEUP = 7;


  public int keyCode;

  /* Our keycode types.  They should correspond to the virtual key
   codes provided by Win32. */
  public final static int VK_LBUTTON      = 1;
  public final static int VK_RBUTTON      = 2;
  public final static int VK_CANCEL       = 3;
  public final static int VK_MBUTTON      = 4;
  public final static int VK_BACK = 8;
  public final static int VK_TAB  = 9;
  public final static int VK_CLEAR        = 12;
  public final static int VK_RETURN       = 13;
  public final static int VK_SHIFT        = 16;
  public final static int VK_CONTROL      = 17;
  public final static int VK_MENU = 18;
  public final static int VK_PAUSE        = 19;
  public final static int VK_CAPITAL      = 20;
  public final static int VK_ESCAPE       = 27;
  public final static int VK_SPACE        = 32;
  public final static int VK_PRIOR        = 33;
  public final static int VK_NEXT = 34;
  public final static int VK_END  = 35;
  public final static int VK_HOME = 36;
  public final static int VK_LEFT = 37;
  public final static int VK_UP   = 38;
  public final static int VK_RIGHT        = 39;
  public final static int VK_DOWN = 40;
  public final static int VK_SELECT       = 41;
  public final static int VK_PRINT        = 42;
  public final static int VK_EXECUTE      = 43;
  public final static int VK_SNAPSHOT     = 44;
  public final static int VK_INSERT       = 45;
  public final static int VK_DELETE       = 46;
  public final static int VK_HELP = 47;
  public final static int VK_0    = 48;
  public final static int VK_1    = 49;
  public final static int VK_2    = 50;
  public final static int VK_3    = 51;
  public final static int VK_4    = 52;
  public final static int VK_5    = 53;
  public final static int VK_6    = 54;
  public final static int VK_7    = 55;
  public final static int VK_8    = 56;
  public final static int VK_9    = 57;
  public final static int VK_A    = 65;
  public final static int VK_B    = 66;
  public final static int VK_C    = 67;
  public final static int VK_D    = 68;
  public final static int VK_E    = 69;
  public final static int VK_F    = 70;
  public final static int VK_G    = 71;
  public final static int VK_H    = 72;
  public final static int VK_I    = 73;
  public final static int VK_J    = 74;
  public final static int VK_K    = 75;
  public final static int VK_L    = 76;
  public final static int VK_M    = 77;
  public final static int VK_N    = 78;
  public final static int VK_O    = 79;
  public final static int VK_P    = 80;
  public final static int VK_Q    = 81;
  public final static int VK_R    = 82;
  public final static int VK_S    = 83;
  public final static int VK_T    = 84;
  public final static int VK_U    = 85;
  public final static int VK_V    = 86;
  public final static int VK_W    = 87;
  public final static int VK_X    = 88;
  public final static int VK_Y    = 89;
  public final static int VK_Z    = 90;
  public final static int VK_NUMPAD0      = 96;
  public final static int VK_NUMPAD1      = 97;
  public final static int VK_NUMPAD2      = 98;
  public final static int VK_NUMPAD3      = 99;
  public final static int VK_NUMPAD4      = 100;
  public final static int VK_NUMPAD5      = 101;
  public final static int VK_NUMPAD6      = 102;
  public final static int VK_NUMPAD7      = 103;
  public final static int VK_NUMPAD8      = 104;
  public final static int VK_NUMPAD9      = 105;
  public final static int VK_MULTIPLY     = 106;
  public final static int VK_ADD  = 107;
  public final static int VK_SEPARATOR    = 108;
  public final static int VK_SUBTRACT     = 109;
  public final static int VK_DECIMAL      = 110;
  public final static int VK_DIVIDE       = 111;
  public final static int VK_F1   = 112;
  public final static int VK_F2   = 113;
  public final static int VK_F3   = 114;
  public final static int VK_F4   = 115;
  public final static int VK_F5   = 116;
  public final static int VK_F6   = 117;
  public final static int VK_F7   = 118;
  public final static int VK_F8   = 119;
  public final static int VK_F9   = 120;
  public final static int VK_F10  = 121;
  public final static int VK_F11  = 122;
  public final static int VK_F12  = 123;
  public final static int VK_F13  = 124;
  public final static int VK_F14  = 125;
  public final static int VK_F15  = 126;
  public final static int VK_F16  = 127;
  public final static int VK_F17  = 128;
  public final static int VK_F18  = 129;
  public final static int VK_F19  = 130;
  public final static int VK_F20  = 131;
  public final static int VK_F21  = 132;
  public final static int VK_F22  = 133;
  public final static int VK_F23  = 134;
  public final static int VK_F24  = 135;
  public final static int VK_QUOTE     = 222;
  public final static int VK_SEMICOLON = 186;
  public final static int VK_PERIOD = 190;
  public final static int VK_SLASH  = 191;

  public OpenGLEvent(Object source, int id) {
    super(source, id);

    this.id = id;
  }
    
}

