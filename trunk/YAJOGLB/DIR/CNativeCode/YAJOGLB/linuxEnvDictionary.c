/*
 * linux32EnvDictionary.c
 *
 * $Id: linuxEnvDictionary.c,v 1.2 1999/05/03 00:06:48 razeh Exp $
 *
 * This module handles getting and setting the current JNIEnv
 * pointer for this thread under Win32.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */


#include "SystemIncludes.h"
#include "cygnusFixes.h"
#include "EnvDictionary.h"
#include "SystemError.h"
#include "ErrorHandling.h"

#include <pthread.h>

////////////////////////////////////////////////////////////////////////
// The actual dictionary functions.
////////////////////////////////////////////////////////////////////////

static pthread_key_t environmentThreadKey = 0;

/* Set the environment pointer for the current thread. */
void setEnvironmentPointerForCurrentThread(JNIEnv *env)
{
  if (0 == environmentThreadKey) {
    int errorNumber = pthread_key_create(&environmentThreadKey, NULL);
    if (0 != errorNumber) {
      logMessage(env, "Unable to create a new thread key");
      fatalUnreportableError(systemErrorMessage());
    }
  }

  if (0 != pthread_setspecific(environmentThreadKey, env)) {
    logMessage(env, "Unable to create a new thread key");
    fatalUnreportableError(systemErrorMessage());
  }
}


/* Clear out the environment pointer for the current thread. */
void unsetEnvironmentPointerForCurrentThread()
{
  if (0 != pthread_setspecific(environmentThreadKey, NULL)) {
    fprintf(stderr, "Unable to set the key at %s:%d\n", __FILE__, __LINE__);
    fatalUnreportableError(systemErrorMessage());
  }
}


/* Get the environment pointer for the current thread. */
JNIEnv *environmentPointerForCurrentThread()
{
  return pthread_getspecific(environmentThreadKey);
}



