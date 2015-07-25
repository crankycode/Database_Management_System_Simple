/* System-wide header files. */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "wHeapUtil.h"
#include "wHeap.h"

#define TRUE 1
#define FALSE 0
#define HEAPSIZE 3
#define FILENAME 2

int insertRecord(FILE *inFile, File* heapFile, int pageSize)
{
   int i,endOfFile = FALSE; /* EndOfFile = last line of data */
   int pageCount =1;        /* No. of page in heapfile */
   char line[300];          /* Array for records read in */
   char *tok;               /* String tokening each fields */
   Page *currentPage;       /* Ptr of current page */
   Record *page_records;    /* Ptr of current array of records */
   hrtime_t start;
   hrtime_t tmp;
   hrtime_t fin;
   start = gethrtime();	
   
   while(!endOfFile) {
      /* Allocate New record array to store records */
      Record *new_page_records = (Record*)calloc(sizeof(Record),pageSize);
      page_records = new_page_records;

      for(i=0; i <pageSize; i++) {

         if((fgets(line,300,inFile))==NULL) {
            endOfFile = TRUE;
            break;
         }

         /* Insert data retrieve from file to Record struct */
         Record newRecord;
         tok = strtok(line,DELIM);
         strcpy(newRecord.NAME,tok);
         tok = strtok(NULL, DELIM);
         newRecord.RACE = atoi(tok);
         tok = strtok(NULL, DELIM);
         newRecord.CLASS = atoi(tok);
         tok = strtok(NULL, DELIM);
         newRecord.ID=atoi(tok);
         tok = strtok(NULL, DELIM);
         /* Check if field is empty */
         if( tok != NULL) {
            strcpy(newRecord.GUILD,tok);
         }
         else {
            strcpy(newRecord.GUILD,"");
         }
         page_records[i] =newRecord;
      }
      /* Create new page */
      currentPage = callocNewPage();
      /* Attach record array to page */
      currentPage->pageRecords =page_records;
      /* Start extending page array from page2 onwards  */
      if(pageCount > 1) {
      heapFile->page=reallocPages(heapFile->page,pageCount);
      heapFile->pageCount++;
      }
      /* Assign the newly created page to page array */
      heapFile->page[pageCount-1] = currentPage;
      /* Increase page count */
      pageCount++;
   }
   /* convert to millisecond */
   tmp = (fin - start)*0.000001;   
   printf("time: %lld ms\n",tmp);
   return 0;
}

int main(int argc, char** argv)
{
   File heapFile;         /* Heapfile */
   FILE *inFile;          /* Data_2011 */
   FILE *outFile;         /* Binary out file */
   unsigned int pageSize; /* User define pagesize */
   int i;

   /* check for arguments */
   if(argc !=4) {
      printf("Invalid number of input argument \n");
      exit(EXIT_FAILURE);
   }

   /* Open file for reading */
   if((inFile=fopen(argv[1],"r"))==NULL) {
      printf("cannot open textfile \n");
      exit(EXIT_FAILURE);
   }

   /* init page size */
   pageSize = atoi(argv[HEAPSIZE]);
   /* Init pages array for heapfile*/
   mallocPages(&heapFile);
   /* Read in data and load into heap memory */
   insertRecord(inFile,&heapFile,pageSize);
   fclose(inFile);

   /* Create binary file */
   if((outFile=fopen(argv[FILENAME],"wb"))==NULL) {
      printf("cannot write binary file\n");
      exit(EXIT_FAILURE);
   }

#if 0
   Record retrieve = (Record)heapFile.page[0]->pageRecords[0];
   printf("%s",retrieve.NAME);
#endif

   /* Write out 1 page per loop */
   for(i =0; i < heapFile.pageCount; i++) {
      fwrite(heapFile.page[i]->pageRecords,sizeof(Record),pageSize,outFile);
   }

   fclose(outFile);

   for(i =0; i < heapFile.pageCount; i++) {
      /* Free records array */
      free(heapFile.page[i]->pageRecords);
      /* Free page */
      free(heapFile.page[i]);
   }
   /* Free pages pointers */
   free(heapFile.page);
   exit(EXIT_SUCCESS);
}
