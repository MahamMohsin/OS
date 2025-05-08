#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void childterminated() {
pid_t pid;
int wstat;//child status

//getting pid till a chld process keeps terminating
while(pid=waitpid(-1,&wstat,WNOHANG)>0){
printf("Child process terminated with pid = %d\n",pid);
}
}

int main(){
int pid=fork();
srand(time(NULL));//used when generating rand num for termination of child

if(pid==-1){
printf("Error in forking!");
return 1;
}

else if(pid == 0){//child
printf("Child process\n");
int code=rand();//child termination code
printf("child terminated with code: %d\n",code);
exit(code);
}

else{//parent >0
signal(SIGCHLD,childterminated);
pause();//waits for termination
}
return 0;
}
