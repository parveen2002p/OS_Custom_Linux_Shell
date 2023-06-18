#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

// int main(){
//     char filename[]={"demo.txt"};
//     rm(3,filename);
//     printf("\nSuccess\n");
//     return 0;
// }
// struct arg_struct{
//     char **cmdline;
//     int target;
// };
// struct arg_struct{
//     char **cmdline;
//     int target;
//     int argc;
// };

void * rm_th(void *arguments){
    struct arg_struct *args = arguments;
    int target = args->target;
    char **cmdline = args->cmdline;
    int argc = args->argc;
    if(target ==1){
        // char custom[200]="./rm 0 0 ";
        // memset(custom, 0, sizeof custom);
        char custom[250];
        memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./rm 0 0 ");
        strcat(custom,cmdline[1]);
        if(system(custom)!=0){
            printf("\n");
        }
    }
    else if(target ==2){
        // char custom[200]="./rm 1 0 ";
        // memset(custom, 0, sizeof custom);
        char custom[250];
        memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./rm 1 0 ");
        strcat(custom,cmdline[2]);
        if(system(custom)!=0){
            printf("\n");
        }
    }
    else if(target ==3){
        // char custom[200]="./rm 0 1 ";
        // memset(custom, 0, sizeof custom);
        char custom[250];
        memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./rm 0 1 ");
        strcat(custom,cmdline[2]);
        if(system(custom)!=0){
            printf("\n");
        }
    } 
}

void rm_fun(int target,char **cmdline,int th,int argc){
    if(th){
        pid_t ret_value;
        ret_value=fork();
        if(ret_value==0){
        struct arg_struct args;
        args.cmdline=cmdline;
        args.target=target;
        args.argc=argc;
        //printf("Inside\n");
        pthread_t tid;
        pthread_create(&tid,NULL,rm_th,(void *)&args);
        pthread_join(tid,NULL);
        // pthread_exit(NULL);
        }
        else
    {
        wait(NULL);
    }
    return;
    }
    pid_t ret_value;
    //printf("\n process id is %d\n ",getpid());
    ret_value=fork();
    if (ret_value<0)
    {
        printf("Fork failed\n");
        return;
    }
    if(target==1 && ret_value==0){
        //printf("\nChild %d PID\n",getpid());
        // char *filename=cmdline[1];
        // char *args[]={"rm",filename,NULL};
        // execvp(args[0],args);
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./rm");
        char *args[]={custom,"0","0",cmdline[1],NULL};
        execvp(args[0],args);
    }
    else if(target==2 && ret_value==0){
        //printf("\nChild %d PID\n",getpid());
        // char *filename=cmdline[2];
        // char *args[]={"rm","-i",filename,NULL};
        // execvp(args[0],args);
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./rm");
        char *args[]={custom,"1","0",cmdline[2],NULL};
        execvp(args[0],args);
    }
    else if(target==3 && ret_value==0){
        //printf("\nChild %d PID\n",getpid());
        // char *filename=cmdline[2];
        // char *args[]={"rm","--",filename,NULL};
        // execvp(args[0],args);
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./rm");
        char *args[]={custom,"0","1",cmdline[2],NULL};
        execvp(args[0],args);
    }
    else if(target==7 && ret_value==0){
        
        if(!strcmp(cmdline[1],"-v")){
        for(int i =2;i<argc;i++){
            pid_t ret_value1;
            ret_value1=fork();
            if (ret_value1<0){
                printf("Fork failed\n");
                return;}
            else if(ret_value1==0){
                char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./rm");
            char *args[]={custom,"1","0",cmdline[i],NULL};
            execvp(args[0],args);
            }
            else{
                wait(NULL);}
        }}
        else if(!strcmp(cmdline[1],"-i")){
            for(int i =2;i<argc;i++){
            pid_t ret_value1;
            ret_value1=fork();
            if (ret_value1<0){
                printf("Fork failed\n");
                return;}
            else if(ret_value1==0){
                char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./rm");
            char *args[]={custom,"0","1",cmdline[i],NULL};
            execvp(args[0],args);
            }
            else{
                wait(NULL);}
        }
        }
        else{
            for(int i =1;i<argc;i++){
            pid_t ret_value1;
            ret_value1=fork();
            if (ret_value1<0){
                printf("Fork failed\n");
                return;}
            else if(ret_value1==0){
                char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./rm");
            char *args[]={custom,"0","0",cmdline[i],NULL};
            execvp(args[0],args);
            }
            else{
                wait(NULL);}
        }
        }
        //printf("In 7 rm\n");
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