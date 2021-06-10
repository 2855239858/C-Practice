#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <stdio.h>

int main() {
    std::string file_name = "./IO_test.txt";

    // 打开方式有：O_RDONLY, O_WRONLY, O_RDWR
    // O_CREAT, O_EXCL, O_NOCTTY, O_TRUNC, O_APPEND
    int fd = open(&file_name[0], O_RDWR|O_CREAT|O_APPEND);
    if (fd == -1) {
        printf("Open file: %s fail with code %d.\n", file_name, fd);
        return -1;
    } else {
        printf("Open success!\n");
    }

    char *words = "This is the test word to test the codes.\n";
    int res = write(fd, words, 40);
    if (res == -1) {
        printf("Write words failed.\n");
        return -1;
    } else {
        printf("Write success.\n");
    }

    res = lseek(fd, 0, SEEK_SET);
    if (res == -1) {
        printf("Move pointer to head failed.\n");
    } else {
        printf("Move success.\n");
    }

    char ans[100];
    res = read(fd, ans, sizeof(ans));
    if (res == -1) {
        printf("Fail to read file.\n");
    } else if (res == 0) {
        printf("Read all of the file.\n");
    } else {
        printf("Read %d.\n", res);
    }

    for (int i = 0; ans[i] != '\0'; i++) {
        printf("%c", ans[i]);
    }
    printf("\n");

    res = close(fd);
    if (res == -1) {
        printf("Close file failed.\n");
    } else {
        printf("Close success.\n");
    }

    return 0;
}




//Linux中的文件类型有：普通文件，目录文件，链接文件和设备文件
//IO操作作用使用函数：open(), close(), read(), write()和Iseek()
//pread()和pwrite类似与lseek+read和lseek+write，但是这两步是原子操作