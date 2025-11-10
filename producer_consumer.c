// CSE3PM11A - Operating Systems Lab
// Department of Computer Engineering and Technology
// Assignment: Producer–Consumer Problem using Semaphores

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems 5     // Maximum items each producer/consumer handles
#define BufferSize 5   // Size of the buffer

sem_t empty, full;
pthread_mutex_t mutex;

int in = 0, out = 0;
int buffer[BufferSize];

// Producer function
void *producer(void *pno) {
    int item;
    for (int i = 0; i < MaxItems; i++) {
        item = rand() % 100;  // Produce a random item
        sem_wait(&empty);     // Decrement empty count
        pthread_mutex_lock(&mutex);  // Enter critical section

        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n",
               *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize;

        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&full);               // Increment full count
    }
    pthread_exit(NULL);
}

// Consumer function
void *consumer(void *cno) {
    for (int i = 0; i < MaxItems; i++) {
        sem_wait(&full);               // Wait if buffer is empty
        pthread_mutex_lock(&mutex);    // Enter critical section

        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",
               *((int *)cno), item, out);
        out = (out + 1) % BufferSize;

        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&empty);              // Increment empty count
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t pro[5], con[5];
    int a[5] = {1, 2, 3, 4, 5};  // Thread identifiers

    // Initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);

    // Create producer threads
    for (int i = 0; i < 5; i++)
        pthread_create(&pro[i], NULL, producer, (void *)&a[i]);

    // Create consumer threads
    for (int i = 0; i < 5; i++)
        pthread_create(&con[i], NULL, consumer, (void *)&a[i]);

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
        pthread_join(con[i], NULL);
    }

    // Cleanup
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("\nAll producers and consumers have finished execution.\n");
    return 0;}

//gcc producer_consumer.c -lpthread -o producer_consumer
}
