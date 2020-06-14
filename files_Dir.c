#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define FILE_NAME_SIZE 20

typedef struct 
{
  uint8_t noOfElement;
  char **strName;
}T_STR_NAME;

T_STR_NAME *  show_dir_content(char * path)
{
  T_STR_NAME *strArch = NULL;

  DIR * d = opendir(path); 
  if(d==NULL) return NULL; 
  struct dirent * dir; 

  strArch = malloc(sizeof(T_STR_NAME));

  
  strArch->strName = malloc(20 * sizeof(char*));
  strArch->noOfElement = 0 ;

  while ((dir = readdir(d)) != NULL) 
  {
      if(dir-> d_type != DT_DIR) //if it's a file 
      {
        strArch->strName[strArch->noOfElement] = malloc(40 * sizeof(char));
        strcpy(strArch->strName[strArch->noOfElement], dir->d_name);

        strArch->noOfElement++; 
        printf("%s\n", dir->d_name); 
      }
   }

   closedir(d); // close

  return strArch;
}

int main(int argc, char **argv)
{
   T_STR_NAME *strArch = NULL;

   if(argc <= 1)
   {
	puts("execution format : ./a.out --./DirPath");
	return -1;
   }

  strArch = show_dir_content(argv[1]);
  printf("Number of Element %d",strArch->noOfElement);
  
  for(int i=0;i<strArch->noOfElement ; i++)
  {
    printf("%s\n",strArch->strName[i]);
  }

  free(strArch->strName);
  free(strArch);

  return(0);
}
