/*************************************************************************
	> File Name: 1.pipe.c
	> Author: 
	> Mail: 
	> Created Time: Thu 08 Dec 2022 04:18:18 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    int pipefd[2];
    pid_t pid;
    if(pipe(pipefd) < 0) {
        perror("pipe");
        exit(1);
    }
    if((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if(pid) {
        //parent pthread
        close(pipefd[0]);
        printf("i am father fd[0] = %d, f[1] = %d, i close %d\n", pipefd[0], pipefd[1], pipefd[0]);
        char buf[1024] = {0};
        scanf("%[^\n]s", buf);
        getchar();
        write(pipefd[1], buf, strlen(buf));
        wait(NULL);
    }else {
        //child pthread
        close(pipefd[1]);
        printf("i am child fd[0] = %d, f[1] = %d, i close %d\n", pipefd[0], pipefd[1], pipefd[1]);
        char buf[1024] = {0};
        read(pipefd[0], buf, sizeof(buf));
        printf("i read : %s\n", buf);
    }

    return 0;
}
