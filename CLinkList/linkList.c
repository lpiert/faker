#include "linkList.h"


// 获取初始化后的数据指针
Data* initData()
{
    Data* data = malloc(sizeof(Data));
    memset(data, 0, sizeof(Data));
    return data;
    //return (Data*)calloc(1, sizeof(Data));
}

void node_proc_func(const Data* data)
{
    assert(data);
    printf("current node:\n"
        "age:%d\n"
        "height:%d\n"
        "name:%s\n"
        "dress:%s\n"
        "description:%s\n",
        data->age,data->height,data->name,data->dress,data->descrip);
}

int node_comp_func(const Data* p, const Data* n)
{
    assert(p);
    assert(n);
    return (p->age == n->age && p->height == n->height &&
        strcmp(p->name,n->name)==0  &&
        strcmp(p->dress, n->dress) == 0 &&
        strcmp(p->descrip, n->descrip) == 0);
}

// 创建链表
LLIST_T* llist_new(int elmsize) {
    List* newlist = NULL;
    newlist = calloc(1,sizeof(List));
    if (newlist == NULL)
        return NULL;
    newlist->head.datap = initData();
    newlist->head.next = &newlist->head;
    newlist->head.prev = &newlist->head;
    newlist->elmnr = elmsize;
    return (void*)newlist;
}

// 追加节点
int llist_node_append(LLIST_T* ptr, const void* datap) {
    assert(ptr);
    assert(datap);
    List* me = ptr;
    Node* newnodep = NULL;
    newnodep = calloc(1,sizeof(Node));
    if (newnodep == NULL)
        return -1;
    newnodep->datap = calloc(1,me->elmnr);
    if (newnodep->datap == NULL) {
        free(newnodep);
        newnodep = NULL;
        return -1;
    }
    memcpy(newnodep->datap, datap, me->elmnr);
    me->head.prev->next = newnodep;
    newnodep->prev = me->head.prev;
    me->head.prev = newnodep;
    newnodep->next = &me->head;
    me->lmsize++;
    return 0;
}

// 前插节点
int llist_node_prepend(LLIST_T* ptr, const void* datap) {
    assert(ptr);
    assert(datap);
    List* me = (List*)ptr;
    Node* newnodep = NULL;
    newnodep = calloc(1,sizeof(Node));
    if (newnodep == NULL)
        return -1;
    newnodep->datap = calloc(1,me->elmnr);
    if (newnodep->datap == NULL) {
        free(newnodep);
        newnodep = NULL;
        return -1;
    }
    memcpy(newnodep->datap, datap, me->elmnr);
    me->head.next->prev = newnodep;
    newnodep->next = me->head.next;
    me->head.next = newnodep;
    newnodep->prev = &me->head;
    me->lmsize++;
    return 0;
}

// 删除节点
void* llist_delete(LLIST_T* ptr) {
    assert(ptr);
    List* me = (List*)ptr;
    Node* curr, * save;
    curr = save = NULL;
    for (curr = me->head.next;
        curr != &me->head; curr = save) {
        save = curr->next;
        free(curr->datap);
        free(curr);
        curr = NULL;
    }
    free(me);
    me = NULL;
    return me;
}

void llist_node_delete(LLIST_T* ptr,
    node_comp_fun_t* comp,
    const void* key) {
    assert(ptr);
    assert(comp);
    assert(key);
    List* me = (List*)ptr;
    Node* curr = NULL;
    for (curr = me->head.next;
        curr != &me->head; curr = curr->next) {
        if ((*comp)(curr->datap, key)) {
            Node* _next, * _prev;
            _prev = curr->prev; _next = curr->next;
            _prev->next = _next; _next->prev = _prev;
            free(curr->datap);
            free(curr);
            curr = NULL;
            break;
        }
    }
    me->lmsize--;
    return;
}

// 查找节点
void* llist_node_find(LLIST_T* ptr,
    node_comp_fun_t* comp, const void* key) {
    assert(ptr);
    assert(comp);
    assert(key);
    List* me = (List*)ptr;
    Node* curr = NULL;
    for (curr = me->head.next;
        curr != &me->head; curr = curr->next) {
        if ((*comp)(curr->datap, key))
            return curr->datap;
    }
    return NULL;
}

// 遍历节点
int llist_travel(LLIST_T* ptr, node_proc_fun_t* proc) {
    assert(ptr);
    assert(proc);
    List* me = (List*)ptr;
    Node* curr = NULL;
    printf("show all node contents.\n");
    for (curr = me->head.next;
        curr != &me->head; curr = curr->next)
        proc(curr->datap);
    return 0;
}