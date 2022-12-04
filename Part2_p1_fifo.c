#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

char* randomStringGenerator(int n){
    char AlphaNumeric[36] = {'a', 'b', 'c','d','e', 'f', 'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9'};
    int randomIndex;
    char *randomString = (char*)malloc(sizeof(char)*(n+2));
    for(int i = 0; i  < n; i++){
        randomIndex = rand()%36;
        randomString[i] = AlphaNumeric[randomIndex];
    }
    randomString[n] = '_'; 
    randomString[n + 1] = '\0';
    return randomString; 
}

int main(){
    char stringIndex[3];
    char** randomStringArrays = (char**)malloc(sizeof(char*)*50);
    for(int i = 0; i < 50; i++){ //11
        char *a = randomStringGenerator(10);
        sprintf(stringIndex, "%d", i);

        if(i < 10){
            strcat(a, "0\0");
            strcat(a,stringIndex);
        }
        else{
            strcat(a,stringIndex);
        }
        randomStringArrays[i] = (char*)malloc(sizeof(char)*15);
        randomStringArrays[i] = a;
        // printf("%s\n", a);
    }

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    mkfifo("NalishOsFifo", 0666);
    int fifoDescripter;
    int id = 0;
    while(id < 50){
        fifoDescripter = open("NalishOsFifo", O_WRONLY);
        for(int j = id; j <= id + 4; j++){
            write(fifoDescripter, randomStringArrays[j], strlen(randomStringArrays[j]));
        }
        close(fifoDescripter);
        fifoDescripter = open("NalishOsFifo", O_RDONLY);
        char returnedIndex[5];
        int j = 0; //
        read(fifoDescripter, returnedIndex, 5);
        id = atoi(returnedIndex); 
        printf("Number recevied from host is %d\n", id);
        close(fifoDescripter);
        id = id + 1;
      
    }

    clock_gettime(CLOCK_REALTIME, &end);

    double timeTaken = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) /1000000000.0;

    printf("Time taken = %lf ", timeTaken);
}