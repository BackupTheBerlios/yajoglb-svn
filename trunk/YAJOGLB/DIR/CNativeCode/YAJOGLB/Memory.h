/*
 * Memory.h
 *
 * $Id: Memory.h,v 1.3 1999/01/26 23:58:11 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 */

#include <stdlib.h>

extern void *privateMalloc(size_t size);
extern void privateFree(void *ptr);
