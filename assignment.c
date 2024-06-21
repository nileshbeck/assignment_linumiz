
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

typedef struct node{ //structure for stack node
char path[1024];//assuming path length 1024 char
struct node* next;
}node;



node* stacktop=NULL;//global variable for top stack

void push (const char* dir){//function to push a directory onto the stack
    node* newnode=(node*)malloc(sizeof(node));
    if(newnode==NULL){
        fprintf(stderr,"memory allocation failed\n");
        exit(EXIT_FAILURE);
    }else{
    strncpy(newnode->path,dir,sizeof(newnode->path));
    newnode->next=stacktop;
    stacktop=newnode;}
}


void pop(){//function  to pop the directory from the stack
    if(stacktop==NULL){
        fprintf(stderr,"stack underflow\n");
        exit(EXIT_FAILURE);
    }else{
        node*temp=stacktop;
        stacktop=stacktop->next;
        free(temp);
    }
}


//fun to change directory (chdir)and update current directory
void changedirectory(const char*dir){
    if(chdir(dir)!=0){
        perror("chdir");

    }
}

//func to get current working dir(getcwd)
void getcurrentdirectory(char* buffer,size_t size){
    if(getcwd(buffer,size)==NULL){
        perror("getcwd");

    }
}



int main(int argc,char*argv[]){
    if (argc<2){
        fprintf(stderr,"usage: %s directory\n",argv[0]);
        return EXIT_FAILURE;
    }

    char currentdir[1024];
    getcurrentdirectory(currentdir,sizeof(currentdir));

    //handle pushd and popd commands
    if(strcmp(argv[1],"pushd")==0&&argc==3){
        char newdir[1024];
        strncpy(newdir,argv[2],sizeof(newdir));
        push(currentdir);
        changedirectory(newdir);
    }else if (strcmp(argv[1],"popd")==0 && argc==2){
        if(stacktop==NULL){
            fprintf(stderr,"stack underflow --no directories in the stack\n");
            return EXIT_FAILURE;
        }
        changedirectory(stacktop->path);
        pop();
    }else{
        fprintf(stderr,"invalid arguments \n");
        return EXIT_FAILURE;

    }
//after execution
getcurrentdirectory(currentdir,sizeof(currentdir));
printf("%s\n",currentdir);

return EXIT_SUCCESS;
}
