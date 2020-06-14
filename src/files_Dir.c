#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

#include"elf_header.h"

#define FILE_NAME_SIZE 20


T_STR_NAME *  show_dir_content(char * path)
{
  T_STR_NAME *strArch = NULL;

  DIR * d = opendir(path); 
  if(d==NULL) return NULL; 
  struct dirent * dir; 

  strArch = malloc(sizeof(T_STR_NAME));

  
  strArch->strName = malloc(sizeof(char*));
  strArch->noOfElement = 0 ;

  while ((dir = readdir(d)) != NULL) 
  {
      if(dir-> d_type != DT_DIR) //if it's a file 
      {
        strArch->strName[strArch->noOfElement] = malloc(40 * sizeof(char));
        strcpy(strArch->strName[strArch->noOfElement], dir->d_name);

        strArch->noOfElement++; 
        strArch->strName = realloc(strArch->strName, (strArch->noOfElement+1) *sizeof(char*));
        //printf("%s\n", dir->d_name); 
      }
   }

   closedir(d); // close

  return strArch;
}

int main(int argc, char **argv)
{
   T_STR_NAME *strArch = NULL;
   int invalidFiles;

   if(argc <= 1)
   {
	puts("execution format : ./a.out --./DirPath");
	return -1;
   }

  strArch = show_dir_content(argv[1]);

  strArch = readArchitecture(argv[1] , strArch);

  printf("Total number of libraries: %d\n",strArch->noOfElement - strArch->invalidFiles);

  printf("File \t\t\t\t ArchType\n");
  printf("==== \t\t\t\t =====\n");
  
  for(int i=0;i<strArch->noOfElement ; i++)
  {
    if( !strncmp(strArch->ArchName[i],"Invalid", 8))
      continue;
    printf("%s \t\t\t %s\n",strArch->strName[i], strArch->ArchName[i]);
  }

  free(strArch->strName);
  free(strArch->ArchName);
  free(strArch);

  return(0);
}
