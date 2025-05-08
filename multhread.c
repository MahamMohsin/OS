#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define n 10 //size

int arr[n];
int product1=1;
int product2=1;
int result;

void* firsthalf(void * arg){
for(int i=0;i<n/2;i++){
product1*=arr[i];
}
pthread_exit(NULL);
}

void* sechalf(void* arg){
for(int i=n/2;i<n;i++){
product2*=arr[i];
}
pthread_exit(NULL);
}

void combine(){
result=product1*product2;
}

int main(){
pthread_t t1,t2;
printf("Enter array elements: ");
for(int i=0;i<n;i++){
scanf("%d",&arr[i]);
}

pthread_create(&t1,NULL,firsthalf,NULL);
pthread_create(&t2,NULL,sechalf,NULL);

pthread_join(t1,NULL);
pthread_join(t2,NULL);
combine();

printf("Final result: %d",result);

return 0;
}


