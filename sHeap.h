#ifndef _WHEAP_H_
#define _WHEAP_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sHeapUtil.h"

#define DELIM ",\n"           /* Use for string tokenizer */
#define HEAPSIZE 3            /* Index of argv** ,user typed  heap size */
#define FILENAME 2            /* Index of argv** ,user typed binary filename */
#define KEY_LENGTH 15         /* Search key length */
#define REQUIRED_ARGUMENTS 4  /* Total of 4 arguments needed */
#define TRUE 1
#define FALSE 0

/* Use bytes of 2 instead of 4 */
#pragma pack(2)
typedef struct Record{

   unsigned int ID;
   unsigned int CLASS;
   unsigned short RACE;
   char NAME[14];
   char GUILD[30];

}Record;

/* A page containing array of records */
typedef struct Page {
   Record *pageRecords;
   int pageSize;
} Page;

/* A page containing array of records */
typedef struct File {
   Page **page;
   int pageCount;
} File;

void searchRecord(FILE *inFile, FILE* heapFile, int pageSize);

#endif
