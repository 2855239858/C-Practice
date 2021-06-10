#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MYPORT 8887

int main() {
    int server_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (server_sock < 0) {
        perror("Create socket failed: ");
        exit(1);
    }

    struct sockaddr_in serve_addr;
    memset(&serve_addr, 0, sizeof(serve_addr));
    serve_addr.sin_family = AF_INET;
    serve_addr.sin_port = htons(MYPORT);
    serve_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(server_sock, (struct sockaddr *) &serve_addr, sizeof(serve_addr));
    if (ret < 0) {
        perror("Bind failed: ");
        exit(1);
    }

    char rec_buffer[1024];
    struct sockaddr_in peer_addr;
    socklen_t peer_len;
    while (1) {
        peer_len = sizeof(peer_addr);
        memset(&rec_buffer, 0, sizeof(rec_buffer));
        ret = recvfrom(server_sock, rec_buffer, sizeof(rec_buffer), 0, (struct sockaddr *) &peer_addr, &peer_len);
        if (ret <= 0) {
            perror("Receive message from server failed: ");
            continue;
        } 
        if (strcmp(rec_buffer, "exit\n") == 0) break;
        printf("%s", rec_buffer);
        sendto(server_sock, rec_buffer, ret, 0, (struct sockaddr *) &peer_addr, peer_len);
    }
    close(server_sock);
    return 0;
}