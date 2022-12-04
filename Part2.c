#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include<unistd.h>
#include <time.h>
#include <sched.h>

#define BILLION  1000000000.0

void child(char c, FILE *file) {

    double processTime;
    if(c == 'A'){
    int rc = fork();
    struct timespec start, end;
    struct sched_param paramA;
    paramA.sched_priority = 0;
    sched_setscheduler(getpid(), SCHED_OTHER, &paramA);

    clock_gettime(CLOCK_REALTIME, &start);
    if (rc == 0) {
        execl("/bin/sh","sh","/home/SecretProject/bashscript.sh",NULL);
    }
    else if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);    
    } 
    else {
        wait(NULL);
        clock_gettime(CLOCK_REALTIME, &end);
        processTime = (end.tv_sec - start.tv_sec)  + (end.tv_nsec - start.tv_nsec) / BILLION;
        printf("A-processTime %lf \n", processTime);
        fprintf(file,"%s", "A-processTime ");
        fprintf(file, "%lf\n", processTime);
    }
    }
    if(c == 'B'){
    int rc = fork();
    struct sched_param paramB;
    paramB.sched_priority = 1;
    sched_setscheduler(getpid(), SCHED_FIFO, &paramB);
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    if (rc == 0) {
        execl("/bin/sh","sh","/home/SecretProject/bashscript2.sh",NULL);
    } 
    else if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);    
    } 
    else {
        wait(NULL);
        clock_gettime(CLOCK_REALTIME, &end);
        processTime = (end.tv_sec - start.tv_sec)  + (end.tv_nsec - start.tv_nsec) / BILLION;
        printf("B-processTime %lf \n", processTime);
        fprintf(file,"%s", "B-processTime ");
        fprintf(file, "%lf\n", processTime);
    }       
    }
    if(c == 'C'){
    int rc = fork();

    struct timespec start, end;

    struct sched_param paramC;
    paramC.sched_priority = 1;
    sched_setscheduler(getpid(), SCHED_RR, &paramC);

    clock_gettime(CLOCK_REALTIME, &start);
    if (rc == 0) {
        execl("/bin/sh","sh","/home/SecretProject/bashscript3.sh",NULL);
    }
    else if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);    
    } 
    else {
        wait(NULL);
        clock_gettime(CLOCK_REALTIME, &end);
        processTime = (end.tv_sec - start.tv_sec)  + (end.tv_nsec - start.tv_nsec) / BILLION;
        printf("C-processTime %lf \n", processTime);
        fprintf(file,"%s", "C-processTime ");
        fprintf(file, "%lf\n", processTime);
    }       
    }
}

int main(){

    FILE *fileOutput;
    fileOutput = fopen("/home/SecretProject/result.txt","w");


    int rc = fork();
    if (rc == 0) {
        child('A', fileOutput);
    } 
    else {
        int rc2 = fork();
        if (rc2 == 0) {
            child('B', fileOutput);
        } 
        else {
            int rc3 = fork();
            if (rc3 == 0) {
                child('C', fileOutput);
            }
            // wait(NULL);
        }
        // wait(NULL);
    }
    fclose(fileOutput);
}

    