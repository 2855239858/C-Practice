#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// int execlp(const char *file, const char *arg, ..., /* (char *) NULL */) 
// p=path，借助PATH环境变量加载程序
// file 需要加载的程序的名字
// arg 一般是程序名
// ... 参数名，可变参数
// 成功：无返回 失败：-1
int print_execlp_list() {
    return execlp("ls", "ls", "-a", "--color=auto", NULL);
}

// execl 与execlp类似，只是不能借助PATH，需要写程序的绝对路径
int print_execl_list() {
    return execl("/bin/ls", "ls", "-a", "--color=auto", NULL);
}

// 还有其他如：execp，execv，execle，execve
// 实际上所有exec*都是基于execve，只有execve是真正的系统调用
// l（list） 命令行参数列表
// p（path） 搜索file时使用path变量
// v（vector） 使用命令行参数数组
// e（environment） 使用环境变量数组，不使用进程原有的环境变量，设置新加载程序运行的环境变量


int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("argument [%d]: %s\n", i, argv[i]);
    }

    // print_execlp_list();
    // perror("Run execlp failed: ");
    print_execl_list();
    perror("Run execl failed: ");

    return 0;
}