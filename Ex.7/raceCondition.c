// File: lab4/race.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 20

long accum = 0;

void *square(void *param) {
    int x = *(int *)param;
    accum += x * x;
    //sleep(1);
    pthread_exit(NULL);
}

/**
 * this program creates 20 threads, each thread will calculate the square of its number and add it to the global variable accum
 */
int main() {
    // Create threads
    pthread_t threads[NUM_THREADS];
    int *params[NUM_THREADS];

    // creating a thread for each number from 1 to NUM_THREADS
    for (long t = 0; t < NUM_THREADS; t++) {
        params[t] = malloc(sizeof(int));  // allocate memory for the parameter
        *params[t] = t + 1;  // assign the parameter to t + 1
        pthread_create(&threads[t], NULL, square, (void *)params[t]);  // create the thread with square function
    }

    // joinning the threads and freeing the memory
    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
        free(params[t]);
    }

    printf("result of computation: %ld\n", accum);  // printing the result of the sum of the squares
    pthread_exit(NULL);  // exit the thread
}