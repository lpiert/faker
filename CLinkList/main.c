
#include "linkList.h"
#include "EasyFree.h"


int main(int argc, char** argv)
{
#if 0 
    // 创建链表
    LLIST_T* list = llist_new(sizeof(Data));
    if (list == NULL) goto end;
    // 数据存储
    Data* data_1 = initData();
    data_1->age = 1;
    memcpy(data_1->dress, "lucking", sizeof("lucking"));
    // 追加节点
    llist_node_append(list, data_1);
    Data* data_2 = initData();
    data_2->age = 2;
    memcpy(data_2->name, "jack", sizeof("jack"));
    llist_node_append(list, data_2);
    // 查询节点
    Data* node = llist_node_find(list, node_comp_func, data_2);
    if (node)
        printf("find node age: %d\n", node->age);
    // 遍历节点
    llist_travel(list, node_proc_func);
    printf("current list size:%d", (*(List*)list).lmsize);

    // 前插节点
    Data* data_3 = initData();
    data_3->age = 3;
    memcpy(data_3->dress, "joineries", sizeof("joineries"));
    llist_node_prepend(list, data_3);
    // 遍历节点
    llist_travel(list, node_proc_func);
    printf("current list size:%d", (*(List*)list).lmsize);
    // 删除节点
    llist_node_delete(list, node_comp_func, data_1);
    // 遍历节点
    llist_travel(list, node_proc_func);
    printf("current list size:%d", (*(List*)list).lmsize);
    // 删除链表
    if (llist_delete(list) == NULL) goto delete;
    // 释放资源
    free(list);
delete:
    list = NULL;
    free(data_1);
    data_1 = NULL;
    free(data_2);
    data_2 = NULL;
    free(data_3);
    data_3 = NULL;
end:
#endif
    int* a = (int*)malloc(sizeof(int));
    int* b = (int*)malloc(sizeof(int));
    printf("%p %p\n", a, b);    
    
    system("pause");
    RETURN_X(0, a, b);
}


