#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/*
 * 标题few表示fork，wait和exec的缩写，这三个函数搭建起了UNIX的框架
 * fork，wait和exec的结合操作：
 * 父进程打印begin然后产生一个子进程
 * 子进程马上去干活：子进程变成了需要的data
 * 父进程等着子进程给他收尸，收尸以后打印end结束
*/
int main() {

    pid_t pid;

    puts("Begin!"); // for understanding

    fflush(NULL);

    pid = fork();
    if(pid < 0) {
        perror("fork()");
        exit(1);
    }

    if(pid==0) {
        execl("/bin/date", "date", "+%s", NULL);
        perror("execl()");
        exit(1);
    }

    wait(NULL);

    puts("End!");

    exit(0);
}

