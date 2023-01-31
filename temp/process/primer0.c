#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200

// fork实例2: 在界限中筛选质数, 只有一个进程进行工作

int main() {

    int i,j, mark;

    for(i=LEFT; i<=RIGHT; i++) {
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
    }

    exit(0);
}