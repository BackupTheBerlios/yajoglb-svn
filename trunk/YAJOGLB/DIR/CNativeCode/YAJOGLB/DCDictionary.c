/* 
 * DCDictionary.c
 *
 * This implements a dictionary of device contexts, windows, OpenGL
 * contexts, java environments, and java objects for our library.
 * Because of the way windows handles events, we sometimes have to
 * find the proper java environment and object to handle an event by
 * associating that object with a NT window. 
 *
 * This module handles the task with a linked list of dictionary entries.
 *
 * Because it's possible that we will be running as a multi-threaded
 * library, we guard access to the dictionary with a critical section.
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com) 
 */



#include <windows.h>
#include <GL/gl.h>

#include "DCDictionary.h"
#include "memory.h"

/* This is used to prevent multiple threads from modifying the
   dictionary at the same time. */
CRITICAL_SECTION DCCriticalSection;

/* The structure that we use for our linked list of dictionary entries. */
typedef struct _dictionaryEntry {
  HDC     hDC;
  HGLRC   hGLRC;
  JNIEnv  *environment;
  jobject widget;
  HWND    hWnd;
  struct _dictionaryEntry *next;
} dictionaryEntry;

/* This is the start of our linked list of dictionary entries. */
static dictionaryEntry *dictionaryBase = NULL;

/* This performs what ever setup getDCLock() and releaseDCLock() need. */
void setupDCLocks()
{
    InitializeCriticalSection(&DCCriticalSection);
}

/* This handles both setting up the critical section we will use to
   guard access to our dictionary and getting a lock for it. */
static void getDCLock()
{
  EnterCriticalSection(&DCCriticalSection);
} 

/* This handles releasing our DC lock.  It's a simple call to
   LeaveCriticalSection. */
static void releaseDCLock()
{
  LeaveCriticalSection(&DCCriticalSection);
}

static dictionaryEntry *addDictionaryEntry()
{
  dictionaryEntry *newEntry  =
    (dictionaryEntry*) privateMalloc(sizeof(dictionaryEntry));

  newEntry->hDC         = NULL;
  newEntry->hGLRC       = NULL;
  newEntry->environment = NULL;
  newEntry->widget      = NULL;
  newEntry->next        = NULL;
  newEntry->hWnd        = NULL;
  newEntry->next        = NULL;

  if (dictionaryBase == NULL)
    dictionaryBase = newEntry;
  else {
    dictionaryEntry *lastEntry = dictionaryBase;
    while(lastEntry->next != NULL)
      lastEntry = lastEntry->next;
    lastEntry->next = newEntry;
  }
  return newEntry;
}



/* Retrieve the dictionary entry for widget, returning NULL if none is
   found. */
static dictionaryEntry *dictionaryEntryForWidget(JNIEnv *env,
						 jobject widget) 
{
  dictionaryEntry *dictionaryPointer = dictionaryBase;
  dictionaryEntry *result = NULL;

  while((dictionaryPointer != NULL) && (result == NULL)) {
    if ((*env)->IsSameObject(env, dictionaryPointer->widget, widget) 
	== JNI_TRUE)
	result = dictionaryPointer;
    dictionaryPointer = dictionaryPointer->next;
  }
  return result;
}



/* This returns the dictionary entry for a given window, and NULL if
   none is found. */
static dictionaryEntry *dictionaryEntryForWindow(HWND hWnd) 
{
  dictionaryEntry *dictionaryPointer = dictionaryBase;
  dictionaryEntry *result = NULL;

  while((dictionaryPointer != NULL) && (result == NULL)) {
    if (dictionaryPointer->hWnd == hWnd)
      result = dictionaryPointer;
    dictionaryPointer = dictionaryPointer->next;
  }
  return result;
}



/* This returns a handle for the device context for the given widget. */
HDC getDCForWidget(JNIEnv *env, jobject widget) 
{
  HDC result = NULL;

  getDCLock();
  {
    dictionaryEntry *entry  = dictionaryEntryForWidget(env, widget);

    if (entry != NULL)
      result = entry->hDC;
  }
  releaseDCLock();
  return result;
}



/* This returns the HGLRC for the given widget. */
HGLRC getGLRCForWidget(JNIEnv *env, jobject widget)
{
  HGLRC result = NULL;

  getDCLock();
  {
    dictionaryEntry *entry  = dictionaryEntryForWidget(env, widget);

    if (entry != NULL)
      result = entry->hGLRC;
  }
  releaseDCLock();
  return result;
}



/* This sets the GLRC for the given widget to hGLRC.  If there isn't
   one already around, it creates a new dictionary entry for env,
   widget, and hGLRC. */
void setGLRCForWidget(JNIEnv *env, jobject widget, HGLRC hGLRC)
{
  getDCLock();
  {
    dictionaryEntry *entry = dictionaryEntryForWidget(env, widget);
    if (entry == NULL) {
      dictionaryEntry *newEntry = addDictionaryEntry();
      newEntry->hGLRC           = hGLRC;
      newEntry->widget          = widget;
      newEntry->environment     = env;
    } else {
      entry->hGLRC = hGLRC;
    }
  }
  releaseDCLock();
}



/* This sets the DC for the given widget and environment to hDC.  If
   there isn't an entry already present a new one is created. */
void setDCForWidget(JNIEnv *env, jobject widget, HDC hDC)
{
  getDCLock();
  {
    dictionaryEntry *entry = dictionaryEntryForWidget(env, widget);
    if (entry == NULL) {
      dictionaryEntry *newEntry = addDictionaryEntry();
      newEntry->environment = env;
      newEntry->widget      = widget;
      newEntry->hDC         = hDC;
    } else {
      entry->hDC = hDC;
    }
  }
  releaseDCLock();
}



/* This returns the widget for the given window. */
jobject widgetForWindow(HWND hWnd)
{
  jobject result = NULL;

  getDCLock();
  {
    dictionaryEntry *entry  = dictionaryEntryForWindow(hWnd);
    
    if (entry != NULL) {
      result = entry->widget;
    }
  }
  releaseDCLock();
  return result;
}



/* This returns the environment that created the given window. */
JNIEnv *environmentForWindow(HWND hWnd)
{
  JNIEnv  *result = NULL;

  getDCLock();
  {
    dictionaryEntry *entry  = dictionaryEntryForWindow(hWnd);
  
    if (entry != NULL)
      result = entry->environment;
  }
  releaseDCLock();
  return result;
}



/* For a given widget object we return the window. */
HWND windowForWidget(JNIEnv *env, jobject widget)
{
  HWND result = NULL;

  getDCLock();
  {
    dictionaryEntry *entry = dictionaryEntryForWidget(env, widget);
    if (entry != NULL) {
      result = entry->hWnd;
    } 
  }
  releaseDCLock();
  return result;
}



/* This sets the dictionary entry for hWnd to have an environment and
   widget entry of env and widget.  If there is no dictionary entry
   for hWnd one is created. */
void setWidgetForWindow(HWND hWnd, JNIEnv *env, jobject widget)
{
  getDCLock();
  {
    dictionaryEntry *entry = dictionaryEntryForWindow(hWnd);
    if (entry == NULL) {
      dictionaryEntry *newEntry = addDictionaryEntry();
      newEntry->hWnd        = hWnd;
      newEntry->widget      = widget;
      newEntry->environment = env;
    } else
      entry->widget = widget;
  }
  releaseDCLock();
}



/* This sets the dictionary entry that contains hWnd to have a widget
   and environment entry of environment and widget.  If there is no
   dictionary entry for hWnd one is created. */
void setEnvironmentForWindow(HWND hWnd, JNIEnv *environment, jobject widget)
{
  getDCLock();
  {
    dictionaryEntry *entry = dictionaryEntryForWindow(hWnd);
    if (entry == NULL) {
      dictionaryEntry *newEntry = addDictionaryEntry();
      newEntry->hWnd        = hWnd;
      newEntry->widget      = widget;
      newEntry->environment = environment;
    } else
      entry->environment = environment;
  }
  releaseDCLock();
}

