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
#include <unistd.h>
int sock;
int conn;
FILE *fp;
char buf[1048576];
char *filename = "mb.txt";
socklen_t len;
int totalBytes = 0;
struct sockaddr_in server;

void send_file() {
    char data[1048576] = {0};

    while (fgets(data, 1048576, fp) != NULL) {
        if (send(sock, data, sizeof(data), 0) == -1) {
            perror("error in sending");
            exit(1);
        }
        bzero(data, 1048576);
    }
}


int main(int argc, char **argv) {
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
    printf("sending first time:\n");
    for (int i = 0; i < 5; ++i) {
        send_file();
        printf("Successfully send the %d time!\n", i);
    }
    printf("first send successful\n");

    //changing to reno
    strcpy(buf, "reno");
    len = strlen(buf);
    if (setsockopt(sock, IPPROTO_IP, TCP_CONGESTION, buf, len) != 0) {
        perror("setsockopt");
        return -1;
    }
    printf("Changed to %s\n", buf);
    //new read of the file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("reading file");
        exit(1);
    }
    sleep(1);
    printf("Sending second time:\n");
    //send file second time
    for (int i = 0; i < 5; ++i) {
        send_file();
        printf("Successfully sent the file on the %d time!\n", i);
    }

    len = sizeof(buf);
    close(sock);
    return 0;
}
