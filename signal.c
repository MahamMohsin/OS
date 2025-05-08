#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
int count=0;
void sig_hand(int signum){
	printf("Entered in SIGINT signal\n");
	if(count>1){
	exit(signum);
	}count++;
}
int main(){
	printf("Press CTRL+C to enter a signal\n");
	signal(SIGINT,sig_hand);
	while(1){
		sleep(0.5);
	}
	return 0;
}
