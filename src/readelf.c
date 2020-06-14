#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#include"elf_header.h"


T_STR_NAME *  readArchitecture(char * path, T_STR_NAME * strArch)
{
	Elf64_Ehdr Elf_header;
        char filepath[60];
        char archname[20];

	int fd;			// file descriptor to read the binary/executable/linkable file

        strArch->ArchName = malloc(strArch->noOfElement * sizeof(char*));

        strArch->invalidFiles = 0;

        for(int i=0;i < strArch->noOfElement ; i++)
        {
          // printf("%s\n",strArch->strName[i]);
          
          sprintf(filepath, "%s/%s",path,strArch->strName[i]);
          
          fd = open(filepath ,O_RDONLY);
	  if(fd == -1)
	  {
		perror("open ");
		return NULL;
	  }
	
	  //reding the binary file
	  if(read(fd,&Elf_header,sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr) )
	  {
		perror("read ");
		return NULL;
          }

          strArch->ArchName[i] = malloc(20 * sizeof(char));


          switch(Elf_header.e_machine)
	  {
		case EM_NONE :  strcpy(archname , "Invalid"); strArch->invalidFiles++; break;
		case EM_M32  :  strcpy(archname, "At&t WE 321"); break;
		case EM_SPARC:  strcpy(archname,"SPARC");break;
		case EM_386  :  strcpy(archname,"x86"); break;
		case EM_68K  :  strcpy(archname,"M68000");break;
		case EM_88K  :  strcpy(archname,"M88000");break;
		case EM_MIPS :  strcpy(archname,"MIPS");break;
                case 183:       strcpy(archname,"ARM_64"); break;
		case 40 :       strcpy(archname,"ARM_32");break;
		case 50 :       strcpy(archname,"IA-64");break;
		case 62 :       strcpy(archname,"x86-64");break;
		default :       strcpy(archname,"Invalid"); strArch->invalidFiles++; break;
	  }
          sprintf( strArch->ArchName[i], "%s", archname);
          
        }

	
	return strArch;
}
