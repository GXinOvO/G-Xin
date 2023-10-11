/*************************************************************************
	> File Name: 1.eledic.c
	> Author: 
	> Mail: 
	> Created Time: Wed 07 Dec 2022 03:21:12 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    char *trans;
    struct Node *next;
} Node;

Node *loadDict(char *pathname) {
    FILE *fp = fopen(pathname, "r");
    if(!fp) {
        perror("OPEN PATHNAME");
        exit(1);
    } 
    char buf[1024] = {0};
    Node *head = NULL;
    //fgets()的作用是: 从第三个参数指定的流中读取最多第二个参数大小的字符到第一个
    //参数指定的容器地址中。在这个过程中，在还没读取够第二个参数指定大小的字符前，
    //读取到换行符'\n'或者需要读取的流中已经没有数据流。则提前结束，并把读取到的字
    //符存储进第一个参数指定的容器地址中。正常情况下返回值和第一个参数相同，但是如
    //果读取出错或读取文件时文件为空你，则返回一个空指针
    while(fgets(buf, sizeof(buf), fp) != NULL) {
        //创建结点
        Node *node = (Node *)malloc(sizeof(Node));
        
        //添加单词
        node->word = (char *)malloc(sizeof(char) * strlen(buf));
        strcpy(node->word, buf + 1);
        node->word[strlen(node->word) - 1] = 0; //\n -> \0

        //再读一行，添加翻译
        fgets(buf, sizeof(buf), fp);
        node->trans = (char *)malloc(sizeof(char) * strlen(buf));
        strcpy(node->trans, buf + 6);
        node->trans[strlen(node->trans) - 1] = 0; // \n -> \0
        
        //把节点插入链表
        node->next = head;
        head = node;
    }
    fclose(fp);
    return head;
}

void splitTrans(const char *trans) {
    //要记得还需一个\0
    char *buf = (char *)malloc(sizeof(char) * (strlen(trans) + 1));
    strcpy(buf, trans);
    //第一次调用strtok()，传入的参数str是要被分割的字符串
    //而成功后返回的是第一个子字符串
    char *token = strtok(buf, "@");
    int cnt = 1;
    while(token) {
        printf("\033[36m%d : %s\033[0m\n", cnt++, token);
        //第二次调用strtok的时候，传入的参数应该为NULL，
        //使得该函数默认使用上一次未分割完的字符串继续
        //分割，直到结束。
        token = strtok(NULL, "@");
    }
    free(buf);
    return ;
} 

void test(Node *head) {
    int cnt = 1;
    while(head && cnt <= 100) {
        printf("cnt = %d, word = %s\n", cnt++, head->word);
        splitTrans(head->trans);
        head = head->next;
    }
}

Node *findNode(Node *head, char *iwnd) {
    //strcmp只有相等时才会等于0
    while(head && strcmp(iwnd, head->word)) {
        head = head->next;
    }
    return head;

}

void findWord(Node *head) {
    char inwd[1024] = {0};
    while(1) {
        printf("Please input a word : ");
        scanf("%s", inwd);
        if(!strcmp(inwd, "q!")) break;

        //查找节点
        Node *node = findNode(head, inwd);
        if(node) {
            printf("%s\n", node->word);
            splitTrans(node->trans);
        }else {
            printf("please input another word!\n");
        }
    }
    printf("ByeBye~~\n");
    return ;
}

void freeDict(Node *head) {
    Node *delete_node;
    while(head) {
        delete_node = head;
        head = head->next;
        free(delete_node->word);
        free(delete_node->trans);
        free(delete_node);
    }
    return ;
}

int main(int argc, char *argv[]) {
   
    if(argc < 2) {
        printf("Usage: cmd + pathname\n");
        exit(1);
    }

    Node *node;
    
    //把字典数据加载到内存(因为文件太大，CPU的处理速度是最快的，因此让CPU来处理)
    //CPU->内存->文件(处理速度大小比对)
    if((node = loadDict(argv[1])) == NULL) {
        perror("loadDict");
        exit(1);
    }
    //test(node);
    
    //启动字典，支持用户反复查询
    findWord(node);
    
    //释放内存，关闭词典
    freeDict(node);
    
    return 0;
}
