/*************************************************************************
	> File Name: 1.myshell.c
	> Author: 
	> Mail: 
	> Created Time: Thu 08 Dec 2022 12:42:30 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>

char *strip(char *str) {
    //strlen()包含\0
    int head = 0, tail = strlen(str) - 1;
    //isspace()用来判断字符是否为空格/回车/制表符等，失败返回0
    while(isspace(str[head])) {
        head++;
    }
    while(isspace(str[tail])) {
        str[tail--] = '\0';
    }
    return str + head;
}

void do_work(char *buf) {
    
    //判断buf里是否有重定向符号
    //如果有重定向符号，分割，如果没有重定向符号，继续
    int redfd = -1;//重定向标准输入、输出redefine fd
    
    if(strstr(buf, "<")) {
        //标准输入
        redfd = 0;
    }else if(strstr(buf, ">")) {
        redfd = 1;
    }

    char *cmd = NULL, *file = NULL;
    if(redfd == -1) {
        cmd = strip(buf);
    }else {
        //strtok()的第二个参数可以是字符也可以是字符集
        cmd = strip(strtok(buf, "><"));
        file = strip(strtok(NULL, "><"));

        //流的重定向
        int fd;
        if(redfd == 0) {
            fd = open(file, O_RDONLY);
        } else {
            fd = open(file, O_RDWR | O_CREAT, 0644);
        }

        close(redfd);
        dup2(fd, redfd);
        close(fd);
    }

    //printf("cmd = [%s], file = [%s]\n", cmd, file);
    char *argv[100];
    int i = 0;
    argv[i++] = strtok(cmd, " ");
    while(argv[i++] = strtok(NULL, " ")) {}
    if(execvp(cmd, argv) < 0) {
        perror("execvp");
        exit(1);
    }
}


int main(int argc, char *argv[]) {
   
    signal(SIGTTOU, SIG_IGN);
    char buf[1024] = {0};
    while(1) {
        memset(buf, 0, sizeof(buf));
        printf("\033[32mbury\033[37m@\033[31mhuguangyao\033[0m $");
        scanf("%[^\n]s", buf);
        getchar();
        if(!strcmp(buf, "exit")) {
            break;
        }else if(!buf[0]) {
            continue;
        }
        
        //判断是否有管道符号
        char *cmdarr[20];
        int i = 0;
        cmdarr[i] = strtok(buf, "|");
        //printf("%d : %s\t", i, cmdarr[i]);
        i++;
        while(cmdarr[i] = strtok(NULL, "|")) {
            //printf("%d : %s\t", i, cmdarr[i]);
            i++;
        }
        pid_t pid, pgrp;
        printf("i = %d\n", i);
        if(!cmdarr[1]) {
            if((pid = fork()) < 0)  {
                perror("fork");
                exit(1);
            }
            if(pid == 0) {
                //child pthread
                //printf("执行命令 : %s\n", buf);
                //sleep(3);
                do_work(buf);
                exit(0);
            }else {
                //parent pthread
                //wait()的作用是阻塞，然后等待子进程变成僵尸，收集信息
                //然后消除它
                wait(NULL);
                continue;
            }
        }else {
            //如果有管道
            int pipefd[20][2];
            int j;
            for(j = 0; j < i - 1; j++) {
                if(pipe(pipefd[j]) < 0) {
                    perror("pipe");
                    exit(1);
                }
            }
            for(j = 0; j < i; j++) {
                if((pid = fork()) < 0) {
                    perror("fork1");
                    exit(1);
                }
                if(pid == 0) {
                    if(j == 0) {
                        //first child pthread
                        dup2(pipefd[j][1], 1);
                    }else if(j == i - 1) {
                        //last child pthread
                        dup2(pipefd[j - 1][0], 0);
                    }else {
                        dup2(pipefd[j - 1][0], 0);
                        dup2(pipefd[j][1], 1);
                    }
                    for(int k = 0; k < i - 1; k++) {
                        close(pipefd[k][0]);
                        close(pipefd[k][1]);
                    }
                    do_work(cmdarr[j]);
                } else {
                    if(j == 0) {
                        pgrp = pid;
                    }
                    //第一个进入进程组的pid作为进程组的id
                    setpgid(pid, pgrp);
                    //前台进程组，
                    tcsetpgrp(0, pgrp);
                }
            }
            for(int k = 0; k < i - 1; k++) {
                close(pipefd[k][0]);
                close(pipefd[k][1]);
            }
            for(int k = 0; k < i; k++) {
                wait(NULL);
            }
            tcsetpgrp(1, getpid());
        }
    }

    return 0;
}
