
#include "linkList.h"
#include "EasyFree.h"


int main(int argc, char** argv)
{
#if 0 
    // ��������
    LLIST_T* list = llist_new(sizeof(Data));
    if (list == NULL) goto end;
    // ���ݴ洢
    Data* data_1 = initData();
    data_1->age = 1;
    memcpy(data_1->dress, "lucking", sizeof("lucking"));
    // ׷�ӽڵ�
    llist_node_append(list, data_1);
    Data* data_2 = initData();
    data_2->age = 2;
    memcpy(data_2->name, "jack", sizeof("jack"));
    llist_node_append(list, data_2);
    // ��ѯ�ڵ�
    Data* node = llist_node_find(list, node_comp_func, data_2);
    if (node)
        printf("find node age: %d\n", node->age);
    // �����ڵ�
    llist_travel(list, node_proc_func);
    printf("current list size:%d", (*(List*)list).lmsize);

    // ǰ��ڵ�
    Data* data_3 = initData();
    data_3->age = 3;
    memcpy(data_3->dress, "joineries", sizeof("joineries"));
    llist_node_prepend(list, data_3);
    // �����ڵ�
    llist_travel(list, node_proc_func);
    printf("current list size:%d", (*(List*)list).lmsize);
    // ɾ���ڵ�
    llist_node_delete(list, node_comp_func, data_1);
    // �����ڵ�
    llist_travel(list, node_proc_func);
    printf("current list size:%d", (*(List*)list).lmsize);
    // ɾ������
    if (llist_delete(list) == NULL) goto delete;
    // �ͷ���Դ
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


