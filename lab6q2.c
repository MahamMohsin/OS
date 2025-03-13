#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//defining pipe id
#define fifoid "/tmp/my_fifo"
#define BUFFER_SIZE 256

//sender writes user inputted msg to named piped
void sender(){
int fifofd;//instead of pipefd[]
char msg[BUFFER_SIZE];

//creating fifo if it doesnt exist
if(mkfifo(fifoid , 0666) == -1){
printf("mkfifo");
return 1;
}

printf("Enter message to send: ");
fgets(msg,BUFFER_SIZE,stdin);

//open fifo for writing
fifofd=open(fifoid,O_WRONLY);
if(fifofd==-1){
printf("error opening");
return 1;
}

//write msg to FIFO
if(write(fifofd,msg,strlen(msg)+1)==-1){
printf("error to write");
close(fifoid);
return 1;
}

close(fifoid);
}

//reads and displays msg from fifo
void receiver(){
int fifoid;
char buffer[BUFFER_SIZE];

//open fifo for reading
fifoid=open(fifoid,O_RDONLY);
if(fifoid==-1){
printf("Error opening");
return 1;
}

//read msg from fifo
if(read(fifofd,buffer,BUFFER_SIZE)==-1){
printf("error reading");
close(fifofd);
return 1;
}


printf("Message received %s\n",buffer);
close(fifofd);
}

int main(int argc,char argv[]){
if(argc!=2){
printf("Correct use: %s Receiver|Sender",argv[0]);
return 1;
}

if(strcmp(argv[1],"sender") == 0){
sender();
}
else if(strcmp(argv[1],"receiver") == 0){
receiver();
}
else{
printf("Invaliddd!");
}
return 0;
}


