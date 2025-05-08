#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter=0;
pthread_mutex_t mutex;//mutex declared
void* count(void * p){
int i;
int* param=(int*)p;
pthread_mutex_lock(&mutex);//only one tread can enter
for(i=0;i<5;i++){
counter++;
printf("Thread %d - count: %d\n",*param,counter);
}
pthread_mutex_unlock(&mutex);
pthread_exit(NULL);
}

int main(){
pthread_t t1,t2,t3;
int a=1,b=2,c=3;//thread nums
pthread_create(&t1,NULL,count,&a);
pthread_create(&t2,NULL,count,&b);
pthread_create(&t3,NULL,count,&c);

pthread_join(t1,NULL);
pthread_join(t2,NULL);
pthread_join(t3,NULL);

pthread_mutex_destroy(&mutex); //else would take memory
return 0;
}
