#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

void _mkdir(char *filename){
   if (mkdir(filename, 0777)){
		printf("mkdir: cannot create directory ‘%s’\n" , filename);}
}

void _vmkdir(char *filename){
   if (mkdir(filename, 0777)){
		printf("mkdir: cannot create directory ‘%s’\n" , filename);}
	else{
		printf("mkdir: created directory '%s'\n" , filename);}
}

void _pmkdir(char *filename){
    char tp[300]="";
  char *token;
  token = strtok(filename, "/");
  strcat(tp,token);
  strcat(tp,"/");
  while (token != NULL) {
//   printf("%s\n", token);
//   printf("%s\n", tp);
  mkdir(tp, 0777);
  token = strtok(NULL, " /");
  strcat(tp,token);
  strcat(tp,"/");
  }
}



int main(int argc, char *argv[])
{
    char *filename=argv[3];
    int p = atoi(argv[1]);
    int v = atoi(argv[2]);
    if(p==1){
        _pmkdir(filename);
    }
    else if(v==1){
         _vmkdir(filename);
    }
    else{
        _mkdir(filename);
    }
    return 0;
}
