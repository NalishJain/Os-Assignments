#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
    mkfifo("NalishOsFifo", 0666);
    int fifoDescripter;
    int counter = 0;
    while (counter < 10){ //10

    char buf[20];
    int maxIndex = 0;
    fifoDescripter = open("NalishOsFifo", O_RDONLY);
    for(int j = 0; j < 5; j++){
        read(fifoDescripter, buf, 13);
        // fputs(buf, stdout);
        printf("%s", buf);
        fputs("\n", stdout);

        char returnedIndex[3];
        returnedIndex[0] = buf[strlen(buf) - 3];
        returnedIndex[1] = buf[strlen(buf) - 2];
        returnedIndex[2] = '\0';

        int intReturnedIndex = atoi(returnedIndex);

        if(intReturnedIndex > maxIndex){
            maxIndex = intReturnedIndex;
        }
    }
    close(fifoDescripter);
    fifoDescripter = open("NalishOsFifo", O_WRONLY);
    counter++;
    char indexToBeSent[6];
    sprintf(indexToBeSent, "%d", maxIndex);
    write(fifoDescripter, indexToBeSent, 2);
    close(fifoDescripter);
    }
}