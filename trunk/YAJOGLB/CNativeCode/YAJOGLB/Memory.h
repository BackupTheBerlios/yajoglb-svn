/*
 * Memory.h
 *
 * $Id$
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

#include <stdlib.h>

extern void *privateMalloc(size_t size);
extern void privateFree(void *ptr);
