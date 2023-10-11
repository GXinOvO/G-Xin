/*************************************************************************
	> File Name: 1.pthread.c
	> Author: 
	> Mail: 
	> Created Time: Fri 09 Dec 2022 02:24:12 PM CST
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int now;
int sum;

//PTHREAD_MUTEX_INITIALIZER是一个结构常量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *do_sth(void *arg) {
    
    int *max = (int *)arg;
    while(1) {
        
        //加锁
        pthread_mutex_lock(&mutex);
        if(now > *max) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        sum += now;
        printf("now = %d, sum = %d pid = %ld\n", now, sum, pthread_self());
        now++;
        
        //解锁
        pthread_mutex_unlock(&mutex);
        
        //这里调用一个usleep()函数，就可以很明显看到几个不同的线程
        //相互抢占，于是我们需要加锁
        usleep(15);
    }
}

int main(int argc, char *argv[]) {
   
    // ./a.out -m npthread -n max
    if(argc != 5) {
        fprintf(stderr, "Usage : %s -m npthread -n max\n", argv[0]);
        exit(1);
    }
    
    int opt;
    int npthread;
    int max;
    while((opt = getopt(argc, argv, "m:n:")) > 0) {
        switch(opt) {
            case 'm':
                npthread = atoi(argv[2]);
                break;
            case 'n':
                max = atoi(argv[4]);
                break;
            default:
                fprintf(stderr, "Usage : %s -m npthread -n max\n", argv[0]);
                exit(1);
        }
    }

    pthread_t tid[npthread];

    for(int i = 0; i < npthread; i++) {

        pthread_create(&tid[i], NULL, do_sth, &max);
    }
    for(int i = 0; i < npthread; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("sum = %d\n", sum);
    return 0;
}
