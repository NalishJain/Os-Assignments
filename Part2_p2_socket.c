#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(){
    int clientSocket;
    struct sockaddr_un clientSocketAddress;

    clientSocket = socket(AF_UNIX, SOCK_STREAM, 0);

    strcpy(clientSocketAddress.sun_path, "sockets");
    clientSocketAddress.sun_family = AF_UNIX;

    if (connect(clientSocket, (struct sockaddr*)&clientSocketAddress, strlen(clientSocketAddress.sun_path) + sizeof(clientSocketAddress.sun_family)) < 0) {
        perror("Error While Trying to Connect to Client");
        exit(1);
    }


    FILE *socketPointer = fdopen(clientSocket, "r");

    int counter = 0;


    while (counter < 10){ //10

        char buf[20];
        int maxIndex = 0;
        for(int j = 0; j < 5; j++){
            fgets(buf, 14, socketPointer);
            printf("%s", buf);
            fputs("\n", stdout);

            char returnedIndex[3];
            returnedIndex[0] = buf[strlen(buf) - 2];
            returnedIndex[1] = buf[strlen(buf) - 1];
            returnedIndex[2] = '\0';

            int intReturnedIndex = atoi(returnedIndex);

            if(intReturnedIndex > maxIndex){
                maxIndex = intReturnedIndex;
            }
        }

        counter++;
        char indexToBeSent[6];
        sprintf(indexToBeSent, "%d", maxIndex);
        write(clientSocket, indexToBeSent, 2);
    }
    close(clientSocket);
}