/* System-wide header files. */
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sHashUtil.h"
#include "sHash.h"


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

void searchRecord(FILE *inFile, FILE* binaryHashFile, HashFileInfo hashFileInfo)
{
   int i=0,hashedVal=0;                        /* Hashed func generated value */
   int pageSize = hashFileInfo.pageSize;     /* Pg size of each page read in */
   int totalPage = hashFileInfo.totalPage;   /* Total no. of page */
   int record_status=FALSE;                  /* True = match found */
   char raw_searchkey[KEY_LENGTH];           /* Search key from search_2011 */
   unsigned int searchKey;                   /* Converted search key */
   hrtime_t start;
   hrtime_t tmp;
   hrtime_t fin;
   start = gethrtime();	
   /* Read in 1 page per loop */
   Record *new_page_records = (Record*)calloc(sizeof(Record),pageSize);
   while((fgets(raw_searchkey,KEY_LENGTH,inFile)!= NULL)) {

      searchKey = atoi(raw_searchkey);
      hashedVal = hashFunctiion(searchKey,pageSize,totalPage);
      

      fseek(binaryHashFile,(sizeof(HashFileInfo)+(hashedVal*(pageSize))),SEEK_SET);
      fread(new_page_records,sizeof(Record),pageSize,binaryHashFile);

           while((i< pageSize)) {
                Record set_record = new_page_records[i];

                /* Match found */
                if(searchKey == set_record.ID) {
                    printf("- Record found -\nName:%s\nRace:%d\n",
                    set_record.NAME,set_record.RACE);
                    printf("Class:%d\nId:%d\nGuild:%s\n\n",
                    set_record.CLASS,set_record.ID,set_record.GUILD);
                    record_status =TRUE;
                }
               /* End of search reach */
               if(set_record.ID == 0)
                  break;
               i++;
            }
            i = 0;
            /* End of searching page, free page */
            memset(new_page_records,'\0',pageSize);
      /* No records found */
     if(record_status == FALSE) {
        printf("- Record not found -\nsearch key:%d\n\n",searchKey);

     }
      /* Reset file pointer to begining of file */
      rewind(binaryHashFile);
      /* Reset record status */
      record_status = FALSE;
   }
   free(new_page_records);
   fin = gethrtime();
   /* convert to millisecond */
   tmp = (fin - start)*0.000001;
   
   printf("time: %lld ms\n",tmp);
}

int main(int argc, char** argv)
{
   FILE *inFile;                        /* Data_2011 */
   FILE *binaryHashFile;                /* Binary Hashfile */
   HashFileInfo hashFileInfo;           /* TotalPg,pgSize & totalRecord */
 
   
   /* Check for arguments */
   if(argc != REQUIRED_ARGUMENTS) {
      printf("Invalid number of input argument \n");
      exit(EXIT_FAILURE);
   }
    /* Open binary file to do searching */
   if((binaryHashFile=fopen(argv[BINARYFILE],"rb"))==NULL) {
      printf("cannot read binary file\n");
      exit(EXIT_FAILURE);
   }
   /* Read the head file */
   fread(&hashFileInfo,sizeof(HashFileInfo),1,binaryHashFile);

   /* Init page size */
   hashFileInfo.pageSize = atoi(argv[HASHSIZE]);

   /* Compute total number of page needed for 80% Occupany*/
   hashFileInfo.totalPage = hashFileInfo.totalRecords *
                            OCCUPANCY / hashFileInfo.pageSize;

   /* Close file */
   fclose(binaryHashFile);

    /* Open binary file to do searching */
   if((binaryHashFile=fopen(argv[BINARYFILE],"rb"))==NULL) {
      printf("cannot read binary file\n");
      exit(EXIT_FAILURE);
   }

   /* Open search keyfile for reading */
   if((inFile=fopen(argv[SEARCHKEY_FILE],"r"))==NULL) {
      printf("cannot open textfile \n");
      exit(EXIT_FAILURE);
   }
   /* Search records using hash function */
   searchRecord(inFile,binaryHashFile,hashFileInfo);

   /* Finish searching close files */
   fclose(binaryHashFile);
   fclose(inFile);
 
   return 0;
}



