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
#include <stdio.h>
#include <netinet/tcp.h>

int sock;
int conn;
int totalBytes = 0;
struct sockaddr_in server;

void createSocket(void) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
}

void createConnection(void) {
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8000);
    conn = connect(sock, (const struct sockaddr *) &server, sizeof(server));
}


int sendMessage() {
    FILE *fp;
    fp = fopen("1gb.txt", "r");
    for (int i = 0; i < 5; ++i) {
        totalBytes += send(sock, fp, 1024, 0);
    }
    return totalBytes;
}

void closeSocket() {

}

//int main() {
//    createSocket();
//    createConnection();
//    int bytes = sendMessage();
//    return 0;
//}

int main(int argc, char **argv) {
    char buf[256];
    socklen_t len;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return -1;
    }

    len = sizeof(buf);
    if (getsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, &len) != 0) {
        perror("getsockopt");
        return -1;
    }

    printf("Current: %s\n", buf);


    strcpy(buf, "reno");
    len = strlen(buf);
    if (setsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, len) != 0) {
        perror("setsockopt");
        return -1;
    }
    len = sizeof(buf);
    if (getsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, &len) != 0) {
        perror("getsockopt");
        return -1;
    }
    printf("New: %s\n", buf);
    close(sock);
    return 0;
}

