#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define LEFT 30000000
#define RIGHT 30000200
#define N 3

// fork实例n: 在界限中筛选质数, 使用201子进程完成该任务, 父进程执行i++
// 使用wait回收资源
// 使用交叉分配法实现

int main() {

    int i,j,n,mark;
    pid_t pid;

    // 使用该循环来分配子进程
    for(n=0; n<N; n++) {
        // fork子进程，分配任务
        pid = fork();
        if(pid < 0) {
            perror("fork");
            // 这里需要一个wait, 如果第三个fork失败了，得把前面释放出去的两个fork wait回来
            exit(1);
        }
        if(pid == 0) {
            // 让子进程算现在待计算的任务
            for(i=LEFT+n; i<=RIGHT; i+=N) { //隔N个拿一个
                mark = 1;
                for(j=2; j<i/2; j++) {
                    if(i % j ==0) {
                        mark = 0;
                        break;
                    }
                }
                if(mark) {
                    printf("[%d] block is in charge of primer %d\n", n, i);
                }
            }
            exit(0);
        }

    }

    // 父进程fork出3个，所以他要负责收3个尸
    //int st; // 查看收尸回来的状态
    for(n=0; n<=N; n++) {
        //wait(&st);
         wait(NULL); //如果不需要状态就写NULL即可
    }

    exit(0);

}