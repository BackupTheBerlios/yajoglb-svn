/*
 * linux32EnvDictionary.c
 *
 * $Id: linuxEnvDictionary.c,v 1.1 1999/02/13 19:27:40 razeh Exp $
 *
 * This module handles getting and setting the current JNIEnv
 * pointer for this thread under Win32.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

#define _MIT_POSIX_THREADS 1
#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include "EnvDictionary.h"
#include "SystemError.h"
#include "ErrorHandling.h"


#include <pthread.h>

////////////////////////////////////////////////////////////////////////
// Setup and shutdown functions for the dictionary.
////////////////////////////////////////////////////////////////////////


/* This should be called when our DLL is loaded. */
int envDictionaryProcessSetup()
{
  return 0;
}



/* This should be called when our DLL goes away. */
int envDictionaryProcessShutdown()
{
  return 0;
}



/* Everytime a thread attaches to our DLL this should be called. */
int envDictionaryThreadSetup()
{
  return 0;
}



/* This should be called when our thread is going away. */
int envDictionaryThreadShutdown()
{
  return 0;
}



////////////////////////////////////////////////////////////////////////
// The actual dictionary functions.
////////////////////////////////////////////////////////////////////////


static JNIEnv *ourTemporaryEnv = NULL;

/* Set the environment pointer for the current thread. */
void setEnvironmentPointerForCurrentThread(JNIEnv *env)
{
  ourTemporaryEnv = env;
}


/* Clear out the environment pointer for the current thread. */
void unsetEnvironmentPointerForCurrentThread()
{
  
  ourTemporaryEnv = NULL;
}

/* Get the environment pointer for the current thread. */
JNIEnv *environmentPointerForCurrentThread()
{
  return ourTemporaryEnv;
}
