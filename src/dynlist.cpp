#include <iostream>
#include <cstdio>
#include "dynlist.h"

using namespace std;

typedef struct NODE * PNODE;

struct NODE {
    ADT data;
    PNODE next;
};

struct LIST {
    int count; //节点个数
    PNODE head, tail;//链表头尾指针
};

PLIST LICreate()
{
    PLIST p = new LIST;
    p->count = 0;
    p->head = nullptr;
    p->tail = nullptr;
    return p;
}

void LIDestroy(PLIST list, DESTROY_OBJECT destroy)
{
    if (list) {
        LIClear(list, destroy);
        delete list;
    }
}

void LIAppend(PLIST list, ADT object)
{
    PNODE t = new NODE;
    if (!list || !object) {
        printf("LIAppend:参数非法！\n");
        exit(1);
    }
    t->data = object;
    t->next = nullptr;
    if (!list->head) {//链表为空时，追加节点作为链表唯一节点
        list->head = t;
        list->tail = t;
    }
    else {//一般情况，把当前尾节点指向新节点，再将新节点作为新尾节点
        list->tail->next = t;
        list->tail = t;
    }
    list->count++;
}

void LIInsert(PLIST list, ADT object, int pos)
{
    if (!list || !object) {
        printf("LIInsert:参数非法！\n");
        exit(1);
    }
    if (pos < list->count) {
        PNODE t = new NODE;
        t->data = object;
        t->next = nullptr;
        if (pos == 0) {//如果在表头插入，就刷新头部指针
            t->next = list->head;
            list->head = t;
        }
        else {//一般情况下
            PNODE u = list->head;//找到待插入位置的前一节点u
            for (int i = 0; i < pos - 1; ++i)
                u = u->next;
            t->next = u->next;//把节点插进去
            u->next = t;
        }
        list->count++;
    }
    else
        LIAppend(list, object);//另一种情况，在尾部追加节点
}

void LIDelete(PLIST list, int pos, DESTROY_OBJECT destroy)
{
    if (!list) {
        printf("LIDestroy:参数非法！\n");
        exit(1);
    }
    if (list->count == 0)
        return;
    if (pos == 0) {//删除头部节点
        PNODE t = list->head;
        list->head = t->next;
        if (!t->next)
            list->tail = nullptr;
        if (destroy)
            (*destroy)(t->data);
        delete t;
        list->count--;
    }
    else if (pos < list->count) {//其他情况
        PNODE u = list->head, t;
        for (int i = 0; i < pos - 1; ++i)
            u = u->next;
        t = u->next;
        u->next = t->next;
        if (!t->next)//删除尾部节点
            list->tail = u;
        if (destroy)
            (*destroy)(t->data);
        delete t;
        list->count--;
    }
}

void LIClear(PLIST list, DESTROY_OBJECT destroy)
{
    if (!list) {
        printf("LIClear：参数非法！\n");
        exit(1);
    }
    while(list->head) {
        PNODE t = list->head;
        list->head = t->next;
        if (destroy)
            (*destroy)(t->data);
        delete t;
        list->count--;
    }
    list->tail = nullptr;
}

void LITraverse(PLIST list, MANIPULATE_OBJECT manipulate, ADT tag)
{
    PNODE t = list->head;
    if (!list) {
        printf("LITraverse:参数非法！\n");
        exit(1);
    }
    while(t) {
        if (manipulate)
            (*manipulate)(t->data, tag);
        t = t->next;
    }
}

bool LISearch(PLIST list, ADT object, COMPARE_OBJECT compare)
{
    PNODE t = list->head;
    if (!list || !object) {
        printf("LISearch:参数非法！\n");
        exit(1);
    }
    while(t) {
        if ((*compare)(t->data, object))
            return true;
        t = t->next;
    }
    return false;
}

int LIGetCount(PLIST list)
{
    return list->count;
}

bool LIIsEmpty(PLIST list)
{
    return list->count == 0;
}
