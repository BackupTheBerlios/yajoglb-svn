/*
  Error reporting for win32.
 
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
 * win32SystemError.c
 * 
 * $Id: win32SystemError.c,v 1.4 2001/08/11 02:16:02 razeh Exp $
 * 
 * This implements our interface to our operating system's error 
 * reporting routines.  We return a character string that describes
 * the latest OS error. 
 *
 */

#include <windows.h>
#include <stdio.h>
#include "memory.h"

/* This returns an error message describing the latest operating system error. 
   The string returned should be released with privateFree from the
   memory.c and memory.h files. */
char *systemErrorMessage()
{
	LPVOID       lpMsgBuf = 0;
	char        *errorMessage;

	FormatMessage( 
	 FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
	 NULL,
	 GetLastError(),
	 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
	 (LPTSTR) &lpMsgBuf,
	 0,
	 NULL);

	if (lpMsgBuf == 0) {
		const char *message = 
			"Unable to obtain a native error message.  Last error = %d.";
		errorMessage = privateMalloc(strlen(message) + 10);  // Enough room for the %d.
		sprintf(errorMessage, message, GetLastError());
		return errorMessage;
	}
	errorMessage = privateMalloc(strlen(lpMsgBuf) + 1);
	strcpy(errorMessage, lpMsgBuf);

	// Free the buffer.
	LocalFree(lpMsgBuf);
	return errorMessage;
}

