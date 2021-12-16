#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <time.h>


int sock;
int bnd;
int lstn;
int accpt;
char buf[256] = {0};
FILE *fp;
int numOfBytes;
socklen_t len;
struct sockaddr_in server;

int main(int argc, char **argv) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
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

    clock_t start, end;

    printf("time started#1 \n");
    start = clock();
    do {
        numOfBytes = recv(accpt, buf, 256, 0);
    } while (numOfBytes > 0);
    end = clock() - start;
    double first_loop = (double) (end) / CLOCKS_PER_SEC;
    printf("time finished#1\n");
    printf("first transfer time: %f \n", first_loop);
    start = clock();
    printf("time started#2\n");
    do {
        numOfBytes = recv(accpt, buf, 256, 0);
    } while (numOfBytes > 0);
    end = clock() - start;
    double second_loop = (double) (end) / CLOCKS_PER_SEC;
    printf("time finished#2\n");
    printf("second transfer time: %f",second_loop);
    return 0;
}