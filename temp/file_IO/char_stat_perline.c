// 使用getline统计给定的source文件每行各有多少有效字符

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    FILE* fp = fopen(argv[1],"r");
    //一定要记得初始化，不然会出现seg fault
    char* linebuf = NULL;
    size_t linesize = 0;

    // getline(&linebuf, &linesize, fp);
    // printf("%ld\n", strlen(linebuf));

    while(1) {
        int success = getline(&linebuf, &linesize, fp);
        if(success<0) {
            break;
        }
        printf("%ld\n", strlen(linebuf));
        printf("%s\n", linebuf);
        //printf("%ld\n", linesize);
    }

    //getline函数会造成可控的内存泄漏 (非碎片泄漏)

    exit(0);
}