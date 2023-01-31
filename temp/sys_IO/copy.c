#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char** argv) {

    int src_fd, dest_fd;
    char buf[BUFSIZE];
    int len,ret,pos;

    if(argc<3) {
        fprintf(stderr, "Usage....\n");
        exit(1);
    }

    src_fd = open(argv[1],O_RDONLY);
    if(src_fd<0) {
        perror("open()");
        exit(1);
    }

    dest_fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC,0600); //目标文件不一定非得存在，所以mode填写的是write only，如果不存在则创建，存在则截断
    //如果mode中含有O_CREAT的话就一定要用open的第二个函数，在最后要随便给一个权限。

    if(dest_fd<0) {
        close(src_fd);  //如果写文件创建失败退出前记得回收读文件，防止内存泄漏
        perror("open()");
        exit(1);
    }

    while(1) {
        len = read(src_fd,buf,BUFSIZE); //第三个参数表示最多读BUFSIZE个大小, 返回真正的字节数
        if(len < 0 ) {
            perror("read()");
            break; //跳出当前while循环然后指向close file操作
        }
        if(len == 0) { //表示达到文件末尾
            break; 
        }
        pos = 0;
        while(len > 0) {
                ret = write(dest_fd,buf+pos,len); //从buf写到dest_fd
            if(ret<0) {
                perror("write()");
                exit(1); //这里就不能用break，因为break只能跳出内层while循环但是还在外层while循环当中
            }
            //需要判断len个字节是否全部被写进去，如果只写了部分字节那么也不会报错，但是最后的结果就是不对的
            pos += ret;
            len -= ret;
        }
        ret = write(dest_fd,buf,len); //从buf写到dest_fd
        if(ret<0) {
            perror("write()");
            break;
        }

    }

    close(dest_fd);
    close(src_fd);

}