#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>

#define Backlog 5

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
    

    int serverSocket;
    struct sockaddr_un serverSocketAddress;
    int fLen;

    int clientSocket;
    struct sockaddr_un clientSocketAddress;

    serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);

    strcpy(serverSocketAddress.sun_path, "sockets");
    serverSocketAddress.sun_family = AF_UNIX;


    if (bind(serverSocket, (struct sockaddr*)&serverSocketAddress, strlen(serverSocketAddress.sun_path) + sizeof(serverSocketAddress.sun_family)) < 0) {
        perror("Bind Error");
        exit(1);
    }


    listen(serverSocket, Backlog);

    if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientSocketAddress, &fLen)) < 0 ){
        perror("Accept Error");
        exit(1);
    }

    FILE *socketPointer = fdopen(clientSocket, "r");
    
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    int id = 0;
    while(id < 50){
        for(int j = id; j <= id + 4; j++){
            write(clientSocket, randomStringArrays[j], strlen(randomStringArrays[j]));
        }
        char returnedIndex[5];
        int j = 0; 

        read(clientSocket, returnedIndex, 5);
        id = atoi(returnedIndex);
        if(id != 0){
        printf("Number recevied from host is %d\n", id);
        id = id + 1;}
    }
    close(serverSocket);

    clock_gettime(CLOCK_REALTIME, &end);

    double timeTaken = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) /1000000000.0;

    printf("Time taken = %lf ", timeTaken);

}