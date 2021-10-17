//POINT是结构力学中的离散化的节点的结构体，是数据。
//list是ADT，抽象链表。
#include <base.h>
#include <point.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include "point.h"

using namespace std;

static char * DuplicateString(const char *s);

PPOINT PtCreate(int x, int y,int z,unsigned int index)
{
    PPOINT t = new POINT;
    t->X = x;
    t->Y = y;
    t->Z = z;
    t->index = index;
    return t;
}

void PtDestroy(PPOINT point)
{
    if (point)
        delete point;
}

void PtGetValue(PPOINT point, int *x, int *y,int *z,unsigned int index)
{
    if (point) {
        if (x) 
        {
            *x = point->X;
        }
        if (y) 
        {
            *y = point->Y;
        }
        if (z) 
        {
            *z = point->Z;
        }
    }
}

void PtSetValue(PPOINT point, int x, int y,int z,unsigned int index)
{
    if (point) {
        point->X = x;
        point->Y = y;
        point->Z = z;
        point->index = index;
    }
}

bool PtCompare(PPOINT point1, PPOINT point2)
{
    if (!point1 || !point2) {
        printf("PtCompare:参数非法！\n");
        exit(1);
    }
    return (point1->X == point2->X) && (point1->Y == point2->Y) && (point1->Z == point2->Z) && point1->index == point2->index;
}

char const* PtTransformIntoString(const char *format, PPOINT point)
{
    char buf[BUFSIZ];//BUFSIZ在stdio.h中定义，linux上可能是8192
    if (point) {
        sprintf(buf, format, point->X, point->Y, point->Z, point->index);
        return DuplicateString(buf);
    }
    else
        return "NULL";
}

void PtPrint(PPOINT point)
{
    if (point)
        printf("(X:%.6lf, Y:%.6lf, Z:%.6lf, index:%d)", point->X, point->Y, point->Z, point->index);
    else
        printf("NULL");
}

char* DuplicateString(const char *s)
{
    int n = strlen(s);
    char *t = new char[n+1];
    for (int i = 0; i < n; ++i)
        t[i] = s[i];
    t[n] = '\0';
    return t;
}
