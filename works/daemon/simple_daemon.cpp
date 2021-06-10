#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>  //定义文件状态所在的伪标准头文件
// stdio 与 stdlib，定位在通用工具函数
// stdio 是标准输入和输出头文件，定位在标准的输入输出工具
// stdlib 是标准库头文件
// 1、stdlib.h主要封装了malloc()、calloc()、realloc()、free()、system()、atoi()、atol()、rand()、srand()、exit()等函数。
// 2、stdio.h主要封装了getchar()、putchar()、scanf()、printf()、gets()、puts()、sprintf()等函数。
#include <stdio.h>
#include <stdlib.h>

void init_daemon() {
    int pid;
    // exit(0):正常退出
    // exit(1):异常退出
    // _exit():直接终止程序运行，不检查文件和缓冲区的状态
    // fork()：从当前进程产生一个新的进程，新进程与当前进程属于一个进程组
    if (pid = fork()) exit(0);
    else if (pid < 0) exit(1);

    // 子进程继续运行
    // setsid():创建新的会话组，子进程成为组长并与控制终端分离
    setsid();

    // 防止子进程获取控制终端
    if (pid = fork()) exit(0);
    else if (pid < 0) exit(1);

    // // 关闭打开的文件描述符，避免资源浪费
    // for (int i = 0; i < NOFILE; i++) {
    //     close(i);
    // }

    // 守护进程需要保持在一个永久存在的目录下
    // 因此可以设为home目录，日志输出可以设为/tmp目录
    chdir("/tmp");

    // 设置子进程的文件权限掩码
    // 因为子进程会继承父进程的文件权限掩码，可能带来潜在的不便与危险
    umask(0);

}

int main() {
    FILE *fd;

    // 忽略子进程结束信号，防止出现僵死进程
    signal(SIGCHLD, SIG_IGN);

    init_daemon();

    while (1) {
        sleep(30);
        if ((fd = fopen("test.log", "a")) != NULL) {
            fprintf(fd, "%s\n", "test message");
            fclose(fd);
        }
    }

    return 0;
}