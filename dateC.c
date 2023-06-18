#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<sys/wait.h>

// struct arg_struct{
//     char **cmdline;
//     int target;
// };

// int main(){
//     char customDate[]={"10 year ago"};
//     dates_fun(1,customDate,1);
//     printf("\nSuccess\n");
//     return 0;
// }
struct arg_struct{
    char **cmdline;
    int target;
    int argc;
};

void * dates_th(void *arguments){
    struct arg_struct *args = arguments;
    int target = args->target;
    char **cmdline = args->cmdline;
    int argc = args->argc;
    if(target ==1){
        char custom[250];
        memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./date 0 0");
        if(system(custom)!=0){
            printf("\n");
        }
    }
    else if(target ==2){
        char custom[250];
        memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./date 1 0");
        if(system(custom)!=0){
            printf("\n");
        }
    }
    else if(target ==3){
        //char custom[200]="./date 0 1 ";
        char custom[250];
        memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./date 0 1 ");
        strcat(custom,cmdline[2]);
        if(system(custom)!=0){
            printf("\n");
        }
    }
}

void dates_fun(int target,char **cmdline,int th){
    if(th){
        pid_t ret_value;
        ret_value=fork();
        if(ret_value==0){
        struct arg_struct args;
        args.cmdline=cmdline;
        args.target=target;
        args.argc=0;
        //printf("Inside\n");
        pthread_t tid;
        pthread_create(&tid,NULL,dates_th,(void *)&args);
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
        //char *args[]={"date",NULL};
        //execvp(args[0],args);
        //_dateI();
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./date");
        char *args[]={custom,"0","0",NULL};
        execvp(args[0],args);
    }
    else if(target==2 && ret_value==0){
        //printf("\nChild %d PID\n",getpid());
        //char *args[]={"date","-u",NULL};
        //execvp(args[0],args);
        //_dateU();
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./date");
        char *args[]={custom,"1","0",NULL};
        execvp(args[0],args);
    }
    else if(target==3 && ret_value==0){
        //printf("\nChild %d PID\n",getpid());
        //char *args[]={"date",cmdline[1],cmdline[2],NULL};
        //execvp(args[0],args);
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./date");
        char *args[]={custom,"0","1",cmdline[2],NULL};
        execvp(args[0],args);
    }
    else
    {
        wait(NULL);
        //printf("\nParent %d pid\n",getpid());
    }
}
