/*************************************************************************
	> File Name: 2.pool.h
	> Author: 
	> Mail: 
	> Created Time: Fri 09 Dec 2022 06:48:43 PM CST
 ************************************************************************/

#ifndef _2.POOL_H
#define _2.POOL_H
/*队列*/
struct task_queue {
    int size;//大小
    int total;//请求的个数
    int head;
    int tail;
    void **data;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

/*初始化队列*/
void task_queue_init(struct task_queue *taskQueue, int size);

/*入队*/
void task_queue_push(struct task_queue *taskQueue, char *buf);

/*出队*/
char *task_queue_pop(struct task_queue *taskQueue);

/* do_work 打印*/
void *do_work(void *arg);

#endif
