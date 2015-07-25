
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wHeapUtil.h"
#include "wHeap.h"

/* Allocate a page of memory to store records */
void *mallocRecords (int size)
{
   Record *pageRecords;
   if ((pageRecords = (Record*) calloc(size ,sizeof(Record))) == NULL)
   {
      fprintf(stderr, "Error! Could not allocate %d bytes of memory.\n",
             size);
      return NULL;
   }
   return pageRecords;
}

/* Allocate more pointers for pages array depending on new_size */
void *reallocPages (void *old_mem, int new_size)
{
   Page **moreBuffer;

   if ((moreBuffer = (Page**) realloc(old_mem, sizeof(Page*)*new_size)) == NULL)
   {
      fprintf(stderr, "Error! Could not allocate %d bytes of memory.\n",
             new_size);
      return NULL;
   }
   return moreBuffer;
}

/* Allocate memory for page struct */
void *callocNewPage()
{
   Page *newPage = (Page*)calloc(sizeof(Page),1);
   return newPage;
}

/* Allocate memory for pages array */
void mallocPages(File* heapFile)
{
   /* Allocate 1 pointer for 2d pages array */
   heapFile->page = (Page**)malloc(sizeof(Page*));
   heapFile->pageCount =1;
}


