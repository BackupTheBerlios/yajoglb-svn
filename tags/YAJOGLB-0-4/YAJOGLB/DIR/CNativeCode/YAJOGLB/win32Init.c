/*
  DLL setup methods.
 
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
 * win32Init.c
 *
 * $Id: win32Init.c,v 1.5 2001/07/06 23:40:05 razeh Exp $
 *
 * This module handles the DLL attachment and detachment.
 *
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

