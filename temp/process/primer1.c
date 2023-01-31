#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200

// fork实例2: 在界限中筛选质数, 使用201子进程完成该任务, 父进程执行i++

int main() {

    int i,j, mark;
    pid_t pid;

    for(i=LEFT; i<=RIGHT; i++) {

        pid = fork(); // 父进程产生了一个i，create a child process然后把这个i交给他
        if(pid<0) {
            perror("Fail to fork");
            exit(1);
        }

        if(pid==0) { // child
            mark = 1;
            for(j=2; j<i/2; j++) {
                if(i % j ==0) {
                    mark = 0;
                    break;
                }
            }   
            if(mark) {
                printf("%d is a primer\n", i);
            }
            exit(0); // 让当前子进程干完活以后就赶紧结束，不然这个产生出来的子进程还会不停的fork
        } //child
    }

    exit(0);
}