#ifndef _WHEAPUTIL_H_
#define _WHEAPUTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sHash.h"

/* Allocate a page of memory to store records */
void *callocRecords (int size);
/* Allocate more pointers for pages array depending on new_size */
void *reallocPages (void *old_mem, int new_size);
/* Allocate new page */
void *callocNewPage();
/* Initializes hashfile */
void mallocPages(File* heapFile,HashFileInfo hashFileInfo);

#endif /* end of _WHEAPUTIL_H_s */



