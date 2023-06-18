#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>


void _dateU(){
    time_t t = time(NULL);
    char s[101];
    char s2[101];
    struct tm* tmu;
    time(&t);
    tmu = gmtime(&t);
     size_t ret = strftime(s, sizeof(s), "%c", tmu);
     // may use ret to find error if or check before 
    strncat(s2, s, 19);
    printf("%s UTC ", s2);
    printf("%d \n",tmu->tm_year+1900);
 }

 void _dateI(){
    time_t t = time(NULL);
    char s[101];
    char s2[101];
    struct tm *tmi = localtime(&t);
    size_t ret = strftime(s, sizeof(s), "%c", tmi);
     // may use ret to find error if or check before
    strncat(s2, s, 19);
    printf("%s IST ", s2);
    printf("%d \n",tmi->tm_year+1900);
 }

 void _dateR(char *path) {
    struct stat tmr;
    int error =stat(path, &tmr);
     // may use ret to find error if or check before 
    if(error==-1){
        printf("date: Error: No such file or directory\n");
        return;
    }
    printf("%s", ctime(&tmr.st_mtime));
}

int main(int argc, char *argv[])
{
    int u = atoi(argv[1]);
    int r = atoi(argv[2]);
    if(u==1){
        _dateU();
    }
    else if(r==1){
        char *filename=argv[3];
        _dateR(filename);
    }
    else{
        _dateI();
    }
    return 0;
}
