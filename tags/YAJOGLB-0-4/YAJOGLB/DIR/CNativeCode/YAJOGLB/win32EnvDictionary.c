/*
  The JNIEnv <-> thread mapping for Win32.
 
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
 * win32EnvDictionary.c
 *
 * $Id: win32EnvDictionary.c,v 1.4 2002/11/23 16:03:40 razeh Exp $
 *
 * This module handles getting and setting the current JNIEnv
 * pointer for this thread under Win32.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

#include "cygnusFixes.h"
#include <windows.h>
#include "EnvDictionary.h"
#include "SystemError.h"
#include "ErrorHandling.h"
#include "win32EnvDictionary.h"

static DWORD threadLocalStorageIndex;



////////////////////////////////////////////////////////////////////////
// Setup and shutdown functions for the dictionary.
////////////////////////////////////////////////////////////////////////



/* This should be called when our DLL is loaded. */
int envDictionaryProcessSetup()
{
	if ((threadLocalStorageIndex = TlsAlloc()) == 0xFFFFFFFF) {
		fatalUnreportableError(systemErrorMessage());
		return -1;
	}
	return 0;
}



/* This should be called when our DLL goes away. */
int envDictionaryProcessShutdown()
{
	if (0 == TlsFree(threadLocalStorageIndex)) {
		fatalUnreportableError(systemErrorMessage());
		return -1;
	}
	return 0;
}



/* Everytime a thread attaches to our DLL this should be called. */
int envDictionaryThreadSetup()
{
	LPVOID environmentPointerHolder = LocalAlloc(LPTR, sizeof(JNIEnv*));

	if (NULL != environmentPointerHolder) {
		if (0 == TlsSetValue(threadLocalStorageIndex, environmentPointerHolder)) {
			fatalUnreportableError(systemErrorMessage());
			return -1;
		}
	} else {
		fatalUnreportableError("Ran out of memory while allocating a JNI environment pointer information for a thread.");
		return -2;
	}
	return 0;
}



/* This should be called when our thread is going away. */
int envDictionaryThreadShutdown()
{
	LPVOID environmentPointerHolder = TlsGetValue(threadLocalStorageIndex);

	if (NULL != environmentPointerHolder) {
		LocalFree((HLOCAL) environmentPointerHolder);
	}
	/* We used to generate a warning here, but JDK 1.4.1 introduced 
	   an interesting scenario when a Java application exits:
envDictionaryThreadSetup(1788)
envDictionaryThreadSetup(1932)
envDictionaryThreadSetup(1732)
envDictionaryThreadSetup(984)
envDictionaryThreadSetup(1980)
envDictionaryThreadSetup(1740)
envDictionaryThreadShutdown(1740)
envDictionaryThreadShutdown(1932)
envDictionaryThreadShutdown(1980)
envDictionaryThreadShutdown(1252)
Unable to get a location to hold a JNI environment pointer while detaching a thr
ead.
     
	   So now just ignore it, since threads are somehow being
	   detached before being attached.
	 */
	return 0;
}



////////////////////////////////////////////////////////////////////////
// The actual dictionary functions.
////////////////////////////////////////////////////////////////////////



/* Set the environment pointer for the current thread. */
void setEnvironmentPointerForCurrentThread(JNIEnv *env)
{
	LPVOID environmentPointerHolder = TlsGetValue(threadLocalStorageIndex);

	if (NULL != environmentPointerHolder) {
		*(JNIEnv**)environmentPointerHolder = env;		
	} else {
		int error = 1;
		// The setup function will not be called for every thread in our environment.
		// It's possible that the Java code may have created threads before loading in
		// our DLL.  If that's the case, we try to create things here first.
		if (0 == envDictionaryThreadSetup()) {
			// It worked.
			environmentPointerHolder = TlsGetValue(threadLocalStorageIndex);
			if (NULL != environmentPointerHolder) {
				*(JNIEnv**)environmentPointerHolder = env;
				error = 0;
			} 
		}

		if (error) {
			printf("setEnvironmentPointerForCurrentThread failed: %p\n", GetCurrentThreadId());
			fatalUnreportableError("Unable to get an location to hold a JNI environment pointer while setting the environment pointer.");
		}
	}
}


/* Clear out the environment pointer for the current thread. */
void unsetEnvironmentPointerForCurrentThread()
{
	LPVOID environmentPointerHolder = TlsGetValue(threadLocalStorageIndex);

	if (NULL != environmentPointerHolder) {
		*(JNIEnv**)environmentPointerHolder = NULL;		
	} else {
		fatalUnreportableError("Unable to get an location to hold a JNI environment pointer while unsetting the environment pointer.");
	}
}



/* Get the environment pointer for the current thread. */
JNIEnv *environmentPointerForCurrentThread()
{
	LPVOID  environmentPointerHolder = TlsGetValue(threadLocalStorageIndex);
	JNIEnv* env = NULL;

	if (NULL != environmentPointerHolder) {
		env = *(JNIEnv**)environmentPointerHolder;		
	} else {
		fatalUnreportableError("Unable to get an location to hold a JNI environment pointer while getting the environment pointer.");
		return NULL;
	}

	return env;
}
