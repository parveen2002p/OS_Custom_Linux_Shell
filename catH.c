#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

// int main(){
//     char filename[]={"demo.txt"};
//     cat(2,filename);
//     printf("\nSuccess\n");
//     return 0;
// }

// struct arg_struct{
//     char **cmdline;
//     int target;
// };

void * cat_th(void *arguments){
    struct arg_struct *args = arguments;
    int target = args->target;
    char **cmdline = args->cmdline;
    int argc = args->argc;
    if(target ==1){
        //char custom[200]="./cat 0 0 ";
        char custom[250];
        memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./cat 0 0 ");
        strcat(custom,cmdline[1]);
        if(system(custom)!=0){
            printf("\n");
        }
    }
    else if(target ==2){
        //  char custom[200]="./cat 1 0 ";
        char custom[250];
        memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./cat 1 0 ");
        strcat(custom,cmdline[2]);
        strcat(custom," 1");
        if(system(custom)!=0){
            printf("\n");
        }
    }
    else if(target ==3){
         //char custom[200]="./cat 0 1 ";
         char custom[250];
         memset(custom, 0, sizeof custom);
        strcat(custom,pathh);
        strcat(custom,"/./cat 0 1 ");
        strcat(custom,cmdline[2]);
        if(system(custom)!=0){
            printf("\n");
        }
    }
    // else if(target==7){
    //     //printf("Inside threead");
    //     char custom[200]="";
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

int count(char *filename,int j){
   FILE * fp;
    size_t curlen = 0;
    ssize_t ret;
    char * current = NULL;

    fp = fopen(filename, "r");
    if (fp == NULL){
        return 0;}

    while ((ret = getline(&current, &curlen, fp)) != -1) {
        j++;
    }
    fclose(fp);
    if (current){
        free(current);}
    return j;
 }    

void cat_fun(int target,char **cmdline,int th,int argc){
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
        pthread_create(&tid,NULL,cat_th,(void *)&args);
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
        // char *args[]={"cat",filename,NULL};
        // //execvp(args[0],args);
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./cat");
        char *args[]={custom,"0","0",cmdline[1],NULL};
        execvp(args[0],args);
    }
    else if(target==2 && ret_value==0){
        //printf("\nChild %d PID\n",getpid());
        // char *filename=cmdline[2];
        // char *args[]={"cat","-n",filename,NULL};
        // //execvp(args[0],args);
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./cat");
        char *args[]={custom,"1","0",cmdline[2],"1",NULL};
        execvp(args[0],args);
    }
    else if(target==3 && ret_value==0){
        //printf("\nChild %d PID\n",getpid());
        // char *filename=cmdline[2];
        // char *args[]={"cat","-s",filename,NULL};
        // //execvp(args[0],args);
        char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./cat");
        char *args[]={custom,"0","1",cmdline[2],NULL};
        execvp(args[0],args);
    }
    else if(target==7 && ret_value==0){

        if(!strcmp(cmdline[1],"-n")){
            int j=1;
        for(int i =2;i<argc;i++){
            pid_t ret_value1;
            ret_value1=fork();
            if (ret_value1<0){
                printf("Fork failed\n");
                return;}
            else if(ret_value1==0){
                char jstring[50];
                sprintf(jstring, "%d",j);
                char custom[250];
            strcat(custom,pathh);
            strcat(custom,"/./cat");
            char *args[]={custom,"1","0",cmdline[i],jstring,NULL};
            execvp(args[0],args);
            }
            else{
                wait(NULL);}
            int lp = count(cmdline[i],1);
            if(lp==0){
                j+=0;
            }
            else{
                j+=lp;
                j--;
            }  
        }}
        else if(!strcmp(cmdline[1],"-e")){
            for(int i =2;i<argc;i++){
            pid_t ret_value1;
            ret_value1=fork();
            if (ret_value1<0){
                printf("Fork failed\n");
                return;}
            else if(ret_value1==0){
                char custom[250];
        strcat(custom,pathh);
        strcat(custom,"/./cat");
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
        strcat(custom,"/./cat");
            char *args[]={custom,"0","0",cmdline[i],NULL};
            execvp(args[0],args);
            }
            else{
                wait(NULL);}
        }
        }
        //printf("In 7 cat\n");
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

