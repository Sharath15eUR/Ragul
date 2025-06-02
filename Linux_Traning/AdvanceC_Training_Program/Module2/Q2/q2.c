#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int N;

void sigint_handler(int sig) {
    printf("\nSIGINT (Ctrl+C) caught. Ignoring...\n");
}

void* threadA_func(void* arg) {
    time_t start = time(NULL);

    int count = 0, num = 2, sum = 0;
    while (count < N) {
        int is_prime = 1;
        for (int i = 2; i*i <= num; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            sum += num;
            count++;
        }
        num++;
    }

    printf("Sum of first %d prime numbers is: %d\n", N, sum);
    printf("Thread A time: %ld seconds\n", time(NULL) - start);
    pthread_exit(NULL);
}

void* threadB_func(void* arg) {
    time_t start = time(NULL);

    int times = 0;
    while (times < 10) {
        printf("Thread 1 is running\n");
        sleep(2);
        times += 2;
    }

    printf("Thread B time: %ld seconds\n", time(NULL) - start);
    pthread_exit(NULL);
}

void* threadC_func(void* arg) {
    time_t start = time(NULL);

    int times = 0;
    while (times < 10) {
        printf("Thread 2 is running\n");
        sleep(3);
        times += 3;
    }

    printf("Thread C time: %ld seconds\n", time(NULL) - start);
    pthread_exit(NULL);
}

int main() {
    signal(SIGINT, sigint_handler);

    pthread_t threadA, threadB, threadC;

    printf("Enter the value of N: ");
    scanf("%d", &N);

    pthread_create(&threadA, NULL, threadA_func, NULL);
    pthread_create(&threadB, NULL, threadB_func, NULL);
    pthread_create(&threadC, NULL, threadC_func, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    printf("All threads completed.\n");
    return 0;
}
