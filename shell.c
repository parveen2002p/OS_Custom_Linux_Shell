#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
char pathh[100];
#include "dateC.c"
#include "lsC.c"
#include "catH.c"
#include "rmC.c"
#include "mkdirC.c"
#include<sys/wait.h>
#include<ctype.h>

int max=1024;
char prompt[]="lnsh$> ";

// struct arg_struct{
//     char **cmdline;
//     int target;
//     int argc;
// };

int cblank(const char *cmd) {
    while (*cmd) {
        if (!isspace(*cmd++)) {
            return 0;
        }
    }
    return 1;
}


int generator(char *cmd,char **cmdline){
    if (cblank(cmd)){
        return -1;
    }
    int count=0;
    char delim[]=" \t\r\n";
    char *token=strtok(cmd,delim);
    cmdline[count]=token;
    while(token!=NULL){
        count++;
        token=strtok(NULL,delim);
        cmdline[count]=token;
    }
    return count;
}

int threadCheck(char **cmdline, int argc){
    if(!strcmp(cmdline[argc-1],"&t")){
        //printf("Thraed prsent\n");
        return 1;
    }
    return 0;
}


void wel(){
    char* buffer;
buffer=getcwd(NULL,0);
    if(buffer==NULL){
        return;
    }
    else{
        strcat(pathh,buffer);
    }
}

void pwd_fun(){
    char* buffer;
buffer=getcwd(NULL,0);
    if(buffer==NULL){
        printf("\nError: directory buffer overflow\n");
    }
    else{
        printf("%s\n",buffer);
    }
}


void echo_fun(){
    pid_t ret_value;
    //printf("\n process id is %d\n ",getpid());
    ret_value=fork();
    if (ret_value<0)
    {
        printf("Fork failed\n");
        return;
    }
    if(ret_value==0){
        char *args[]={"echo","--help",NULL};
        execvp(args[0],args);
    }
    else
    {
        wait(NULL);
    }
}


int sense(char **cmdline,int argc,int th){
    char pwd[]="pwd";
    char cd[]="cd";
    char echo[]="echo";
    char cat[]="cat";
    char rm[]="rm";
    char mkdir[]="mkdir";
    char date[]="date";
    char ls[]="ls";
    
    if(!strcmp(cmdline[0],pwd)){
        char pwdL[]="-L";
        char pwdP[]="-P";
        if(argc==1){
            //printf(" \nEqual pwd\n");
            pwd_fun();
            return 1;
        }
        else if (!strcmp(cmdline[1],pwdL) && argc==2){
        //printf(" \nEqual pwd L \n");
        pwd_fun();
        return 2;
        }
        else if (!strcmp(cmdline[1],pwdP) && argc==2){
        //printf(" \nEqual pwd P\n");
        pwd_fun();
        return 3;
        }
        else{
            printf("pwd command syntax not appropriate\n");
        }
    }

    else if(!strcmp(cmdline[0],cd)){
        char cdH[]="~";
        char cdB[]="..";
        if(argc==1){
            //printf(" \nEqual cd\n");
            chdir("/home");
            return 1;
        }
        else if (!strcmp(cmdline[1],cdH) && argc==2){
        //printf(" \nEqual cd ~ \n");
        chdir("/home");
        return 2;
        }
        else if (!strcmp(cmdline[1],cdB) && argc==2){
        //printf(" \nEqual cd .. P\n");
        chdir("..");
        return 3;
        }
        else if (argc==2){
            if(chdir(cmdline[1])){
                printf("%s: No such file or directory\n",cmdline[1]);}
            return 3;
        }
        else{
            printf("cd command syntax not appropriate\n");
        }
    }

    else if(!strcmp(cmdline[0],echo)){
        char echoN[]="-n";
        if(argc==1){
            //printf(" \nEqual echo\n");
            //just print blank line
            printf("\n");
            return 1;
        }
        else if (!strcmp(cmdline[1],echoN) && argc>=2){
            int i =2;
            char custom[400]="";
            while(i<argc){
                strcat(custom," ");
                strcat(custom,cmdline[i]);
                i++;
            }
            printf("%s",custom);
        //just print entire line
        return 2;
        }
        else if (!strcmp(cmdline[1],"--help") && argc==2){
        echo_fun();
        return 23;
        }
        else if (!strcmp(cmdline[1],"*") && argc==2){
        ls_fun(1,cmdline,0,1);
        return 23;
        }
        else if (argc>=2){
            int i =1;
            char custom[400]="";
            while(i<argc){
                strcat(custom," ");
                strcat(custom,cmdline[i]);
                i++;
            }
            printf("%s\n",custom);
        return 3;
        }
        else{
            printf("echo command syntax not appropriate\n");
        }
    }

    else if(!strcmp(cmdline[0],cat) && argc>1){
        char catN[]="-n";
        char catS[]="-e";
        if(argc==2){
            //printf(" \nEqual cat th val %d \n",th);
            cat_fun(1,cmdline,th,argc);
            return 11;
        }
        else if (!strcmp(cmdline[1],catN) && argc==3){
        //printf(" \nEqual CAT N \n");
        cat_fun(2,cmdline,th,argc);
        return 12;
        }
        else if (!strcmp(cmdline[1],catS) && argc==3){
        //printf(" \nEqual CAT S\n");
        cat_fun(3,cmdline,th,argc);
        return 13;
        }
        else if(argc>=3){
            //printf("Here bro\n");
            cat_fun(7,cmdline,0,argc);
        }
        else{
            printf("cat command syntax not appropriate\n");
        }
    }

    else if(!strcmp(cmdline[0],rm) && argc>1){
        char rmI[]="-i";
        char rm2D[]="-v";
        if(argc==2){
            //printf(" \nEqual rm\n");
            rm_fun(1,cmdline,th,argc);
            return 21;
        }
        else if (!strcmp(cmdline[1],rm2D) && argc==3){
        //printf(" \nEqual rmi \n");
        rm_fun(2,cmdline,th,argc);
        return 22;
        }
        else if (!strcmp(cmdline[1],rmI) && argc==3){
        //printf(" \nEqual rm-- \n");
        rm_fun(3,cmdline,th,argc);
        return 23;
        }
        else if(argc>=3){
            //printf("Here bro\n");
            rm_fun(7,cmdline,0,argc);
        }
        else{
            printf("rm command syntax not appropriate\n");
        }
    }

    else if(!strcmp(cmdline[0],mkdir) && argc>1){
        char mkdirP[]="-p";
        if(argc==2){
            //printf(" \nEqual mkdir\n");
            mkdir_fun(1,cmdline,th,argc);
            return 31;
        }
        else if (!strcmp(cmdline[1],mkdirP) && argc==3){
        //printf(" \nEqual mkdir -p \n");
        mkdir_fun(2,cmdline,th,argc);
        return 32;
        }
        else if (!strcmp(cmdline[1],"-v") && argc==3){
        //printf(" \nEqual mkdir -p \n");
        mkdir_fun(3,cmdline,th,argc);
        return 32;
        }
        else if(argc>=3){
            //printf("Here bro\n");
            mkdir_fun(7,cmdline,0,argc);
        }
        else{
            printf("mkdir command syntax not appropriate\n");
        }
    }

    else if(!strcmp(cmdline[0],date)){
        char dateU[]="-u";
        char dateR[]="-r";
        if(argc==1){
            //printf(" \nEqual date\n");
            dates_fun(1,cmdline,th);
            return 41;
        }
        else if (!strcmp(cmdline[1],dateU) && argc==2){
        //printf(" \nEqual date -u \n");
        dates_fun(2,cmdline,th);
        return 42;
        }
        else if (!strcmp(cmdline[1],dateR) && argc==3){
        //printf(" \nEqual date -r filename \n");
        dates_fun(3,cmdline,th);
        return 43;
        }
        else{
            printf("date command syntax not appropriate\n");
        }
    }

    else if(!strcmp(cmdline[0],ls)){
        char lsA[]="-a";
        char lsL[]="-m";
        if(argc==1){
            //printf(" \nEqual ls\n");
            ls_fun(1,cmdline,th,argc);
            return 51;
        }
        else if (!strcmp(cmdline[1],lsA) && argc==2){
        //printf(" \nEqual ls -a \n");
        ls_fun(2,cmdline,th,argc);
        return 52;
        }
        else if(!strcmp(cmdline[1],lsL) && argc==2){
        //printf(" \nEqual ls -l \n");
        ls_fun(3,cmdline,th,argc);
        return 53;
        }
        else if(argc>=2){
            ls_fun(7,cmdline,0,argc);
        }
        else{
            printf("ls command syntax not appropriate\n");
        }
    }
    else if(!strcmp(cmdline[0],"help")){
        printf("Help is here:\n");
        printf("1. cd: cd, cd~, cd /, cd path, cd ..\n");
        printf("2. pwd: pwd -L, pwd -P\n");
        printf("3. echo: echo YourContent, echo -n YourContent\n");
        printf("4. ls: ls -a, ls -m\n");
        printf("5. cat: cat filename, cat -n filename, cat -e filename\n");
        printf("6. date: date, date -u, date -r filename\n");
        printf("7. rm: rm filename, rm -i filename, rm -v filename\n");
        printf("8. mkdir: mkdir dir, mkdir -p dir, mkdir -v dir1\n");
    }
    else{
        printf("Error: command not found\n");
    }
}


int main(){
    char cmd[max];
    char *cmdline[max];
    printf("**************Parveen Custom Shell***************\n");
    wel();
    //printf("path %s\n",pathh);
    while (1)
    {
        printf("%s",prompt);
        if((fgets(cmd,max,stdin)==NULL)){
            printf("\nCommand length overflow\n");
            break;
        }
        cmd[strlen(cmd)-1]='\0';
        int argcount = generator(cmd,cmdline);
        if(argcount==-1){
            // blank line
            continue;
        }
        int i=0;
    //     while(i<argcount){
    //         printf("%s | ",cmdline[i]);
    //         i++;
    // }
        int th = threadCheck(cmdline,argcount);
        if(th){
            // printf("th val %d\n",th);
            argcount--;
            int val = sense(cmdline,argcount,th);
        }
        else{
            int val = sense(cmdline,argcount,th);
        }
    }
    return 0;
}