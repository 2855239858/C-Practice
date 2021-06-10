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

//（1）创建socket（2）bind（）（3）listen（）（4）accept（）

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

    char buffer[1024];
    while (1) {
        memset(buffer, 0, sizeof(buffer));

        //read()
        //recv():
        int len = recv(conn, buffer, sizeof(buffer), 0);
        //strcmp:str1 < str2 return <0
        //       str1 == str2 return 0
        //       str1 > str2 return >0
        if (strcmp(buffer, "exit\n") == 0) break;
        printf("buffer is: %s\n", buffer);

        //send()
        send(conn, buffer, len, 0);
    }
    close(conn);
    close(ss);
    return 0;
}




// socket编程中需要用到的头文件
// sys/types.h：数据类型定义
// sys/socket.h：提供socket函数及数据结构
// netinet/in.h：定义数据结构sockaddr_in
// arpa/inet.h：提供IP地址转换函数
// netdb.h：提供设置及获取域名的函数
// sys/ioctl.h：提供对I/O控制的函数
// sys/poll.h：提供socket等待测试机制的函数
 
// 其他在网络程序中常见的头文件
// unistd.h：提供通用的文件、目录、程序及进程操作的函数
// errno.h：提供错误号errno的定义，用于错误处理
// fcntl.h：提供对文件控制的函数
// time.h：提供有关时间的函数
// crypt.h：提供使用DES加密算法的加密函数
// pwd.h：提供对/etc/passwd文件访问的函数
// shadow.h：提供对/etc/shadow文件访问的函数
// pthread.h：提供多线程操作的函数
// signal.h：提供对信号操作的函数
// sys/wait.h、sys/ipc.h、sys/shm.h：提供进程等待、进程间通讯（IPC）及共享内存的函数
 
// 建议： 在编写网络程序时，可以直接使用下面这段头文件代码
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netdb.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include <errno.h>
// #include <malloc.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <sys/ioctl.h>
// #include <stdarg.h>
// #include <fcntl.h>
// #include <fcntl.h>
 
 
// 涉及到用户权限及密码验证问题时加入如下语句：
// #include <shadow.h>
// #include <crypt.h>
// #include <pwd.h>
// 需要注意的是，应该在编译时链接加密算法库，即增加编译选项：
// -lcrypt
// 　 
 
// 涉及到文件及时间操作加入如下语句：
// #include <sys/time.h>
// #include <utime.h>
// #include <time.h>
// #include <sys/stat.h>
// #include <sys/file.h>
 
 
// 涉及到多进程操作时加入如下语句：
// #include <sys/wait.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <signal.h>
 
 
// 涉及到多线程操作时加入如下语句：
// #include <pthread.h>
// #include <sys/poll.h>
// 需要注意的是，应该在编译时链接线程库，即增加编译选项：
// -lthread