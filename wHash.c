#include <stdlib.h>
#include <stdio.h>
#include "wHashUtil.h"
#include "wHash.h"

/* Hash function for deciding which page to go */
int hashFunctiion(unsigned int primaryKey,int pageSize,int totalPage)
{
   int hashedValue = (primaryKey % pageSize);
   /* Cap the value at totalPage value */
   if(hashedValue > totalPage) {
      return totalPage;
   }
   else {
      return hashedValue;
   }
}

/* Insert record to page using hash function */
int insertRecord(FILE *inFile,File* hashFile,HashFileInfo hashFileInfo)
{
   /* Total no. of page to store all the records */
   int totalPage = hashFileInfo.totalPage;
   /* User keyed in pageSize */
   int pageSize = hashFileInfo.pageSize;
   int hashedValue=0;       /* The result of hash function */
   int numberOfRecord;      /* Current no. of record in the page */
   char line[RECORD_LEN];   /* Array for records read in */
   char *tok;               /* String tokening each fields */
   Page *currentPage;       /* Ptr of current page */

   /* Start looping until end of line reach */
   while(TRUE) {

      /* Read in a line of record from data_2011 */
      if((fgets(line,RECORD_LEN,inFile))==NULL) {
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

      /* Generate hash value using ID*/
      hashedValue = hashFunctiion(newRecord.ID,pageSize,totalPage);
      currentPage = hashFile->page[hashedValue];
      numberOfRecord = currentPage->recordCount;
      /* Add record to page, if page is not full */
      if(!(currentPage->recordCount == pageSize)) {
         numberOfRecord = (currentPage->recordCount++);
         currentPage->pageRecords[numberOfRecord] = newRecord;
      }
   }
   return 0;
}
/* Count the no. of records */
int getTotalRecord(FILE *inFile)
{
   int i;
   char temp[RECORD_LEN];
   for(i=0;fgets(temp,RECORD_LEN,inFile)!= NULL;i++)
               ;

   return i;
}

int main(int argc,char** argv)
{
   File hashFile;                       /* Heapfile */
   FILE *inFile;                        /* Data_2011 */
   FILE *outFile;                       /* Binary out file */
   HashFileInfo hashFileInfo;           /* TotalPg,pgSize & totalRecord */
   int i;                               /* Variable is use for "loops" */

   /* Check for arguments */
   if(argc !=4) {
      printf("Invalid number of input argument \n");
      exit(EXIT_FAILURE);
   }
   /* Open file for counting no. of records */
   if((inFile=fopen(argv[1],"r"))==NULL) {
      printf("cannot open textfile \n");
      exit(EXIT_FAILURE);
   }
   /* Init page size */
   hashFileInfo.pageSize = atoi(argv[HASHSIZE]);
   /* Scan data_2011 for number of records */
   hashFileInfo.totalRecords = getTotalRecord(inFile);
   /* Compute total number of page needed for 80% Occupany*/
   hashFileInfo.totalPage = hashFileInfo.totalRecords *
                            OCCUPANCY / hashFileInfo.pageSize;
   /* Close file */
   fclose(inFile);

   /* Init hashFile pages arrays pointers */
   mallocPages(&hashFile,hashFileInfo);

   /* Open file for generating binary file */
   if((inFile=fopen(argv[RECORDS_FILE],"r"))==NULL) {
      printf("cannot open textfile \n");
      exit(EXIT_FAILURE);
   }

   /* Insert records */
   insertRecord(inFile,&hashFile, hashFileInfo);

     /* Create binary file */
   if((outFile=fopen(argv[FILENAME],"wb"))==NULL) {
      printf("cannot write binary file\n");
      exit(EXIT_FAILURE);
   }

   /* Write file header */
   fwrite(&hashFileInfo,sizeof(HashFileInfo),1,outFile);
   /* Write out to binary file , 1 page per loop */
   for(i =0; i < hashFile.pageCount; i++) {
      fwrite(hashFile.page[i]->pageRecords,sizeof(Record),
             hashFileInfo.pageSize,outFile);
   }
   /* Close binary file */
   fclose(outFile);
   
/* check for data competion */
#if 0
   int test_recordCounter=0;
   int test_counter=0;
   for(int i=0; i<hashFileInfo.totalPage;i++) {

         Page *test_page;
         test_page=hashFile.page[i];
         for(int k=0; k<test_page->recordCount;k++) {
               test_counter++;
               Record test_record = (Record)test_page->pageRecords[k];
               printf("Name:%s ID:%d\n no. of record:%d\n",test_record.NAME,test_record.ID,test_counter);

         }

   }
#endif

   /* Release memory */
   for(i =0; i <= hashFileInfo.totalPage; i++) {
      /* Free records array */
      free(hashFile.page[i]->pageRecords);
      /* Free page */
      free(hashFile.page[i]);
   }
   /* Free pages pointers */
   free(hashFile.page);

   exit(EXIT_SUCCESS);
}



