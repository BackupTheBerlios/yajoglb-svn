/*
  Dictionary mapping for the JNIEnv and threads.
 
  Copyright 2001, Robert Allan Zeh (razeh@yahoo.com)
  7346 Lake Street #3W
  River Forest, IL 60305
 
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA

*/

/*
 * linux32EnvDictionary.c
 *
 * $Id: linuxEnvDictionary.c,v 1.3 2001/07/06 23:40:05 razeh Exp $
 *
 * This module handles getting and setting the current JNIEnv
 * pointer for this thread under Linux.
 *
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



