/*************************************************************************
	> File Name: 2.pthread_pool.c
	> Author: 
	> Mail: 
	> Created Time: Fri 09 Dec 2022 06:44:58 PM CST
 ************************************************************************/

#include <stdio.h>
#include "3.head.h"

#define INS 5
#define MAX 20

int main(int argc, char *argv[]) {
    
    //模拟顾客来到理发店，打印文件的每一行
    //文件的每一行 - 顾客
    //打印文件的每一行 - tony(pop)
    //读到文件的一行 - 顾客进入到理发店坐到等待区(队列push)

    //打开文件
    //初始化队列()
    //读文件每一行，放到队列中(push)
    //线程池中的线程响应队列中的请求(pop, do_work)
    //如果队列满了

    pthread_t tid[INS];
    struct task_queue taskQueue;
    char buf[MAX][1024] = {0};

    task_queue_init(&taskQueue, MAX);
    for(int i = 0; i < INS; i++) {
        pthread_create(&tid[i], NULL, do_work, (void *)&taskQueue);
    }
    while(1) {
        //创建顾客
        int sub = 0;
        FILE *fp = fopen("a.txt", "r");
        if(fp == NULL) {
            perror("fopen");
            exit(1);
        }
        //模拟顾客源源不断的来
        while((fgets(buf[sub], 1024, fp)) != NULL) {
            task_queue_push(&taskQueue, buf[sub]);
            sleep(1);
            sub++;
            if(sub == MAX) {
                printf("sub = queuesize\n");
                sub = 0;
            }
            if(taskQueue.size == taskQueue.total) {
                //模拟自旋等待 在门口等
                while(1) {
                    if(taskQueue.size > taskQueue.total) break;
                    else usleep(50000);
                }
            }
        }    
        fclose(fp);
    }


    return 0;
}
