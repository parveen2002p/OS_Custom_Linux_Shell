#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void __cat(char *filename){
    char  ch;
    FILE *fp;
    fp=fopen(filename, "r");
    if(fp == NULL) {
       printf("cat: %s: No such file or directory\n", filename);
       return;
    }
    while((ch=fgetc(fp)) != EOF){
         putchar(ch);
    }
    fclose(fp);
 }

 int _ncat(char *filename,int j){
   FILE * fp;
    size_t curlen = 0;
    ssize_t ret;
    char * current = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("cat: %s: No such file or directory\n",filename);
        return j;}

    while ((ret = getline(&current, &curlen, fp)) != -1) {
        printf("%d ", j);
        printf("%s", current);
        j++;
    }
    fclose(fp);
    if (current){
        free(current);}
    return j;
 }

void _dcat(char *filename){
   FILE * fp;
    size_t curlen = 0;
    ssize_t ret;
    char * current = NULL;

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("cat: %s: No such file or directory\n",filename);
        return;}

    while ((ret = getline(&current, &curlen, fp)) != -1) {
        current[strcspn(current, "\n")] = 0;
        printf("%s", current);
        printf("$\n");
    }
    fclose(fp);
    if (current){
        free(current);}
 }



int main(int argc, char *argv[])
{
    char *filename=argv[3];
    int n = atoi(argv[1]);
    int d = atoi(argv[2]);
    if(n==1){
        int j = atoi(argv[4]);
        //printf("\nj val %d\n",j);
        _ncat(filename,j);
    }
    else if(d==1){
         _dcat(filename);
    }
    else{
        __cat(filename);
    }
    return 0;
}