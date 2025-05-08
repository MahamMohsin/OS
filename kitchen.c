#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_ORDERS 10

int orders[MAX_ORDERS];
int count = 0;

pthread_mutex_t mutex;
sem_t chef;

void* customer(void* arg) {
    int id = *(int*)arg;
    free(arg);

    pthread_mutex_lock(&mutex);
    if (count < MAX_ORDERS) {
        orders[count] = id;
        printf("Customer %d placed an order - total orders: %d\n", id, count + 1);
        count++;
    } else {
        printf("Customer %d: Kitchen full!\n", id);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* chef(void* arg) {
    while (1) {
        sem_wait(&chef); // Wait for a chef slot

        pthread_mutex_lock(&mutex);
        if (count > 0) {
            int ord_id = orders[--count];
            printf("Chef %ld is prepping for customer %d [remaining orders: %d]\n", pthread_self(), ord_id, count);
            pthread_mutex_unlock(&mutex);

            sleep(rand() % 3); // Simulate prep time
            printf("Chef %ld finished prepping for customer %d\n", pthread_self(), ord_id);
        } else {
            pthread_mutex_unlock(&mutex);
            sem_post(&chef); // Release semaphore if no orders
            break;
        }

        sem_post(&chef); // Allow other chefs to proceed
    }

    return NULL;
}

int main() {
    pthread_t customers[MAX_ORDERS];
    pthread_t chefs[2];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&chef, 0, 2); // Initialize semaphore for 2 chefs

    // Create customer threads
    for (int i = 0; i < MAX_ORDERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&customers[i], NULL, customer, id);
        usleep(100000); // Small delay for realism
    }

    // Wait for all customers to place orders
    for (int i = 0; i < MAX_ORDERS; i++) {
        pthread_join(customers[i], NULL);
    }

    // Create chef threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&chefs[i], NULL, chef, NULL);
    }

    // Wait for chefs to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(chefs[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&chef);

    printf("All orders have been prepared.\n");

    return 0;
}

