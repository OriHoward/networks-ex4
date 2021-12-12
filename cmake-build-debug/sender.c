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
FILE *fp;
char buf[1024];
socklen_t len;
int totalBytes = 0;
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
    conn = connect(sock, (struct sockaddr *) &server, sizeof(server));
    if (conn == -1) {
        perror("connect");
        return -1;
    }

//    send file
    fp = fopen("SampleTextFile_20kb.txt", "r");
    for (int i = 0; i < 5; ++i) {
        totalBytes += send(sock, fp, 1024, 0);
    }

    len = sizeof(buf);

    //cubic
    if (getsockopt(sock, IPPROTO_IP, TCP_CONGESTION, buf, &len) != 0) {
        perror("getsockopt");
        return -1;
    }

    printf("Current: %s\n", buf);

    //reno
    strcpy(buf, "reno");
    len = strlen(buf);
    if (setsockopt(sock, IPPROTO_IP, TCP_CONGESTION, buf, len) != 0) {
        perror("setsockopt");
        return -1;
    }

    //send file
    for (int i = 0; i < 5; ++i) {
        totalBytes += send(sock, fp, 1024, 0);
    }
    printf("%d",totalBytes);

    len = sizeof(buf);
    if (getsockopt(sock, IPPROTO_IP, TCP_CONGESTION, buf, &len) != 0) {
        perror("getsockopt");
        return -1;
    }
    printf("New: %s\n", buf);
    close(sock);
    return 0;
}

