#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdio.h> // standard input and output library
#include <stdlib.h> // this includes functions regarding memory allocation
#include <string.h> // contains string functions
#include <errno.h> //It defines macros for reporting and retrieving error conditions through error codes
#include <time.h> //contains various functions for manipulating date and time
#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h>  // for socket creation
#include <netinet/in.h>  //contains constants and structures needed for internet domain addresses

using namespace std;
#define PORT 5000

void *server(void *arg){
    int listen_socket = -1;
    int connec_socket = -1;
    int n = 0;
    struct sockaddr_in eNB_addr;

    char sent_buffer[1024], received_buffer[1024];
    string msg;

    memset(received_buffer, 0, sizeof(received_buffer));
    memset(sent_buffer, 0, sizeof(sent_buffer));
    memset(&eNB_addr, 0, sizeof(eNB_addr));

    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    eNB_addr.sin_family = AF_INET;
    eNB_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    eNB_addr.sin_port = htons(PORT);

    bind(listen_socket, (struct sockaddr*) &eNB_addr, sizeof(eNB_addr));
    listen(listen_socket, 10);
    // Accept the request and return a new socket
    connec_socket = accept(listen_socket, (struct sockaddr*)NULL, NULL);
    
    // Listen
    read(connec_socket, received_buffer, sizeof(received_buffer) - 1);
    cout << "receive packet:" << received_buffer << endl;

    // Send the RRC connection setup
    msg = "RRC Connection Setup";
    strcpy(sent_buffer, &msg[0]);
    send(connec_socket, sent_buffer, sizeof(sent_buffer) - 1, 0);
    cout << "Send RRC Connection Setup" << endl;

    // Finally, 
    read(connec_socket, received_buffer, sizeof(received_buffer) - 1);
    cout << "receive packet:" << received_buffer << endl;

    // Close
    close(connec_socket);
    close(listen_socket);

    pthread_exit(NULL);
}

void *client(void *arg){
    // Declare parameters
    int com_socket = -1;
    struct sockaddr_in eNB_addr;

    char sent_buffer[1024], received_buffer[1024];
    string msg;
    // strcpy(sent_buffer, &msg[0]);

    memset(received_buffer, 0, sizeof(received_buffer));
    memset(sent_buffer, 0, sizeof(sent_buffer));
    memset(&eNB_addr, 0, sizeof(eNB_addr));

    com_socket = socket(AF_INET, SOCK_STREAM, 0);
    eNB_addr.sin_family = AF_INET;
    eNB_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    eNB_addr.sin_port = htons(PORT);

    if(connect(com_socket, (struct sockaddr *)&eNB_addr, sizeof(eNB_addr))<0)
    {
        printf("Connection failed due to port and ip problems\n");
        pthread_exit(NULL);
    }
    
    // Send the RRC connection request
    msg = "RRC Connection ReQuest";
    strcpy(sent_buffer, &msg[0]);
    send(com_socket, sent_buffer, strlen(sent_buffer), 0);
    cout << "Send RRC Connection ReQuest" << endl;
    
    // After that wait for the RRC connection setup
    read(com_socket, received_buffer, sizeof(received_buffer) - 1);
    cout << "receive packet:" << received_buffer << endl;
    
    //Finally, 
    msg = "RRC Connection Setup Complete";
    strcpy(sent_buffer, &msg[0]);
    send(com_socket, sent_buffer, strlen(sent_buffer), 0);
    cout << "Send RRC Connection Setup Complete" << endl;

    // Close
    close(com_socket);

    pthread_exit(NULL);
}

int main(){
    pthread_t thread1;
    pthread_t thread2;
    int rc, n;
    void *p;
    
    pthread_create(&thread1, NULL, server, p);
    pthread_create(&thread2, NULL, client, p);

    pthread_exit(NULL);
}