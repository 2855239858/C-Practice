#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

#pragma message("ENV_TEST")

// getenv(const char*)获取一个环境变量，不存在返回-1
char* get_env(const char* name) {
    return getenv(name); 
}

// setenv(char* name, char* value, int)
// 设置环境变量，name为环境变量名，value环境变量值，int  1/0 （覆盖/不覆盖 原环境变量）
int set_env(const char* name, const char* value, int override) {
    return setenv(name, value, override);
}

// unsetenv(char* name)
// 删除环境变量，name不存在的时候返回0（成功）
int unset_env(const char* name, const char* value, int ovrride) {
    return unsetenv(name);
}

// fork() 创建子进程
// 两次返回，父进程返回子进程id，子进程返回0
int create_child_thread() {
    return fork();
}
////补充知识：fork()时遵循 （读时共享，写时复制） 的原则


// pid_t getpid()与getppid()
// getpid获取当前进程id，获取当前进程的父进程id
void print_pid() {
    printf("This process's pid is %d, father's pid is %d \n", getpid(), getppid());
}
// 补充：init是有所进程的祖先进程

// uid_t getuid(void) 获取当前进程实际用户ID
// uid_t geteuid(void) 获取当前进程有效组用户ID
void print_u_and_eu_id() {
    printf("User id is %d\n", getuid());
    printf("Effective user id is %d\n", geteuid());
}

// gid_t getgid(void) 获取当前进程使用用户组ID
// gid_t getegid(void) 获取当前进程有效用户组ID
void print_u_and_eg_id() {
    printf("Group id is %d\n", getgid());
    printf("Effective group id is %d\n", getegid());
}

int main() {
    printf("Env is [%s]\n", get_env("HOME"));
    printf("Thread begin.\n");
    create_child_thread();
    print_pid();
    print_u_and_eu_id();
    print_u_and_eg_id();

    return 0;
}