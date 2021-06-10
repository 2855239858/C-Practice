//这是一个简单的socket client实例
//client发送消息给服务器

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> //unix标准中通用头文件，包含open，fclose等
#include <sys/shm.h> //共享内存的一些函数

#define MYPORT  7000
#define BUFFER_SIZE 1024

int main() {
    //定义socket
    int sock_client = socket(AF_INET, SOCK_STREAM, 0);

    //定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //连接服务器
    int res = connect(sock_client, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if (res < 0) {
        perror("Connect failed: ");
        exit(1);
    }

    char send_buf[BUFFER_SIZE];
    char rec_buf[BUFFER_SIZE];
    while (fgets(send_buf, sizeof(send_buf), stdin) != NULL) {
        send(sock_client, send_buf, strlen(send_buf), 0);  //发送
        if (strcmp(send_buf, "exit\n") == 0) {
            break;
        }
        recv(sock_client, rec_buf, sizeof(rec_buf), 0);
        fputs(rec_buf, stdout);

        memset(&send_buf, 0, sizeof(send_buf));
        memset(&rec_buf, 0, sizeof(rec_buf));
    }
    close(sock_client);
    return 0;
}