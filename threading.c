#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// Function to be executed by the thread
void* doSomething(void *arg) {
    for(int i=0;i<1000;i++){
        printf("Hello");
    }
    for (unsigned long i = 0; i < 1000000; i++);
    printf("Thread %ld has finished executing.\n", (long)arg);
    return NULL;
}

int main(void) {
    pthread_t tid[2];
    int err;
    struct timespec start, end;
    double time_taken;

    // Start the clock
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < 2; i++) {
        err = pthread_create(&tid[i], NULL, &doSomething, (void*)(long)i);
        if (err != 0)
            printf("Can't create thread :[%s]\n", strerror(err));
        else
            printf("Thread %d created successfully.\n", i);
    }

    // Wait for threads to finish executing
    for (int i = 0; i < 2; i++) {
        pthread_join(tid[i], NULL);
    }

    // Stop the clock
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate the time taken in seconds
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    printf("Total time taken to create and run threads: %.9f seconds\n", time_taken);

    return 0;
}
