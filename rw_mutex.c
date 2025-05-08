#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* write_to_file(void* arg) {
    FILE* file = fopen("file.txt", "w");
    pthread_mutex_lock(&mutex);
    fprintf(file, "Thread 1: Writing data.\n");
    fclose(file);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* read_from_file(void* arg) {
    FILE* file = fopen("file.txt", "r");
    char buffer[256];
    pthread_mutex_lock(&mutex);
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* append_to_file(void* arg) {
    FILE* file = fopen("file.txt", "a");
    pthread_mutex_lock(&mutex);
    fprintf(file, "Thread 3: Appending data.\n");
    fclose(file);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, write_to_file, NULL);
    pthread_create(&t2, NULL, read_from_file, NULL);
    pthread_create(&t3, NULL, append_to_file, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
