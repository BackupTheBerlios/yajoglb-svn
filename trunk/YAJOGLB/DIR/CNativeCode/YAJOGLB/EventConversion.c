/*
 * EventConversion.c
 *
 * This handles converting window 32 character key codes into ones
 * that java understands.
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@yahoo.com) 
 */

#include <windows.h>
#include "cygnusFixes.h"
#include "JNIInterface.h"
#include "EventConversion.h"

/* This converts a windows 32 character key code into one that the
   Java runtime will understand.  We use the JNI method lookup to get
   our Java constants. */
int win32CharacterToJava(JNIEnv *env, jclass class,
			 int character) {

  int win32Character = character;

  switch(character) {
  case VK_HOME:
    lookupStaticIntField(env, class,
			 "VK_HOME", &win32Character);
    break;
  case VK_END:
    lookupStaticIntField(env, class,
			 "VK_END", &win32Character);
    break;
  case VK_PRIOR:
    lookupStaticIntField(env, class,
			 "VK_PGUP", &win32Character);
    break;
  case VK_NEXT:
    lookupStaticIntField(env, class,
			 "VK_NEXT", &win32Character);
    break;
  case VK_UP:
    lookupStaticIntField(env, class,
			 "VK_UP", &win32Character);
    break;
  case VK_DOWN:
    lookupStaticIntField(env, class,
			 "VK_DOWN", &win32Character);
    break;
  case VK_RIGHT:
    lookupStaticIntField(env, class,
			 "VK_RIGHT", &win32Character);
    break;
  case VK_LEFT:
    lookupStaticIntField(env, class,
			 "VK_LEFT", &win32Character);
    break;
  case VK_F1:
    lookupStaticIntField(env, class,
			 "VK_F1", &win32Character);
    break;
  case VK_F2:
    lookupStaticIntField(env, class,
			 "VK_F2", &win32Character);
    break;
  case VK_F3:
    lookupStaticIntField(env, class,
			 "VK_F3", &win32Character);
    break;
  case VK_F4:
    lookupStaticIntField(env, class,
			 "VK_F4", &win32Character);
    break;
  case VK_F5:
    lookupStaticIntField(env, class,
			 "VK_F5", &win32Character);
    break;
  case VK_F6:
    lookupStaticIntField(env, class,
			 "VK_F6", &win32Character);
    break;
  case VK_F7:
    lookupStaticIntField(env, class,
			 "VK_F7", &win32Character);
    break;
  case VK_F8:
    lookupStaticIntField(env, class,
			 "VK_F8", &win32Character);
    break;
  case VK_F9:
    lookupStaticIntField(env, class,
			 "VK_F9", &win32Character);
    break;
  case VK_F10:
    lookupStaticIntField(env, class,
			 "VK_F10", &win32Character);
    break;
  case VK_F11:
    lookupStaticIntField(env, class,
			 "VK_F11", &win32Character);
    break;
  case VK_F12:
    lookupStaticIntField(env, class,
			 "VK_F12", &win32Character);
    break;
  case VK_DIVIDE:
    lookupStaticIntField(env, class,
			 "VK_DIVIDE", &win32Character);
    break;
  case VK_SHIFT:
    lookupStaticIntField(env, class,
			 "VK_SHIFT", &win32Character);
    break;
    case VK_RETURN:
      win32Character = '\n';
      break;
  case VK_DELETE:
    win32Character = '\177';
    break;
  default:
    break;
  }

  return win32Character;
}
    

// Converts Windows modifier bits to awt modifier bits.
long GetModifiers(JNIEnv *env, jclass class,
		  unsigned int nFlags)
{
	int nModifiers = 0;
	int state;

	if ((1<<24) & nFlags) {
		nModifiers |= staticIntField(env, class,
					     "META_MASK");
	}	
	state = GetAsyncKeyState(VK_CONTROL);
	if (HIBYTE(state)) {
		nModifiers |= staticIntField(env, class,
					     "CTRL_MASK");
	}		
	state = GetAsyncKeyState(VK_RBUTTON);
	if (HIBYTE(state)) {
	    nModifiers |= staticIntField(env, class,
					 "META_MASK");
	}
	state = GetAsyncKeyState(VK_SHIFT);
	if (HIBYTE(state)) {
		nModifiers |= staticIntField(env, class,
					     "SHIFT_MASK");
	}
	state = GetAsyncKeyState(VK_MBUTTON);
	if (HIBYTE(state)) {
	    nModifiers |= staticIntField(env, class, "ALT_MASK");
	}
	return nModifiers;
}



int translateToAscii(JNIEnv *env, UINT *nChar, long modifiers)
{
    int state;
    static int caps_lock = 0;
    jclass class;

    class = 
      getClass(env, "java/awt/event/InputEvent",
	       "Unable to get java.awt.event.InputEvent class");

    *nChar = MapVirtualKey(*nChar, 2);	
    state = GetAsyncKeyState(VK_CAPITAL);

    if (LOBYTE(state)) {
	caps_lock = !caps_lock;
    }
    if (caps_lock != 0) {
	if (*nChar >= 'a' && *nChar <= 'z') {
	    *nChar = (*nChar - 'a') + 'A';
	}
    }
    if ((modifiers&staticIntField(env, class,  "SHIFT_MASK"))  == 0) {
	if (caps_lock == 0) {
	    if (*nChar >= 'A' && *nChar <= 'Z') {
		*nChar = (*nChar - 'A') + 'a';
	    }
	}
    } else {
	switch (*nChar) {
	  case '`':
	    *nChar = '~';
	    break;
	  case '1':
	    *nChar = '!';
	    break;
	  case '2':
	    *nChar = '@';
	    break;
	  case '3':
	    *nChar = '#';
	    break;
	  case '4':
	    *nChar = '$';
	    break;
	  case '5':
	    *nChar = '%';
	    break;
	  case '6':
	    *nChar = '^';
	    break;
	  case '7':
	    *nChar = '&';
	    break;
	  case '8':
	    *nChar = '*';
	    break;
	  case '9':
	    *nChar = '(';
	    break;	
	  case '0':
	    *nChar = ')';
	    break;
	  case '-':
	    *nChar = '_';
	    break;
	  case '=':
	    *nChar = '+';
	    break;
	  case '\\':
	    *nChar = '|';
	    break;
	  case '[':
	    *nChar = '{';
	    break;
	  case ']':
	    *nChar = '}';
	    break;
	  case ';':
	    *nChar = ':';
	    break;
	  case '\'':
	    *nChar = '"';
	    break;
	  case ',':
	    *nChar = '<';
	    break;
	  case '.':
	    *nChar = '>';
	    break;
	  case '/':
	    *nChar = '?';
	    break;
	  default:
	    break;
	}
    }
    if ((modifiers&staticIntField(env, class, "CTRL_MASK")) != 0) {
        switch (*nChar) {
        case '[':
        case ']':
        case '\\':
        case '_':
	    *nChar -= 64;
            break;
        default:
	  /*	   if (isalpha(*nChar)) {
	       *nChar = tolower(*nChar) - 'a' + 1;*/
	  if (*nChar >= 'A' && *nChar <= 'Z')
	    *nChar = (*nChar + 32) - 'a' + 1; 
	  if (*nChar >= 'a' && *nChar <= 'A')
	    *nChar = *nChar - 'a' + 1; 

	   }
       }
    return 1;
}

