#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/wait.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

void _lsparse(int isa,int isl,const char *filename)
{
	struct dirent *dp;
	DIR *dh = opendir(filename);
	if (!dh)
	{
        printf("ls: Error: unable to locate or read directory\n");
		return;
	}
	while ((dp = readdir(dh)) != NULL)
	{
		if (!isa && dp->d_name[0] == '.'){
			continue;}
		printf("%s", dp->d_name);
		if(isl==1){
			printf(", ");}
		else{
			printf("   ");
		}
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
    int a = atoi(argv[2]);
    int l = atoi(argv[3]);
    _lsparse(a,l,argv[1]);
    return 0;
}