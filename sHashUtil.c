
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sHashUtil.h"
#include "sHash.h"

/* Allocate a page of memory to store records */
void *callocRecords (int size)
{
   Record *pageRecords;
   if ((pageRecords = (Record*) calloc(size ,sizeof(Record))) == NULL) {
      fprintf(stderr, "Error! Could not allocate %d bytes of memory.\n",
             size);
      return NULL;
   }
   return pageRecords;
}

/* Allocate more pointers for pages array depending on new_size */
void *reallocPages (void *old_mem, int new_size)
{
   /* Array of arrays of pointers */
   Page **moreBuffer;

   if ((moreBuffer = (Page**) realloc(old_mem, sizeof(Page*)*new_size)) == NULL) {
      fprintf(stderr, "Error! Could not allocate %d bytes of memory.\n",
             new_size);
      return NULL;
   }
   return moreBuffer;
}

/* Allocate memory for page struct */
void *callocNewPage()
{
   /* Create new page */
   Page *newPage = (Page*)calloc(sizeof(Page),1);
   newPage->recordCount=0;
   return newPage;
}

/* Allocate memory for pages array */
void mallocPages(File* heapFile,HashFileInfo hashFileInfo)
{
    Page *newPage;
    Record *recordArray;
    int totalPage = hashFileInfo.totalPage;
    int pageSize = hashFileInfo.pageSize;
    int i;
    /* Allocate all pointers for 2d pages array */
   heapFile->page = (Page**)(malloc(sizeof(Page*)*totalPage));
   heapFile->pageCount =totalPage;
    /* Create page and add it to  */
    for (i = 0; i <= totalPage; i++) {
          newPage = callocNewPage();
          recordArray = callocRecords(pageSize);
          newPage->pageRecords = recordArray;
          heapFile->page[i] = newPage;  // Allocate arrays of data.
    }
}


