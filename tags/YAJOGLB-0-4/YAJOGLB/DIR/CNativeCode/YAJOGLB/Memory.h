/*
 * Memory.h
 *
 * $Id: Memory.h,v 1.4 2002/07/21 16:54:25 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

#include <stdlib.h>

extern void *privateMalloc(size_t size);
extern void privateFree(void *ptr);
