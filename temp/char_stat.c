// 该功能统计一个文件中的有效字符个数, 在终端使用 ls -l也可以看到文件中的有效字符个数
// ./char_stat <filename>
// P8
// 涉及到的知识点：文件IO

# include <stdio.h>

int main(int argc, char*argv[]) {
    if(argc<2) {
        printf("Usage: %s <src_fole> <dest_file>\n", argv[0]);
    }

    int count = 0;
    FILE* src_file = fopen(argv[1], "r");

    if(src_file==NULL) {
        perror("fopen(): ");
        return 1;
    }

    while(fgetc(src_file) != EOF) {
        count++;
    }

    printf("Effective character count of file %s is: %d\n", argv[1], count);

    fclose(src_file);
    return 0;
}