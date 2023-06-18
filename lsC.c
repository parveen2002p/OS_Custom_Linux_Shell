#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/wait.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

// int main(int argc, char const *argv[])
// {
    
//     int a = atoi(argv[2]);
//     int l = atoi(argv[3]);
//     _ls(argv[1],a,l);
//     return 0;
// }

// struct arg_struct{
//     char **cmdline;
//     int target;
//     int argc;
// };

void * ls_th(void *arguments){
    struct arg_struct *args = arguments;
    int target = args->target;
    char **cmdline = args->cmdline;
    int argc = args->argc;
    //printf("Target %d",target);
    if(target ==1){
        char custom[250];
        memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./ls . 0 0");
        if(system(custom)!=0){
            printf("\n");
        }
    }
    else if(target ==2){
        char custom[250];
        memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./ls . 1 0");
        if(system(custom)!=0){
            printf("\n");
        }
    }
    else if(target ==3){
        char custom[250];
        memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./ls . 0 1");
        if(system(custom)!=0){
            printf("\n");
        }
    }
    // else if(target==7){
    //     //printf("Inside threead");
    //     char custom[200]="./ls";
    //     for(int i =0;i<argc;i++){
    //         strcat(custom,cmdline[i]);
    //         strcat(custom," ");
    //     }
    //     //printf("%s",custom);
    //     if(system(custom)!=0){
    //         printf("\n");
    //     }
    // }
}

void ls_fun(int target,char **cmdline,int th,int argc){
    if(th){
        pid_t ret_value;
        ret_value=fork();
        if(ret_value==0){
        struct arg_struct args;
        args.cmdline=NULL;
        args.target=target;
        args.argc=argc;
        //printf("INside\n");
        pthread_t tid;
        pthread_create(&tid,NULL,ls_th,(void *)&args);
        pthread_join(tid,NULL);
        //pthread_exit(NULL);
        }
        else
    {
        wait(NULL);
    }
        return;
    }
    pid_t ret_value;
    // printf("\n process id is %d\n ",getpid());
    ret_value=fork();
    if (ret_value<0)
    {
        printf("Fork failed\n");
        return;
    }
    if(target==1 && ret_value==0){
        // printf("\nChild %d PID\n",getpid());
        //char *args[]={"ls",NULL};
        //execvp(args[0],args);
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./ls");
        char *args[]={custom,".","0","0",NULL};
        execvp(args[0],args);
        
    }
    else if(target==2 && ret_value==0){
        //printf("\nChild %d PID\n",getpid());
        //char *args[]={"ls","-l",NULL};
        //execvp(args[0],args);
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./ls");
        char *args[]={custom,".","1","0",NULL};
        execvp(args[0],args);
    }
    else if(target==3 && ret_value==0){
        //printf("\nChild %d PID\n",getpid());
        //char *args[]={"ls","-a",NULL};
        //execvp(args[0],args);
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./ls");
        char *args[]={custom,".","0","1",NULL};
        execvp(args[0],args);
    }
    else if(target==7 && ret_value==0){

        if(!strcmp(cmdline[1],"-a")){
        for(int i =2;i<argc;i++){
            printf("%s:\n",cmdline[i]);
            pid_t ret_value1;
            ret_value1=fork();
            if (ret_value1<0){
                printf("Fork failed\n");
                return;}
            else if(ret_value1==0){
                char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./ls");
            char *args[]={custom,cmdline[i],"1","0",NULL};
            execvp(args[0],args);}
            else{
                wait(NULL);}
        }}
        else if(!strcmp(cmdline[1],"-m")){
            for(int i =2;i<argc;i++){
              printf("%s:\n",cmdline[i]);
            pid_t ret_value1;
            ret_value1=fork();
            if (ret_value1<0){
                printf("Fork failed\n");
                return;}
            else if(ret_value1==0){
                char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./ls");
            char *args[]={custom,cmdline[i],"0","1",NULL};
            execvp(args[0],args);}
            else{
                wait(NULL);}
        }
        }
        else{
            for(int i =1;i<argc;i++){
               printf("%s:\n",cmdline[i]);
            pid_t ret_value1;
            ret_value1=fork();
            if (ret_value1<0){
                printf("Fork failed\n");
                return;}
            else if(ret_value1==0){
                char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./ls");
            char *args[]={custom,cmdline[i],"0","0",NULL};
            execvp(args[0],args);}
            else{
                wait(NULL);}
        }
        }
        //printf("In 7\n");
        // char *args[argc];
        // for(int i =0;i<argc;i++){
        //     args[i]=cmdline[i];
        // }
        // args[argc]=NULL;
        // execvp(args[0],args);
    }
    else
    {
        wait(NULL);
        //printf("\nParent %d pid\n",getpid());
    }
}

