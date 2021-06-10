//服务器接受消息并打印

#include <sys/types.h> //数据类型定义
#include <sys/socket.h> //提供socket函数基数据结构
#include <stdio.h> //定义了一些类型，宏，以及函数来执行各种输入和输出
#include <netinet/in.h>  //定义数据结构sockaddr_in
#include <arpa/inet.h>  //提供ip地址转换函数
#include <unistd.h> //通用目录，文件，程序及进程操作的函数
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <typeinfo>

#define PORT 7000
#define QUEUE 20
int conn;

int main() {
    //实例化socket对象：AF_INET为IPV4，SOCK_STREAM为tcp
    //0为协议，默认自动选择合适的协议
    int ss = socket(AF_INET, SOCK_STREAM, 0);
    //创建一个struct
    struct sockaddr_in server_sockaddr;
    //定义结构体参数
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind()
    int res = bind(ss, (struct sockaddr *) &server_sockaddr, sizeof(server_sockaddr));
    if (res == -1) {
        // perror:将上一个函数的错误输出到stderr，先输出参数中的string
        perror("Bind failed: ");
        exit(1);
    }

    //listen()
    res = listen(ss, QUEUE);
    if (res == -1) {
        perror("Listen failed: ");
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    //accept()
    conn = accept(ss, (struct sockaddr *) &client_addr, &length);
    if (conn < 0) {
        perror("Accept failed: ");
        exit(1);
    }

    //定义select相关的参数，来实现异步聊天
    fd_set rfds;
    struct timeval tv;
    int rec_val, max_fd;
    char rec_buffer[1024];
    char send_buffer[1024];
    while (1) {
        //由于每次select以后都会改变rfds的状态，监听对象有改变相应比特为会变成1
        //因此，每次select监听前，我们都要设置集合
        //清空可读文件描述符
        FD_ZERO(&rfds);
        //将标准输入的文件描述符加入到集合中
        //0：标准输入表述符，1：标准输出描述符，3：标准错误描述符号
        FD_SET(0, &rfds);    
        max_fd = 0;
        //把当前连接的描述符也加入到集合中
        FD_SET(conn, &rfds);
        //找出最大描述符
        if (max_fd < conn) {
            max_fd = conn;
        }
        //设置超时时间
        tv.tv_sec = 5;  //秒
        tv.tv_usec = 0;  //毫秒
        //等待聊天，处理
        //select参数依次为：
        //最大监听描述符个数+1，可读问价/可写文件/异常文件描述符集合
        //监听时长
        // rec_val = select(max_fd + 1, &rfds, NULL, NULL, &tv);
        rec_val = select(max_fd + 1, &rfds, NULL, NULL, 0);
        if (rec_val == -1) {
            perror("Select failed: ");
            break;
        } else if (rec_val == 0) {
            printf("No message from client, waiting...\n");
            continue;
        } else {
            //从客户端接收到消息
            if (FD_ISSET(conn, &rfds)) {
                memset(&rec_buffer, 0, sizeof(rec_buffer));
                int len = recv(conn, rec_buffer, sizeof(rec_buffer), 0);
                if (strcmp(rec_buffer, "exit\n") == 0) break;
                printf("%s", rec_buffer);
            }
            //当前终端输入信息
            if (FD_ISSET(0, &rfds)) {
                memset(&send_buffer, 0, sizeof(send_buffer));
                fgets(send_buffer, sizeof(send_buffer), stdin);
                send(conn, &send_buffer, sizeof(send_buffer), 0);
                if (strcmp(send_buffer, "exit\n") == 0) break;
            }
        }
    }
    close(conn);
    close(ss);
    return 0;
}