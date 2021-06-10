#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 成功，返回终止的子进程id；失败，返回-1，设置errno
// 子进程死亡原因
/// 正常死亡 WIFEXITED，若真，WEXITSTATUS获取退出状态
/// 非正常死亡 WIFSIGNALED，若真，WTERMSIG得到信号
/// 暂停 WIFSTOPPED，若真，WSTOPSIG获取使之暂停信号编号
///     WIFCONTINUED，若真，表示暂停后继续执行


// wait()
/// 作用：（1）阻塞等待（2）回收子进程资源（3）查看死亡原因

// pid_t wait(int *status)
void wait_test() {
    pid_t pid;
    int i;
    
    for (i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            printf("I am child, pid=%d, ppid=%d\n", getpid(), getppid());
            // sleep(5);
            break;
            // exit(i);
        }
    }
    if (i == 5) {
        sleep(5);
        for (i = 0; i < 5; i++) {
            int status;
            pid_t wpid = wait(&status);
            printf("Wait success, wpid=%d, pid=%d\n", wpid, getpid());
            if (WIFEXITED(status)) {
                printf("Child pid[%d] exit with %d\n", wpid, WEXITSTATUS(status));
            } else if(WIFSIGNALED(status)) {
                printf("Child pid[%d] killed by %d\n", wpid, WTERMSIG(status));
            }
        }
        while(1) {
            sleep(1);
        }
    }
}

// pid_t waitpid(pid_t pid, int *status, int options)
/// pid：（1）<-1组ID(pid的绝对值)（2）-1回收任意（3）0回收和调用进程组id相同的组内子进程
/// （4）>0回收指定的pid
/// options：（1）0与wait形同，也会阻塞（2）WNOHANG 如果没有子进程退出的，会立即返回
/// 返回值：（1）若设置WNOHANG，无子进程退出，返回0；有子进程退出，返回子进程pid
/// （2）失败：返回-1，设置errno
void waitpid_test() {
    pid_t pid;
    int i;
    
    for (i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            printf("I am child, pid=%d, ppid=%d\n", getpid(), getppid());
            break;
        }
    }
    if (i == 5) {
        sleep(5);
        for (i = 0; i < 5; i++) {
            int status;
            pid_t wpid = waitpid(-1, &status, 0);
            printf("Wait success, wpid=%d, pid=%d\n", wpid, getpid());
            if (WIFEXITED(status)) {
                printf("Child pid[%d] exit with %d\n", wpid, WEXITSTATUS(status));
            } else if(WIFSIGNALED(status)) {
                printf("Child pid[%d] killed by %d\n", wpid, WTERMSIG(status));
            }
        }
        while(1) {
            sleep(1);
        }
    }
}


// int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options)
/// glibc和POSIX的接口


int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("Arguement [%d]: %s\n", i, argv[i]);
    }

    // wait_test();
    waitpid_test();

    return 0;
}