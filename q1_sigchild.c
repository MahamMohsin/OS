#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

pid_t childs[3];//declaring 3 child process

void sighandler(int signum){
int status;//child stat
pid_t pid;

//reap
while((pid=waitpid(-1,&status,WNOHANG))>0){
if( pid != childs[2])//ignore msg for child 2
{
printf("Child terminated with pid: %d\n",pid);
}
}
}

int main(){
signal(SIGCHLD,sighandler);//registering siganl

pid_t pid;
for (int i=0;i<3;i++){
pid=fork();//making 3 childs

if(pid<0){
printf("Error in forking!");
exit(1);
}

if(pid==0){
sleep(2+i);//sep time for each child
exit(0);
}
else{
childs[i]=pid;
}
}

//parent process
while(1){pause();}
return 0;
}

