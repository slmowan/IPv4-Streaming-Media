// this is a function who can copy source file to destination.
// command: ./copy srcfile destfile
// P8
// 涉及到的知识点：文件IO，防止内存泄漏
// 可以使用fprintf函数代替printf函数（属于同一函数族）, 可以指定输出流

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc<3) {
        // perror()? //不知道这里可不可以用perror这个函数，好像这里不能用这个函数，到时候看看
        // printf("Usage: %s <src_fole> <dest_file>\n", argv[0]);
        fprintf(stderr,"Usage: %s <src_fole> <dest_file>\n", argv[0]);
    }

    FILE* src_file;                                         // create a FILE object
    FILE *dest_file;
    int char_read;

    src_file = fopen(argv[1],"r");                          // open the sourve file in read mode only
    if(src_file==NULL) {
        perror("fopen() fail");                             // print a system error message
        exit(1);
    }

    dest_file = fwrite(argv[2],"w");
    if(dest_file==NULL) {
        fclose(src_file);                                   // prevent memory leakage (以后可以用钩子函数优化)
        perror("fopen() fail");
        exit(1);
    }

    // read one, write one, each time, read one char
    while(1) {
        char_read = fgetc(src_file);
        if(char_read == EOF){
            break;
        }
        fputc(char_read,dest_file);
    }

    fclose(dest_file);
    fclose(src_file);

    exit(0);

}
