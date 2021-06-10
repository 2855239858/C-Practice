#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MYPORT 8887
char *SERVEIP = "127.0.0.1";

int main() {
    int client_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (client_sock < 0) {
        perror("Create socket failed: ");
        exit(1);
    }

    struct sockaddr_in serve_addr;
    memset(&serve_addr, 0, sizeof(serve_addr));
    serve_addr.sin_family = AF_INET;
    serve_addr.sin_port = htons(MYPORT);
    serve_addr.sin_addr.s_addr = inet_addr(SERVEIP);

    int ret;
    char rec_buffer[1024];
    char send_buffer[1024];

    while (1) {
        memset(&send_buffer, 0, sizeof(send_buffer));
        fgets(send_buffer, sizeof(send_buffer), stdin);
        sendto(client_sock, send_buffer, sizeof(send_buffer), 0, (struct sockaddr *) &serve_addr, sizeof(serve_addr));
        if (strcmp(send_buffer, "exit\n") == 0) break;

        memset(&rec_buffer, 0, sizeof(rec_buffer));
        ret = recvfrom(client_sock, rec_buffer, sizeof(rec_buffer), 0, NULL, NULL);
        if (ret == -1) {
            perror("Receive message from server failed: ");
            continue;
        } 
        if (strcmp(rec_buffer, "exit\n") == 0) break;
        printf("%s", rec_buffer);
    }
    close(client_sock);
    return 0;
}