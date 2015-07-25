#ifndef _WHEAP_H_
#define _WHEAP_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sHashUtil.h"

#define TRUE 1
#define FALSE 0
#define HASHSIZE 3        /* Index of argv** ,user typed binary filename */
#define BINARYFILE 2      /* Index of argv**, Binary Hashed filename */
#define SEARCHKEY_FILE 1  /* Index of argv**, Search key file index */
#define RECORDS_FILE      /* Index of argv** ,user typed records filename */
#define RECORD_LEN 60     /* Value uses for char array for reading in records */
#define OCCUPANCY 1.25    /* Occupany for hash func. currently set at 80% */
#define DELIM ",\n"           /* Use for string tokenizer */
#define KEY_LENGTH 15         /* Search key length */
#define NAME_LEN 14           /* Length of name */
#define GUILD_LEN 30          /* Length of guild */
#define REQUIRED_ARGUMENTS 4  /* Total of 4 arguments needed */

/* Use bytes of 2 instead of 4 */
#pragma pack(2)
typedef struct Record{

   unsigned int ID;
   unsigned int CLASS;
   unsigned short RACE;
   char NAME[NAME_LEN];
   char GUILD[GUILD_LEN];

}Record;
/* A page containing array of records */
typedef struct Page {
   Record *pageRecords;
   int recordCount;
} Page;
/* A file containing array of pages */
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
void searchRecord(FILE *inFile, FILE* binaryHashFile, HashFileInfo hashFileInfo);
/* Hash function for deciding where a records is to be stored */
int hashFunctiion(unsigned int primaryKey,int pageSize,int totalPage);
#endif
