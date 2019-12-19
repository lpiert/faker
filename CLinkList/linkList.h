// linkList.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#ifndef LINK_LIST_H_
#define LINK_LIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <corecrt_memcpy_s.h>
#include <windows.h>

// 数据结构定义
typedef struct data
{
    int age;
    int height;
    char name[64];
    char dress[128];
    char descrip[512];
}Data;

Data* initData();
void node_proc_func(const Data* data);
int node_comp_func(const Data* p, const Data* n);


// 链表节点定义，data 为void* 可以自定义
typedef struct node {
    void* datap;
    struct node * next, * prev;
}Node;

// 链表定义
typedef struct list {
    Node head;
    int lmsize;
    int elmnr;
}List;

// 找到节点后操作
typedef void node_proc_fun_t(void*);
// 比较节点
typedef int node_comp_fun_t(const void*, const void*);
// 列表定义
typedef void LLIST_T;

// 初始化
LLIST_T* llist_new(int elmsize);
// 删除
void* llist_delete(LLIST_T* ptr);
// 前后插入
int llist_node_append(LLIST_T* ptr, const void* datap);
int llist_node_prepend(LLIST_T* ptr, const void* datap);
// 遍历
int llist_travel(LLIST_T* ptr, node_proc_fun_t* proc);
// 删除
void llist_node_delete(LLIST_T* ptr, node_comp_fun_t* comp, const void* key);
// 查找
void* llist_node_find(LLIST_T* ptr, node_comp_fun_t* comp, const void* key);

#endif
// TODO: 在此处引用程序需要的其他标头。
