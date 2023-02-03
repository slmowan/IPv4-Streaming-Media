#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * 打印时间
*/

int main() {

    // 如果不加fflush将这个输出重定向到文件中的话，begin不会被输出
    // begin还没来得及输出execl就replace了旧的进程映像了
    puts("Begin"); 

    fflush(NULL); // !!!

    execl("/usr/bin/date", "date", "+%s", NULL); // argv[0] = date, argv[1] = "+%s"
    
    perror("execl()"); // 这里不用设置参数判断返回值的原因是：execl成功的话就不会再回到这个进程了，他会去一个新的进程
    exit(1);

    puts("End!"); // 替换之后这个end不会打印出来，因为进程映像已经被替换了

    exit(0);
}