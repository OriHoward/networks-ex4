//
// Created by Oriho on 10/12/2021.
//

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>

int sock;
int bnd;
int lstn;
int accpt;
FILE *fp;
int numOfBytes;
socklen_t len;
struct sockaddr_in server;

int main(int argc, char **argv) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return -1;
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
    bnd = bind(sock, (struct sockaddr *) &server, sizeof(server));
    if (bnd == -1) {
        perror("bind");
        return -1;
    }
    lstn = listen(sock, 10);
    if (lstn == -1) {
        perror("listen");
        return -1;
    }
    accpt = accept(sock, (struct sockaddr *) &server, &len);
    if (accpt == -1) {
        perror("accept");
        return -1;
    }
    fp = fopen("1gb.txt", "r");
    do {
        numOfBytes = recv(sock, fp, 256, 0);
        if (numOfBytes == -1) {
            perror("recv");
            return -1;
        }
    } while (numOfBytes != 0);
    // need to measure times
    do {
        numOfBytes = recv(sock, fp, 256, 0);
        if (numOfBytes == -1) {
            perror("recv");
            return -1;
        }
    } while (numOfBytes != 0);
    return 0;
}
