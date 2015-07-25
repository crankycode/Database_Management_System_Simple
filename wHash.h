#ifndef _WHEAP_H_
#define _WHEAP_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "wHashUtil.h"

#define TRUE 1
#define FALSE 0
#define HASHSIZE 3        /* Index of argv** ,user typed binary filename */
#define FILENAME 2        /* Index of argv**, user typed search filename */
#define RECORDS_FILE 1    /* Index of argv** ,user typed records filename */
#define RECORD_LEN 60     /* Value uses for char array for reading in records */
#define OCCUPANCY 1.25    /* Occupany for hash func. currently set at 80% */
#define DELIM ",\n"       /* Use for string tokenizer */

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
   int recordCount;
} Page;

/* A page containing array of records */
typedef struct File {
   Page **page;
   int pageCount;
} File;

/* Header file */
typedef struct HashFileInfo{

   int totalRecords;
   int pageSize;
   int totalPage;

}HashFileInfo;

/* Insert record into page using hash function */
int insertRecord(FILE *inFile, File *heapFile,HashFileInfo hashFileInfo);
/* Count total no. of record */
int getTotalRecord(FILE *inFile);
/* Hash function for deciding where a records is to be stored */
int hashFunctiion(unsigned int primaryKey,int pageSize,int totalPage);
#endif
