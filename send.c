#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
#define MAX_SIZE 50
struct msgfm{
        long mtype;
        char mtext[MAX_SIZE];
    }send,recv;
void sending(char text[],int msgid){
        
        send.mtype=1;
        if(msgsnd(msgid,&send,MAX_SIZE,0)==-1){
            perror("Message sending failed");
        }/*else{
            printf("\n(sendmtype- %ld)",send.mtype);
        }*/

}
void receiving(int msgid){
    recv.mtype=2;
    if(msgrcv(msgid,&recv,MAX_SIZE,2,0)==-1){
        perror("receiving failed");
    }else{
        printf("\nnew message receieved: ");
        printf("%s",recv.mtext);
    }
    
    //printf("\n(recvmtype- %ld)",recv.mtype);
}
int main(){
    
    int msgid;
    if((msgid=msgget((key_t)106,IPC_CREAT|0666))==-1){
        perror("Message queue creation failed");
    }
    printf("message id: %d\n",msgid);
    char text[MAX_SIZE];
    
    
    do{
        printf("\nEnter message: ");
        gets(text);
        strcpy(send.mtext,text);
        sending(send.mtext,msgid);
        receiving(msgid);
    }while(strncmp(text,"end",3)!=0);


    

}
