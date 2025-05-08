#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double balance=10000;
pthread_mutex_t mutex;//declared a mutex

void* teller(void* arg){
int id=*(int *)arg;//teller id

//working for 4 transactions
for(int i=0;i<4;i++){
pthread_mutex_lock(&mutex);//locking 
int amt=(rand() % 2000) - 1000;//rand value bw -1000 to 1000
balance+=amt;
printf("Teller %d - processed trans: %d balance: %.2lf \n",id,amt,balance);
pthread_mutex_unlock(&mutex);
}
return NULL;
}

int main(){
pthread_t t[3];
int ids[3]={1,2,3};

pthread_mutex_init(&mutex,NULL);

//creating threads;
for(int i=0;i<3;i++){
pthread_create(&t[i],NULL,teller,&ids[i]);
}

//joining
for(int i=0;i<3;i++){
pthread_join(t[i],NULL);
}

//destroying mutex lock
pthread_mutex_destroy(&mutex);

printf("Final Account balance: %.2lf\n",balance);

return 0;
}
