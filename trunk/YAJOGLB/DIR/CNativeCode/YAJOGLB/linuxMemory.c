/*
 * memory.c
 *
 * This serves as a interface between the memory functions we use
 * (privateMalloc, privateFree), and what ever the system wide memory
 * functions are.
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com) 
 */



#include "SystemInclude.h"
#include "Memory.h"

void *privateMalloc(size_t size)
{
  return malloc(size);
}



void privateFree(void *pointer)
{
  free(pointer);
}
