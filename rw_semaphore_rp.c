// Readers–Writers Problem using Semaphores (Readers Priority)
// CSE3PM11A - Operating Systems Lab
// Department of Computer Engineering and Technology

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int readercount = 0;
int sharedvar = 99;

// Reader function
void *reader(void *arg) {
    int id = *((int *)arg);
    sem_wait(&mutex);
    readercount++;
    if (readercount == 1)
        sem_wait(&wrt);  // First reader locks writers
    sem_post(&mutex);

    printf("\nReader %d is READING sharedvar = %d", id, sharedvar);
    sleep(1);
    printf("\nReader %d is DONE reading", id);

    sem_wait(&mutex);
    readercount--;
    if (readercount == 0)
        sem_post(&wrt);  // Last reader unlocks writers
    sem_post(&mutex);

    pthread_exit(NULL);
}

// Writer function
void *writer(void *arg) {
    int id = *((int *)arg);
    printf("\nWriter %d is TRYING to enter", id);
    sem_wait(&wrt);  // Lock for writers
    printf("\nWriter %d has ENTERED Critical Section", id);

    sharedvar++;
    printf("\nWriter %d CHANGED sharedvar TO %d", id, sharedvar);
    sleep(1);

    printf("\nWriter %d is EXITING Critical Section", id);
    sem_post(&wrt);

    pthread_exit(NULL);
}

// Main function
int main() {
    int n, i;
    printf("Enter the number of readers and writers: ");
    scanf("%d", &n);

    pthread_t readers[n], writers[n];
    int id[n];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < n; i++) {
        id[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &id[i]);
        pthread_create(&readers[i], NULL, reader, &id[i]);
    }

    for (i = 0; i < n; i++) {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    printf("\n\nAll readers and writers have finished execution.\n");
    return 0;
}
