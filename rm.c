#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


void _rm(char *filename){
    if (remove(filename)){
		printf("rm: cannot remove '%s': No such file or directory\n" , filename);}
}

void _vrm(char *filename){
    if (remove(filename)){
		printf("rm: cannot remove '%s': No such file or directory\n" , filename);}
	else{
		printf("removed '%s'\n" , filename);}
 }


void _irm(char *filename){
    char inpu[200];
    printf("rm: remove regular file '%s'? " , filename);
	fgets(inpu, sizeof(inpu), stdin);
    inpu[strlen(inpu)-1]='\0';
    if ((!strcmp(inpu,"y") || !strcmp(inpu,"Y"))){
	     if (remove(filename)){
           printf("rm: cannot remove '%s': No such file or directory\n" , filename);
           }}
}

int main(int argc, char *argv[])
{
    char *filename=argv[3];
    int v = atoi(argv[1]);
    int i = atoi(argv[2]);
    if(v==1){
        _vrm(filename);
    }
    else if(i==1){
         _irm(filename);
    }
    else{
        _rm(filename);
    }
    return 0;
}