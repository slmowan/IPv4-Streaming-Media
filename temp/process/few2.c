#include <sys/wait.h>
#include <unistd.h>


// Lec04 ppt P27页习题
// Lec04 34:16处
// Writing a program to run program —— shell
// 用execlp function

#define MAX_CMD_LEN 512
#define PROMPT "> "

int main() {
    char cmd[MAX_CMD_LEN];
    while(1) {
        printf(PROMPT);

        // Read in command and exit if needed
        // fork a child process
        // child runs command
        // parent waits for child and prints child's exit code

    }
}