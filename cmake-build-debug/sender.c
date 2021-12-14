#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <bits/types/FILE.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/tcp.h>
#include <stdlib.h>

int sock;
int conn;
FILE *fp;
char buf[256];
char *filename = "1gb.txt";
socklen_t len;
int totalBytes = 0;
struct sockaddr_in server;

void send_file(FILE *fp, int sock) {
    char data[256] = {0};

    while (fgets(data, 256, fp) != NULL) {
        if (send(sock, data, sizeof(data), 0) == -1) {
            perror("error in sending");
            exit(1);
        }
        bzero(data, 256);
    }
}


int main(int argc, char **argv) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
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
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("reading file");
        exit(1);
    }

    for (int i = 0; i < 5; ++i) {
        send_file(fp, sock);
    }
    printf("first send successful");

    len = sizeof(buf);

    //cubic
    if (getsockopt(sock, IPPROTO_IP, TCP_CONGESTION, buf, &len) != 0) {
        perror("getsockopt");
        return -1;
    }
    puts(buf);
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
        totalBytes += send(sock, fgets(buf, 256, fp), 256, 0);
    }

    len = sizeof(buf);
    if (getsockopt(sock, IPPROTO_IP, TCP_CONGESTION, buf, &len) != 0) {
        perror("getsockopt");
        return -1;
    }
    printf("New: %s\n", buf);
    close(sock);
    return 0;
}

