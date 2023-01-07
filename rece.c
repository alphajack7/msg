#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#define MAX_SIZE 50
struct msgfm{
    long mtype;
    char mtext[MAX_SIZE];
}send,recv;
void receiving(int msgid){
    recv.mtype=1;
    if(msgrcv(msgid,&recv,MAX_SIZE,1,0)==-1){
        perror("receiving failed");
    }else{
        printf("\n new message receieved: ");
        printf("%s",recv.mtext);
        //printf("\n(recvmtype- %ld)",recv.mtype);
        
    }
    
    
}
void sending(char text[],int msgid){
    send.mtype=2;
    if(msgsnd(msgid,&send,MAX_SIZE,0)==-1){
        perror("sending failed");
    }/*else{
        printf("\n(sendmtype- %ld)",send.mtype);
    }*/
}
int main(){
    int msgid;
    if((msgid=msgget((key_t)106,IPC_CREAT|0666))==-1){
        perror("queue failed");
    }
    
    char text[MAX_SIZE];
    
    
    do{
    receiving(msgid);
    printf("\nEnter message: ");
    gets(text);
    strcpy(send.mtext,text);
    sending(send.mtext,msgid);
    }while(strncmp(recv.mtext,"end",3)!=0);

    
}
