#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/*
 * 使用few模型实现sleep 100的功能
*/
int main() {

    // 首先知道sleep在哪里，使用which sleep命令

    pid_t pid;

    puts("Begin!"); // for understanding

    fflush(NULL);

    pid = fork();
    if(pid < 0) {
        perror("fork()");
        exit(1);
    }

    if(pid==0) {
        execl("/bin/sleep", "sleep", "100", NULL);
        perror("execl()");
        exit(1);
    }

    wait(NULL);

    puts("End!");

    exit(0);
}

