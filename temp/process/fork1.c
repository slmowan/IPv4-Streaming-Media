#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * 产生父子进程，让父子进程做不同的事情
*/
int main() {

    pid_t pid;

    printf("[%d] Begin!\n", getpid()); // 这句话在fork之前，所以肯定是父进程负责打印

    fflush(NULL); // 在fork之前刷新所有打开的流, 重要

    pid = fork(); // create a child process

    if(pid < 0) { // <0 means error
        perror("Fail to fork");
        exit(1);
    }

    if(pid==0) { // 说明是child进程
        printf("[%d]: Child is working\n", getpid());

    }else{ // 说明是parent
        printf("[%d]: Parent is working\n", getpid());
    }

    printf("[%d] End!\n", getpid());

    exit(0);
}