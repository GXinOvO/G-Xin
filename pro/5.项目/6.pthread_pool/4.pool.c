/*************************************************************************
	> File Name: 4.pool.c
	> Author: 
	> Mail: 
	> Created Time: Fri 09 Dec 2022 06:58:14 PM CST
 ************************************************************************/

#include "3.head.h"

/*队列的初始化*/
void task_queue_init(struct task_queue *taskQueue, int size) {
    taskQueue->size = size;
    taskQueue->total = 0;
    taskQueue->head = taskQueue->tail = 0;

    pthread_mutex_init(&taskQueue->mutex, NULL);
    pthread_cond_init(&taskQueue->cond, NULL);
    
    //calloc()在申请后对空间逐一进行初始化，并设置值为0
    taskQueue->data = calloc(size, sizeof(void *));
    
    return ;
}

/*入队*/
void task_queue_push(struct task_queue *taskQueue, char *buf) {

    pthread_mutex_lock(&taskQueue->mutex);
    if(taskQueue->total == taskQueue->size) {
        //队列满
        fprintf(stderr, "taskQueue is full\n");
        pthread_mutex_unlock(&taskQueue->mutex);
        return ;
    }
    taskQueue->data[taskQueue->tail] = buf;
    taskQueue->tail++;
    taskQueue->total++;

    //因为我们是循环队列，就循环了一遍
    if(taskQueue->tail == taskQueue->size) {
        taskQueue->tail = 0;
        printf("taskQueue tail reach end\n");
    }
    //pthread_cond_signal()的作用是发送一个信号给另外一个正在处于阻塞
    //等待状态的线程，使其脱离阻塞阻塞状态，继续执行
    pthread_cond_signal(&taskQueue->cond);
    pthread_mutex_unlock(&taskQueue->mutex);
}

/*出队*/
char *task_queue_pop(struct task_queue *taskQueue) {
    pthread_mutex_lock(&taskQueue->mutex);
    if(taskQueue->total == 0) {
        printf("taskQueue is empty\n");
        pthread_cond_wait(&taskQueue->cond, &taskQueue->mutex);
    }

    char *buf = taskQueue->data[taskQueue->head];
    taskQueue->head++;
    taskQueue->total--;
    if(taskQueue->head == taskQueue->size) {
        taskQueue->head = 0;
        printf("taskQueue head reach end\n");
    }
    pthread_mutex_unlock(&taskQueue->mutex);
    return buf;
}

/* do_work 打印 */
void *do_work(void *arg) {
    pthread_detach(pthread_self());
    struct task_queue *taskQueue = (struct task_queue *)arg;
    while(1) {
        char *buf = task_queue_pop(taskQueue);
        printf("<%ld> %s\n", pthread_self(), buf);
    }
}
