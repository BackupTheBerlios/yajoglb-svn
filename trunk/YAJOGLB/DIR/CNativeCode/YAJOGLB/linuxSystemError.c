/*
 * SystemError.c
 * 
 * $Id: linuxSystemError.c,v 1.1 1999/02/13 19:27:40 razeh Exp $
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

#include "SystemIncludes.h"
#include <errno.h>
#include "Memory.h"

/* This returns an error message describing the latest operating system error. 
   The string returned should be released with privateFree from the
   memory.c and memory.h files. */
char *systemErrorMessage()
{
  char  *errorMessage = NULL;
  char  *returnMessage = NULL;

  errorMessage = strerror(errno);
  if (NULL != errorMessage) {
    returnMessage = (char*)privateMalloc(strlen(errorMessage) + 1);
    strcpy(returnMessage, errorMessage);
  }
  return errorMessage;
} 
