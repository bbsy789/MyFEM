#ifndef POINT_H
#define POINT_H

#include <base.h>

//为了不失一般性，使用3维坐标表示，当遇到平面问题时，某一个坐标轴值即为0。
typedef struct point
{
    unsigned int index;//节点号
    double X;//X轴坐标
    double Y;//Y轴坐标
    double Z;//Z轴坐标
}POINT;

typedef POINT* PPOINT;//定义指向POINT的指针类型为PPOINT

//定义节点位移，包含编号，六个自由度
typedef struct point_displacement
{
    unsigned int index;//节点号
    double Xd;//Xdisplacement
    double Yd;//Ydisplacement
    double Zd;//Zdisplacement
    float Xr;//Xrotation
    float Yr;//Yrotation
    float Zr;//Zrotation
}POINT_DISPLACEMENT;

PPOINT PtCreate(int x, int y,int z,unsigned int index);
void PtDestroy(PPOINT point);
void PtGetValue(PPOINT point, int *x, int *y,int *z,unsigned int index);
void PtSetValue(PPOINT point, int x, int y,int z,unsigned int index);
bool PtCompare(PPOINT point1, PPOINT point2);//只比较两个点坐标是否相等
char const* PtTransformIntoString(const char *format, PPOINT point);
void PtPrint(PPOINT point);

#endif
