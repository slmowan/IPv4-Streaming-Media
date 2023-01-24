// 这个方法使用fseek()和ftell()函数统计一个文件中的有效字节，但是该文件不能超过2G的大小
// ./char_stat_byseek <src_file>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if(argc<2) {
        fprintf(stderr,"Usage: %s <src_fole> <dest_file>\n", argv[0]);
    }

    FILE *fp = fopen(argv[1], "r");

    if(fp==NULL) {
        perror("open()");
        exit(1);
    }

    //使用fseek()将给定流定位到文件末尾的位置
    int success = fseek(fp, 0, SEEK_END);
    if(success==-1) {
        perror("fseek()");
        exit(1);
    }

    //fseek成功，使用ftell()报告此时流当前所在的位置，即文件的大小
    long size = ftell(fp);
    if(size==-1) {
        perror("ftell()");
        exit(1);
    }


    fprintf(stdout, "The file size of %s is %ld\n", argv[1], size);
    fclose(fp); //close the file
    exit(0); //success
}

