
//自己尝试实现getline函数
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// int getdelim(char** buf, int* n, int delim, FILE* stream);
// int getline(char** lineptr, int* n, FILE* stream);



// 返回一个文件一行的内容，将每一行的内容存在一个一个 char[]数组中
// 如果读到一行的末尾或无法读取则返回-1，成功读取的话就返回0
// 如果一行的字符超过了120个那就用realloc再申请空间
// reads an entire line from the stream
int my_getline(char** lineptr, int* n, FILE* stream) {
    static char line[30]; //为什么要放在static区域, 原数组
    char* ptr = NULL;
    //unsigned int len;

    //错误情况判断
    if(lineptr==NULL || n==NULL) {
        errno = EINVAL; //Invalid argument, fail
    }
    
    if(ferror(stream)!=0) {
        return -1; //fail, 出现文件读写错误, open close的时候出错
    }

    if(feof(stream)!=0) {
        return -1; //到达文件末尾
    }

    fgets(line,30,stream); //size最大为200,将stream写入line当中

    //写入一行后计算此时line的大小
    ptr = strchr(line,'\n'); //将文件指针定位到'\n'处
    if(ptr==NULL) { //如果没有这样的ptr存在的话,说明line的大小是够用的
        *n = 30;
        return (int)(*n); // success, exit(0)

    }
    //如果有这样的ptr存在的话,说明line已经快要满了，最后一个字符是'\n' （"abcd" with size=5需要读两次的例子）
    //*ptr = strchr(line,'\0'); // 将

    //realloc
    ptr = realloc(*lineptr,20); //ptr指向扩容后的数组
    if(ptr==NULL) { //没有开辟成功
        return -1; //储存失败
    }

    //成功，将原数组中的数据拷贝到新数组中并释放掉原数组
    strcpy(*lineptr,line);
}

// // free memory caused by getline function
// int getline_free(char **lineptr) {
//     return 0;
// }

int main(int argc, char* argv[]) {

    FILE* fp = fopen(argv[1],"r");
    //一定要记得初始化，不然会出现seg fault
    char* linebuf = NULL;
    int linesize = 0;

    // getline(&linebuf, &linesize, fp);
    // printf("%ld\n", strlen(linebuf));

    while(1) {
        int success = my_getline(&linebuf, &linesize, fp);
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