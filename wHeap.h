#ifndef _WHEAP_H_
#define _WHEAP_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "wHeapUtil.h"

     
#define DELIM ",\n"     /* Use for tokening data_2011 records */
#define RECORD_LEN 60   /* Value uses for char array for reading in records */
#define HEAPSIZE 3      /* Index of argv** ,user typed binary filename */ 
#define FILENAME 2      /* Index of argv** ,user typed record size */ 
#define RECORDS_FILE 1  /* Index of argv** ,user typed records filename */ 
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

/* Insert records packly into all pages */
int insertRecord(FILE *inFile, File* heapFile, int pageSize);

#endif
