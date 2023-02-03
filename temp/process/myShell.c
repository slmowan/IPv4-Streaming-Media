
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <glob.h>
#include <sys/wait.h>

#define DELIMS " \t\n"

// 实现一个简单的shell

struct cmd_st
{
    glob_t globres;
};


static void prompt() {
    printf("mysh-0.1$ ");
}

static void parse(char* line, struct cmd_st* res) {
    int i = 0;
    char *token;

    while(1) {
        token = strsep(&line, DELIMS);
        if(token == NULL) {
            break;
        }
        if(token[0] == '\0') { //空串，当多个delims连续时
            continue;
        }

        // i的作用：第一次不追加，后面的每一次都追加
        // 将i=0，第一次的话就是GLOB_NOCHECK | 0 = GLOB_NUCHECK
        glob(token, GLOB_NOCHECK|GLOB_APPEND*i, NULL, &res->globres);
        i = 1;
    }
}

int main() {

    char* linebuf = NULL;
    size_t linebuf_size = 0;
    //glob_t globres;
    struct cmd_st cmd;
    pid_t pid;



    while(1) {

        // 命令输入提示符
        prompt();

        // 读取输入
        if ( getline(&linebuf, &linebuf_size, stdin) < 0) {
            break;
        }


        parse(linebuf, &cmd); // 区分内部命令还是外部命令
        if(0) {

        }else{
            pid = fork();
            if(pid < 0) {
                perror("fork");
                exit(1);
            }

            if(pid == 0) { //子进程
                execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
                perror("execvp()");
                exit(1);
            }else{
                wait(NULL);
            }
        }


    } // shell是一个死循环

    exit(0);

}