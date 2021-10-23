#ifndef DYNLIST_H
#define DYNLIST_H

typedef struct LIST * PLIST;

typedef void * ADT;
typedef const void * CADT;
typedef int (*COMPARE_OBJECT)(CADT e1, CADT e2);//用来比较ADT类型数据的回调函数的函数指针
typedef void (*DESTROY_OBJECT)(ADT e);//用来删除ADT数据类型的回调函数的函数指针
typedef void (*MANIPULATE_OBJECT)(ADT e, ADT tag);//用来操作ADT类型数据的回调函数的函数指针

PLIST LICreate();//链表的构造
void LIDestroy(PLIST list, DESTROY_OBJECT destroy);//链表的销毁
void LIAppend(PLIST list, ADT object);//追加节点
void LIInsert(PLIST list, ADT object, int pos);//插入节点
void LIDelete(PLIST list, int pos, DESTROY_OBJECT destroy);//删除节点
void LIClear(PLIST list, DESTROY_OBJECT destroy);//链表清空
void LITraverse(PLIST list, MANIPULATE_OBJECT manipulate, ADT tag);//链表遍历
bool LISearch(PLIST list, ADT object, COMPARE_OBJECT compare);//查找节点
int LIGetCount(PLIST list);//统计节点个数
bool LIIsEmpty(PLIST list);//链表是否为空

#endif
