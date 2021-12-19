#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
int sock;
int bnd;
int lstn;
int accpt;
char buf[1048576] = {0};
FILE *fp;
int numOfBytes = 1;
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


    struct timeval tval_before, tval_after, tval_result;
    
    
    
    long int seconds = 0.0;
    long int milliseconds = 0.0;
    for (int i = 0; i < 5; ++i) {
        gettimeofday(&tval_before,NULL);
        recv(accpt, buf, 1048576, 0);
        gettimeofday(&tval_after,NULL);
        timersub(&tval_after,&tval_before,&tval_result);
        printf("#%d cubic: %ld.%06ld\n",i,(long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
        seconds += (long int)tval_result.tv_sec;
        milliseconds += (long int)tval_result.tv_usec;
    }
    printf("total sum: %ld.%06ld\n", seconds,milliseconds);
    printf("average sum: %ld.%06ld\n", seconds/5,milliseconds/5);

    seconds = 0.0;
    milliseconds = 0.0;
    for (int i = 0; i < 5; ++i) {
    gettimeofday(&tval_before,NULL);
        recv(accpt, buf, 1048576, 0);
        gettimeofday(&tval_after,NULL);
        timersub(&tval_after,&tval_before,&tval_result);
        printf("#%d reno: %ld.%06ld\n",i,(long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
        seconds += (long int)tval_result.tv_sec;
        milliseconds += (long int)tval_result.tv_usec;
    }
    printf("total sum: %ld.%06ld\n", seconds,milliseconds);
    printf("average sum: %ld.%06ld\n", seconds/5,milliseconds/5);
    
    
    return 0;
}
