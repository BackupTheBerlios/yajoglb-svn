/*
 * win32SystemError.c
 * 
 * $Id: win32SystemError.c,v 1.2 1999/02/13 19:27:40 razeh Exp $
 * 
 * This implements our interface to our operating system's error 
 * reporting routines.  We return a character string that describes
 * the latest OS error. 
 *
 * Copyright 1998
 * 
 * Robert Allan Zeh (razeh@balr.com)
 *
 */

#include <windows.h>
#include "memory.h"

/* This returns an error message describing the latest operating system error. 
   The string returned should be released with privateFree from the
   memory.c and memory.h files. */
char *systemErrorMessage()
{
	LPVOID        lpMsgBuf;
	 char        *errorMessage;

	FormatMessage( 
	 FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
	 NULL,
	 GetLastError(),
	 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
	 (LPTSTR) &lpMsgBuf,
	 0,
	 NULL);

	errorMessage = privateMalloc(strlen(lpMsgBuf) + 1);
	strcpy(errorMessage, lpMsgBuf);

	// Free the buffer.
	LocalFree(lpMsgBuf);
	return errorMessage;
} 