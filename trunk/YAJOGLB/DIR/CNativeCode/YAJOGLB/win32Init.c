/*
 * init.c
 *
 * $Id: win32Init.c,v 1.4 1999/01/04 02:01:37 razeh Exp $
 *
 * This module handles the DLL attachment and detachment.
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

#include "cygnusFixes.h"
#include <windows.h> 
#include "win32EnvDictionary.h"

extern 
int WINAPI DllMain (HANDLE h, DWORD reason, void *ptr);


int WINAPI DllMain (HANDLE ignored1, 
		      DWORD reason,
		      void *ignore2)
{
  switch (reason) 
    {
    case DLL_PROCESS_ATTACH:
		envDictionaryProcessSetup();
	    break;
    case DLL_PROCESS_DETACH:
		envDictionaryProcessShutdown();
	    break;
    case DLL_THREAD_ATTACH:
		envDictionaryThreadSetup();
        break;
    case DLL_THREAD_DETACH:
		envDictionaryThreadShutdown();
        break;
  }
  return 1;
}

