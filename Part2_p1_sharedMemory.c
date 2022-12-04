#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
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

    int SharedfileDescriptor;
    int id = 0;
    while(id < 50){
        SharedfileDescriptor = shm_open("NalishMemory", O_CREAT | O_RDWR, 0600);
        ftruncate(SharedfileDescriptor, sizeof(char)*5*17);
        char* sharedData = (char*) mmap(0, sizeof(char)*5*17, PROT_READ|PROT_WRITE, MAP_SHARED, SharedfileDescriptor, 0);
        int counter = 0;
        sharedData[counter] = ')';
        counter++;
        for(int j = id; j <= id + 4; j++){
            for(int j1 = 0; j1 < strlen(randomStringArrays[j]); j1++){
                sharedData[counter] = randomStringArrays[j][j1];
                counter++;
            }
            sharedData[counter] = '\n';
            counter++;
        }
        sharedData[counter] = '(';
        counter++;

        munmap(sharedData,sizeof(char)*5*17);
        close(SharedfileDescriptor);

        SharedfileDescriptor = shm_open("NalishMemory", O_RDONLY, 0666);
    
        int* data = (int*) mmap(0, sizeof(int), PROT_READ, MAP_SHARED, SharedfileDescriptor, 0);

        while(data[0] > 50){
            int* data = (int*) mmap(0, sizeof(int), PROT_READ, MAP_SHARED, SharedfileDescriptor, 0);
        }

        id = data[0];
        printf("Number recevied from host is %d\n", id);
              id = id + 1;
        munmap(data, sizeof(int));
        close(SharedfileDescriptor);
    }
    
    clock_gettime(CLOCK_REALTIME, &end);

    double timeTaken = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) /1000000000.0;

    printf("Time taken = %lf ", timeTaken);


}