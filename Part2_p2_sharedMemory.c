#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main(){
    int SharedfileDescriptor;
    int counter = 0;
    while(counter  < 10){
        SharedfileDescriptor = shm_open("NalishMemory", O_RDWR, 0600);

        char* sharedData = (char*) mmap(0, sizeof(char)*5*17, PROT_READ|PROT_WRITE, MAP_SHARED, SharedfileDescriptor, 0);
        while(sharedData[0] != ')'){
            char* sharedData = (char*) mmap(0, sizeof(char)*5*17, PROT_READ|PROT_WRITE, MAP_SHARED, SharedfileDescriptor, 0);
        }
        char Index[3];
        int counter1 = 1;
        while(sharedData[counter1] != '('){
            printf("%c", sharedData[counter1]);
            counter1++;
        }

      
     
      
        Index[0] = sharedData[counter1 -3];
        Index[1] = sharedData[counter1 -2];
        Index[2] = '\0';

        munmap(sharedData,sizeof(char)*5*17);
        close(SharedfileDescriptor);
        // printf("Index is %s \n", Index);
        SharedfileDescriptor = shm_open("NalishMemory", O_RDWR, 0600);
        ftruncate(SharedfileDescriptor, sizeof(int));
        int* data = (int*) mmap(0, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, SharedfileDescriptor, 0);
        int indexToBeReturned = atoi(Index);
        data[0] = indexToBeReturned;
        // printf("Index to be sent is %d\n", indexToBeReturned);
        munmap(sharedData,sizeof(int));
        close(SharedfileDescriptor);
        counter++;

    }
}