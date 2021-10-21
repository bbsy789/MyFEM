#ifndef POINT_H
#define POINT_H

PPOINT PtCreate(int x, int y,int z,unsigned int index);
void PtDestroy(PPOINT point);
void PtGetValue(PPOINT point, int *x, int *y,int *z,unsigned int index);
void PtSetValue(PPOINT point, int x, int y,int z,unsigned int index);
bool PtCompare(PPOINT point1, PPOINT point2);//只比较两个点坐标是否相等
char const* PtTransformIntoString(const char *format, PPOINT point);
void PtPrint(PPOINT point);

PPOINT_DISPLACEMENT PtDCreate(double Xd,double Yd,double Zd,fload Xr,float Yr,float Zr,unsigned int index);
void PtDDestroy(PPOINT_DISPLACEMENT point_displacement);
void PtDGetValue

#endif
