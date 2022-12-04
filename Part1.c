#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <sched.h>

#define BILLION  1000000000.0

typedef struct { double x; } Double;


void countA(){
    unsigned int count = 0;
    for(unsigned int i = 0; i < UINT_MAX; i++){
        count++;
    }
}

void countB(){
     unsigned int count = 0;
    for( unsigned int i = 0; i < UINT_MAX; i++){
        count++;
    }
}

void countC(){
     unsigned int count = 0;
    for( unsigned int i = 0; i < UINT_MAX; i++){
        count++;
    }
}

void* p1caller(void *f){
    struct sched_param paramA;
    paramA.sched_priority = 0;
    pthread_setschedparam(pthread_self(), SCHED_OTHER, &paramA);
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    countA();
    clock_gettime(CLOCK_REALTIME, &end);
    Double *ptr = malloc(sizeof(Double));
    ptr->x = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / BILLION;
    return (void*)ptr;
}

void* p2caller(void *f){
    struct sched_param paramB;
    paramB.sched_priority = 1;
    pthread_setschedparam(pthread_self(), SCHED_RR, &paramB);

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    countB();
    clock_gettime(CLOCK_REALTIME, &end);
    Double *ptr = malloc(sizeof(Double));
    ptr->x = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / BILLION;
    return (void*)ptr;
}

void* p3caller(void *f){
    struct sched_param paramC;
    paramC.sched_priority = 1;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &paramC);

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    countC();
    clock_gettime(CLOCK_REALTIME, &end);

    Double *ptr = malloc(sizeof(Double));
    ptr->x = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / BILLION;
    return (void*)ptr;
}

int main(){
    pthread_t ThreadA, ThreadB, ThreadC;
  



    Double *r1; 
    Double *r2;
    Double *r3;
    pthread_create(&ThreadA, NULL, &p1caller,NULL);
    pthread_create(&ThreadB, NULL, &p2caller, NULL);
    pthread_create(&ThreadC, NULL, &p3caller, NULL);

    
    
    
    pthread_join(ThreadA, (void **)&r1);
    pthread_join(ThreadB, (void **)&r2);
    pthread_join(ThreadC, (void **)&r3);

    printf("%lf %lf %lf",r1->x,r2->x,r3->x);



    // pthread_join(pid1, NULL);
}