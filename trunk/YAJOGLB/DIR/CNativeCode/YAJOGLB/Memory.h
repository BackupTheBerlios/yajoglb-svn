/*
 * memory.h
 *
 * $Id: Memory.h,v 1.2 1998/11/01 21:44:18 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

#include <stdlib.h>

extern void *privateMalloc(size_t size);
extern void privateFree(void *ptr);
