/*
 * EventHandling.c
 *
 * $Id: EventHandling.c,v 1.3 2002/07/21 16:54:21 razeh Exp $
 *
 * This code handles invoking the handleEvent method for our widget
 * with a the appropriate event object.
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@yahoo.com) 
 */


#include "cygnusFixes.h"
#include "EventHandling.h"
#include "EventConversion.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"








/* This constructs a MouseEvent. 

   We return NULL if there are any problems in constructing the
   MouseEvent, and the new MouseEvent otherwise.  */
static jobject newMouseEvent(JNIEnv *env, jobject widget,
			     const char *fieldNameForID,
			     jlong when,
			     jint modifiers,
			     jint x,
			     jint y,
			     jint clickCount,
			     jboolean popupTrigger)
{
  jclass    mouseEventClass;
  jint      id;
  jmethodID eventConstructor;
  jobject   mouseEvent;

  mouseEventClass = getClass(env, "java/awt/event/MouseEvent",
			     "Unable to get java.awt.event.MouseEvent class");
  if (mouseEventClass == 0) {
    return NULL;
  }

  eventConstructor = getMethodID(env, mouseEventClass, 
				 "<init>",
				 "(Ljava/awt/Component;IJIIIIZ)V",
				 "Unable to get the init method for the "
				 "java.awt.event.MouseEvent class.");

  if (eventConstructor == 0) {
    return NULL;
  }


  /* Get the proper value for the id of our event. */
  if (lookupStaticIntField(env, mouseEventClass, fieldNameForID, &id) != 0) {
    return NULL;
  }

  /* Create our MouseEvent. */
  mouseEvent = (*env)->NewObject(env, mouseEventClass,
				 eventConstructor, 
				 widget, id, when, modifiers,
				 x, y, clickCount, popupTrigger);

  if (mouseEvent == 0) {
    handleError(env, "OpenGL/OpenGLNativeException",
		"Unable to get new MouseEvent object");
    return NULL;
  }

  return mouseEvent;
}



/* This creates and returns a simple event type given the class name
   and init signature to call, along with a character string of the
   field type.  If something goes wrong NULL is returned. */
static jobject newSimpleEvent(JNIEnv *env, jobject widget,
			      const char *className,
			      const char *initSignature,
			      const char *fieldNameForID)
{
  jclass    simpleEventClass;
  jmethodID eventConstructor;
  jobject   simpleEvent;
  jint      id;

  simpleEventClass = 
    getClass(env, className, "Unable to get a simple event class");
  if (simpleEventClass == 0) {
    return NULL;
  }
  
  /* Get the methodID for the proper constructor. */
  eventConstructor = getMethodID(env, simpleEventClass,
				 "<init>",
				 initSignature,
				 "Unable to get a simple event init method");
  if (eventConstructor == 0)
    return NULL;

  /* Lookup the ID field we will pass to our constructor. */
  if (lookupStaticIntField(env, simpleEventClass, fieldNameForID, &id) != 0)
    return NULL;

  /* Get the brand new event. */
  simpleEvent = (*env)->NewObject(env, simpleEventClass,
				  eventConstructor, widget, id);
  if (simpleEvent == 0) {
    handleError(env, "OpenGL/OpenGLNativeException",
		"Unable to get new simpleEvent");
    return NULL;
  }
  return simpleEvent;
}



/* This returns a new window event with its ID set to fieldNameForID.
   If something went wrong NULL is returned. */
static jobject newWindowEvent(JNIEnv *env, jobject widget,
			      const char *fieldNameForID)
{
  return newSimpleEvent(env, widget,
			"java/awt/event/WindowEvent",
			"(Ljava/awt/Window;I)V",
			fieldNameForID);
}



/* This returns a new component event with the given field name as its
   ID.  If something went wrong NULL is returned; otherwise the new
   object is returned. */
static jobject newComponentEvent(JNIEnv *env, jobject widget,
				 const char *fieldNameForID)
{
  return newSimpleEvent(env, widget,
			"java/awt/event/ComponentEvent",
			"(Ljava/awt/Component;I)V",
			fieldNameForID);
}



/* This returns a new java.awt.Rectangle object if everything goes
   right, with the supplied x, y, width, and height.  If anything goes
   wrong we will call handleError and return NULL. */
static jobject newRectangle(JNIEnv *env, 
			    jint x, jint y, jint width, jint height)
{
  jclass    rectangleClass;
  jmethodID rectangleConstructor;
  jobject   newRectangle;

  rectangleClass = getClass(env, "java/awt/Rectangle", 
			    "Unable to get the java.awt.Rectangle class");
  if (rectangleClass == 0) {
    return NULL;
  }

  rectangleConstructor = getMethodID(env, rectangleClass,
				     "<init>", "(IIII)V", 
				     "Unable to get the init method for the "
				     "java.awt.Rectangle class");
  if (rectangleConstructor == 0) {
    return NULL;
  }

  newRectangle = (*env)->NewObject(env, rectangleClass,
				   rectangleConstructor, x, y, width, height);
  if (newRectangle == 0) {
    handleError(env, "OpenGL/OpenGLNativeException",
		"Unable to create new Rectangle");
    return NULL;
  }
  return newRectangle;
}



/* This constructs a new paint event object with the given field ID.
   If something goes wrong NULL is returned; otherwise we return the
   new object. */
static jobject newPaintEvent(JNIEnv *env, jobject widget,
			     const char *fieldNameForID,
			     jint x, jint y, jint width, jint height)
{
  jobject   newRectangleForPaintEvent, newEvent;
  jclass    newPaintEventClass;
  jmethodID eventConstructor;
  jint      id;

  /* Get the paint event class. */
  newPaintEventClass = 
    getClass(env, "java/awt/event/PaintEvent",
	     "Unable to get java.awt.event.PaintEvent class");
  
  if (newPaintEventClass == 0) {
    return NULL;
  }

  /* Get our constructor. */
  eventConstructor = 
    getMethodID(env, newPaintEventClass,
		"<init>", "(Ljava/awt/Component;ILjava/awt/Rectangle;)V",
		"Unable to get the init method for "
		"java.awt.event.PaintEvent class");
  if (eventConstructor == 0) {
    return NULL;
  }

  /* Get the rectangle that needs to be repainted. */
  newRectangleForPaintEvent = newRectangle(env, x, y, width, height);
  if (newRectangle == 0) {
    return NULL;
  }

  /* Get the static field for out event. */
  if (lookupStaticIntField(env, newPaintEventClass, 
			   fieldNameForID, &id) != 0) {
    return NULL;
  }

  newEvent = (*env)->NewObject(env, newPaintEventClass, eventConstructor, 
			       widget, id, newRectangleForPaintEvent);
  return newEvent;
}



/* This returns a new key event.  If we run into any problems
   constructing the object we will return NULL; otherwise we return
   the new object. */
static jobject newKeyEvent(JNIEnv *env, jobject widget,
			   const char *fieldNameForID,
			   jlong when,
			   jint modifiers,
			   jint keyCode)
{
  jclass    newKeyEventClass; /* The class of object we will create. */
  jint      id;               /* The AWTEvent field ID. */
  jmethodID eventConstructor; /* The constructor method ID. */
  jobject   keyEvent;         /* The event we construct and return. */

  newKeyEventClass = getClass(env, "java/awt/event/KeyEvent",
			      "Unable to get java.awt.event.KeyEvent class");
  if (newKeyEventClass == 0) {
    return NULL;
  }

  /* Make sure that Java will understand our keycode. */
  keyCode = win32CharacterToJava(env, newKeyEventClass,
				 keyCode);

  eventConstructor = getMethodID(env, newKeyEventClass,
				 "<init>",
				 "(Ljava/awt/Component;IJII)V",
				 "Unable to get the init method for the "
				 "java.awt.event.KeyEvent class.");
  
  if (eventConstructor == 0) {
    return NULL;
  }
	
  if (lookupStaticIntField(env, newKeyEventClass, fieldNameForID, &id) != 0) {
    return NULL;
  }

  keyEvent = (*env)->NewObject(env, newKeyEventClass,
			       eventConstructor, 
			       widget, id, when, modifiers, keyCode);

  return keyEvent;
}



/*
  This hands off the given event.
 */

static int handOff(JNIEnv *env,
		   jobject widget,
		   jobject event)
{
  jclass    widgetClass;       /* The class of our widget jobject. */
  jmethodID handleEvent;       /* The event handler we call. */

  widgetClass = (*env)->GetObjectClass(env, widget);
  if (widgetClass == NULL)
    return JNI_FALSE;

  handleEvent =
    (*env)->GetMethodID(env, widgetClass, "handleEvent",
			"(Ljava/awt/AWTEvent;)Z");
  if (handleEvent == 0)
    return JNI_FALSE;


  (*env)->CallObjectMethod(env, widget, handleEvent, event);
  return JNI_TRUE;
}



/* This is called when the window was opened for the very first time.
   We create a window event for it and then call the widget's
   handleEvent method with a WindowEvent.  A return code of JNI_TRUE
   means things worked out; otherwise something went wrong. */
int handOffWindowActivated(JNIEnv *env, jobject widget)
{
  jobject windowActivatedEvent;

  windowActivatedEvent = newWindowEvent(env, widget, "WINDOW_ACTIVATED");
  if (windowActivatedEvent == NULL)
    return JNI_FALSE;
  
  return handOff(env, widget, windowActivatedEvent);
}



/* This is called when the window needs to be repainted for some
 reason.  A return code of JNI_TRUE means that things worked out;
 otherwise something went wrong. */
int handOffWindowExposed(JNIEnv *env, jobject widget)
{
  jobject paintEvent;

  paintEvent = newPaintEvent(env, widget, 
			     "PAINT", 0, 0, 0, 0);
  return handOff(env, widget, paintEvent);
}



/* This handles resizing the window.  We set the widget's height and
   width to the supplied values with setSize(), and then call
   handOffEvent. We return JNI_FALSE if things went badly and JNI_TRUE
   if all is well.*/
int handOffWindowResized(JNIEnv *env, jobject widget, 
			 int width, int height)
{
  jclass    widgetClass;       /* The class of our widget jobject. */
  jmethodID setSizeMethodID;   /* The setSize(int width, int height) method. */
  jobject   componentEvent;

  widgetClass = (*env)->GetObjectClass(env, widget);
  if (widgetClass == NULL)
    return JNI_FALSE;

  setSizeMethodID = (*env)->GetMethodID(env, widgetClass, "setSize",
					"(II)V");
  if (setSizeMethodID == 0)
    return JNI_FALSE;

  (*env)->CallObjectMethod(env, widget, setSizeMethodID, width, height);
  
  componentEvent = newComponentEvent(env, widget, "COMPONENT_RESIZED");
  
  return handOff(env, widget, componentEvent);
}


/* This is used by other methods that accept key events.  We set the
   event's keycode to the supplied value and then invoke the widget's
   handleEvent.  */
static int handOffKeyEvent(JNIEnv *env, jobject
			   widget, int keyCode, const char *keyEventType) 
{
  jobject keyEvent;
  long modifiers; jclass eventClass;

  eventClass = 
    getClass(env, "java/awt/event/InputEvent",
	     "Unable to get java.awt.event.InputEvent class");

  modifiers = GetModifiers(env, eventClass,  0);
  
  keyEvent = newKeyEvent(env, widget, 
			 keyEventType,
			 /* when */ 0,
			 modifiers,
			 keyCode);
  if (keyEvent == NULL) {
    return JNI_FALSE;
  }
  
  return handOff(env, widget, keyEvent);
}



/* This handles a key being down.  We return JNI_FALSE if things went
   badly and JNI_TRUE if all is well. */
int handOffKeyPressed(JNIEnv *env, jobject widget,
		   int keyCode)
{
  return handOffKeyEvent(env, widget, keyCode, "KEY_PRESSED");
}



/* This handles a key being down.  We return JNI_FALSE if things went
   badly and JNI_TRUE if all is well. */
int handOffKeyReleased(JNIEnv *env, jobject widget,
		       int keyCode)
{
  return handOffKeyEvent(env, widget, keyCode, "KEY_RELEASED");
}



/* This is called when we receive a mouse move event.  We return
   JNI_FALSE if something went wrong and JNI_TRUE if everything we
   well. */
int handOffMouseMove(JNIEnv *env, jobject widget,
		     int x, int y)
{
  jobject mouseEvent;        /* The event for this mouse down. */

  mouseEvent = newMouseEvent(env, widget, "MOUSE_MOVED", 0, 0, x, y, 0, 
			     JNI_FALSE);
  if (mouseEvent == NULL) {
    return JNI_FALSE;
  }

  return handOff(env, widget, mouseEvent);
}



/* This is called when we want to pass on a mouse down event.  We
   return JNI_FALSE if something went wrong and JNI_TRUE if everything
   worked out ok. */
int handOffMouseDown(JNIEnv *env, jobject widget, int x, int y)
{
  jobject mouseEvent;        /* The event for this mouse down. */

  mouseEvent = newMouseEvent(env, widget, "MOUSE_PRESSED", 0, 0, x, y, 0, 
			     JNI_FALSE);
  if (mouseEvent == NULL) {
    return JNI_FALSE;
  }

  return handOff(env, widget, mouseEvent);
}




/* This is called when we want to pass on a mouse down event.  We
   return JNI_FALSE if something went wrong and JNI_TRUE if everything
   worked out ok. */
int handOffMouseUp(JNIEnv *env, jobject widget,
		   int x, int y)
{
  jobject mouseEvent;        /* The event for this mouse down. */

  mouseEvent = newMouseEvent(env, widget, "MOUSE_RELEASED", 0, 0, x, y, 0, 
			     JNI_FALSE);
  if (mouseEvent == NULL) {
    return JNI_FALSE;
  }

  return handOff(env, widget, mouseEvent);
}
