#include <stdlib.h> // for atoi
#include <stdio.h>
#include <limits.h> // for INT_MAX and INT_MIN
#include <pthread.h>

int* nums;
int numcount;
double avgfinal;
int maxval, minval;

// COMPUTE AVG
void* avg(void *arg){
    int sum = 0;
    for(int i = 0; i < numcount; i++){
        sum += nums[i];
    }
    avgfinal = (double)sum / numcount;
    pthread_exit(NULL);
}

// COMPUTE MIN
void* min(void *arg){
    minval = INT_MAX;
    for(int i = 0; i < numcount; i++){
        if(minval > nums[i]){
            minval = nums[i];
        }
    }
    pthread_exit(NULL);
}

// COMPUTE MAX
void* max(void *arg){
    maxval = INT_MIN;
    for(int i = 0; i < numcount; i++){
        if(maxval < nums[i]){
            maxval = nums[i];
        }
    }
    pthread_exit(NULL);
}

// MAIN 
int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Correct usage: %s <numbers>\n", argv[0]);
        return 1;
    }

    numcount = argc - 1;
    nums = (int *) malloc(numcount * sizeof(int));
    for(int i = 0; i < numcount; i++){
        nums[i] = atoi(argv[i + 1]); // i+1 because argv[0] is the program name
    }

    pthread_t tavg, tmin, tmax;

    pthread_create(&tavg, NULL, avg, NULL);
    pthread_create(&tmin, NULL, min, NULL);
    pthread_create(&tmax, NULL, max, NULL);

    pthread_join(tavg, NULL);
    pthread_join(tmin, NULL);
    pthread_join(tmax, NULL);

    printf("Average: %.2f\n", avgfinal);
    printf("Max value: %d\n", maxval);
    printf("Min value: %d\n", minval);

    free(nums);
    return 0;
}

