#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 5

sem_t mut, empt, full;
int buf[BUFFSIZE];
int in = 0, out = 0;

void *prod(void *arg) {
    int it;
    while (1) {
        it = rand() % 100;

        sem_wait(&empt);     // Wait if buffer is full
        sem_wait(&mut);      // Lock critical section

        buf[in] = it;
        printf("producer: %d\n", buf[in]);
        fflush(stdout);      // Ensure immediate output
        in = (in + 1) % BUFFSIZE;

        sem_post(&mut);      // Unlock critical section
        sem_post(&full);     // Signal that item is added

        sleep(rand() % 3);   // Simulate work
    }
    return NULL;
}

void *cons(void *arg) {
    int it;
    while (1) {
        sem_wait(&full);     // Wait if buffer is empty
        sem_wait(&mut);      // Lock critical section

        it = buf[out];
        printf("consumer: %d\n", it);
        fflush(stdout);      // Ensure immediate output
        out = (out + 1) % BUFFSIZE;

        sem_post(&mut);      // Unlock critical section
        sem_post(&empt);     // Signal that slot is free

        sleep(rand() % 3);   // Simulate work
    }
    return NULL;
}

int main() {
    // Initialize semaphores
    sem_init(&mut, 0, 1);         // Binary semaphore for mutual exclusion
    sem_init(&empt, 0, BUFFSIZE); // Counting semaphore for empty slots
    sem_init(&full, 0, 0);        // Counting semaphore for full slots

    // Create threads
    pthread_t prodT, consT;
    pthread_create(&prodT, NULL, prod, NULL);
    pthread_create(&consT, NULL, cons, NULL);

    // Wait for threads (they run infinitely)
    pthread_join(prodT, NULL);
    pthread_join(consT, NULL);

    // Clean up (unreachable in this infinite loop version)
    sem_destroy(&mut);
    sem_destroy(&empt);
    sem_destroy(&full);

    return EXIT_SUCCESS;
}

