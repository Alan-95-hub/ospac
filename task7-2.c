#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int numb = 0;

void* mythread(void* dummy) {
    pthread_t thid;
    thid = pthread_self();
    numb++;
    printf("[thread %u] calculation result: %d\n", thid, numb);
    return NULL;
}

int main() {
    pthread_t main_thid, thid1, thid2;
    int result;
    result = pthread_create(&thid1, (pthread_attr_t*)NULL, mythread, NULL);
    if (result != 0) {
        printf("[error] on first thread create, fault code: %d\n", result);
        exit(-1);
    }
    printf("[thread %u] created\n", thid1);
    result = pthread_create(&thid2, (pthread_attr_t*)NULL, mythread, NULL);
    if (result != 0) {
        printf("[error] on second thread create, fault code: %d\n", result);
        exit(-1);
    }
    printf("[thread %u] created\n", thid2);
    main_thid = pthread_self();
    numb++;
    printf("[thread %u] calculation result: %d\n", main_thid, numb);
    pthread_join(thid1, (void**)NULL);
    pthread_join(thid2, (void**)NULL);
    return 0;
}