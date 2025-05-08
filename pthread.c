#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int sum=0;
//summation using threads
void * runner(void* num){
//int sum=0;//made local to thread
int i;
int upper=*(int *)num;

if(upper>=0){
for(i=0;i<=upper;i++){
sum+=i;
}
}
//pthread_exit((void*) (long)sum);
}

int main(){
pthread_t tid; //thread id
pthread_attr_t attr; //attr

int num;
void* retval;
printf("Enter a number you want summation of: ");
scanf("%d",&num);

if(num<0){
printf("enter valid num!");
return 1;
}

pthread_attr_init(&attr);//def attributes
pthread_create(&tid,NULL,runner,(void *)&num);//num sent as parameter
pthread_join(tid,NULL);
printf("Sum = %d",sum);
return 0;
}

//if we would have made sum local to thread then exit command would be needed 
//and in join instead of null &retval written.
