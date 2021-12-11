//
// Created by Oriho on 10/12/2021.
// AWESOME

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <bits/types/FILE.h>
#include <unistd.h>


struct sockaddr_in server, client;


int createSocket(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    return sock;
}

int createConnection(void) {
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8000);
    int conn = connect(createSocket(), (const struct sockaddr *) &server, sizeof(server));
    return conn;
}

void sendMessage() {
    int conn = createConnection();
    for (int i = 0; i < 5; ++i) {
        send(createSocket(),"1gb.txt",1024,0);
    }
}

void closeSocket() {
    int cls = close(createSocket());
}
