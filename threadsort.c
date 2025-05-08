#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define n 10 //size

int arr[n];
int sorted[n];

void * sortfirst(void * arg){
int temp;
//applying bubble sort for first half
for(int i=0;i<n/2;i++){
for(int j=0;j<n/2-1-i;j++){
if(arr[j]>arr[j+1]){
temp=arr[j];
arr[j]=arr[j+1];
arr[j+1]=temp;
}
}
}
pthread_exit(NULL);
}

void* sortsec(void * arg){
int temp;
for(int i=n/2;i<n;i++){
for(int j=n/2;j<n-1-(i-n/2);j++){
if(arr[j]>arr[j+1]){
temp=arr[j];
arr[j]=arr[j+1];
arr[j+1]=temp;
}
}
}
pthread_exit(NULL);
}

//merging both
void merge(){
int i=0,j=n/2,k=0;

while(i<n/2 && j<n){
if(arr[i]<arr[j]){
sorted[k++]=arr[i++];
}
else{
sorted[k++]=arr[j++];
}
}

while(i<n/2){
sorted[k++]=arr[i++];
}

while(j<n){
sorted[k++]=arr[j++];
}
}



int main(){
pthread_t t1,t2;//declaring threads

printf("Enter array elements: ");
for(int i=0;i<n;i++){
scanf("%d",&arr[i]);
}

pthread_create(&t1,NULL,sortfirst,NULL);
pthread_create(&t2,NULL,sortsec,NULL);

pthread_join(t1,NULL);
pthread_join(t2,NULL);
merge();

printf("SORTED ARRAY: \n");
for(int i=0;i<n;i++){
printf(" %d ",sorted[i]);
}

return 0;
}
