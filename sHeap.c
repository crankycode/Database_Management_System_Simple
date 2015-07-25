/* System-wide header files. */
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sHeapUtil.h"
#include "sHeap.h"

void searchRecord(FILE *inFile, FILE* heapFile, int pageSize)
{

   int record_status=FALSE;         /* True = match found */
   char raw_searchkey[KEY_LENGTH];  /* Search key in text form */
   unsigned int searchKey;          /* Search key converted to int */
   unsigned int userid;             /* User id from data_2011, for comparing */
   int i;                           /* Use for all the "loops" */
   clock_t start, end;              /* System clock */
   double elapsed;                  /* Computed running time */
   /* Starting time */
   
   /* Create a page to store records */
   Record *new_page_records = (Record*)calloc(sizeof(Record),pageSize);
   /* Read in 1 page per loop */
   while((fgets(raw_searchkey,KEY_LENGTH,inFile)!= NULL)) {

      searchKey = atoi(raw_searchkey);
      do {
         
         fread(new_page_records,sizeof(Record),pageSize,heapFile);

           while((i< pageSize)) {
               Record set_record =new_page_records[i];
               userid =(int)set_record.ID;
               /* Match found */
               if(searchKey == userid) {
                  printf("- Record found -\nName:%s\nRace:%d\n",
                         set_record.NAME,set_record.RACE);
                  printf("Class:%d\nId:%d\nGuild:%s\n\n",
                         set_record.CLASS,set_record.ID,set_record.GUILD);
                    record_status =TRUE;
               }
               /* End of page reach */
               if(userid == 0)
                  break;
               i++;
            }
         i =0;
         /* Finish searching this page, free it */
         memset(new_page_records,'\0',pageSize);
      } while(!feof(heapFile));
      /* No match found */
     if(record_status == FALSE) {
        printf("- Record not found -\nsearch key:%d\n\n",searchKey);
     }
      rewind(heapFile);
      record_status = FALSE;
   }
   /* Finish */
   free(new_page_records);
}

int main(int argc, char** argv)
{
   FILE *inFile;           /* Data_2011 */
   FILE *heapFile;         /* Binary out file */
   int pageSize;

   /* check for arguments */
   if(argc !=4) {
      printf("Invalid number of input argument \n");
      exit(EXIT_FAILURE);
   }

   /* Open search keyfile for reading */
   if((inFile=fopen(argv[1],"r"))==NULL) {
      printf("cannot open textfile \n");
      exit(EXIT_FAILURE);
   }
   /* init page size */
   pageSize = atoi(argv[HEAPSIZE]);

    /* Create open heapfile file */
   if((heapFile=fopen(argv[FILENAME],"rb"))==NULL) {
      printf("cannot read binary file\n");
      exit(EXIT_FAILURE);
   }

   /* Search records by comparing every records */
   searchRecord(inFile,heapFile,pageSize);
   fclose(heapFile);
   fclose(inFile);
   return 0;
}



