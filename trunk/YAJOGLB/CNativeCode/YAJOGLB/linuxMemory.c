/*
  A simple interface for memory allocation (because Windows has to be
  different).
 
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
 * memory.c
 *
 * This serves as a interface between the memory functions we use
 * (privateMalloc, privateFree), and what ever the system wide memory
 * functions are.
 *
 */



#include "SystemIncludes.h"
#include "Memory.h"

void *privateMalloc(size_t size)
{
  return malloc(size);
}



void privateFree(void *pointer)
{
  free(pointer);
}

