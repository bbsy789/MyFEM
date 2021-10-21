#ifndef POINT_H
#define POINT_H

#include <base.h>

PPOINT PtCreate(_IN int x, _IN int y, _IN int z, _IN unsigned int index);
void PtDestroy(_IN PPOINT point);
void PtGetValue(_IN PPOINT point, _OUT int *x,
                                  _OUT int *y,
                                  _OUT int *z,
                                  _OUT unsigned int* index);
void PtSetValue(_IN PPOINT point, _IN int x, _IN int y, _IN int z, _IN unsigned int index);
bool PtCompare(_IN PPOINT point1,_IN PPOINT point2);//只比较两个点坐标是否相等
char const* PtTransformIntoString(_IN const char *format, _IN PPOINT point);
void PtPrint(_IN PPOINT point);

PPOINT_DISPLACEMENT PtDCreate(_IN double Xd, _IN double Yd, _IN double Zd, _IN float Xr, _IN float Yr, _IN float Zr, _IN unsigned int index);
void PtDDestroy( _IN PPOINT_DISPLACEMENT );
void PtDGetValue( _IN PPOINT_DISPLACEMENT ,_OUT unsigned int* index,
                                           _OUT double* Yd, 
                                           _OUT double* Zd, 
                                           _OUT float* Xr, 
                                           _OUT float* Yr, 
                                           _OUT float* Zr);
void PtDSetValue( _IN PPOINT_DISPLACEMENT ,_IN double Xd, _IN double Yd, _IN double Zd, _IN float Xr, _IN float Yr, _IN float Zr, _IN unsigned int index);
bool PtDCompare(_IN PPOINT_DISPLACEMENT p1, _IN PPOINT_DISPLACEMENT p2);
char const* PtDTransformIntoString(_IN const char *format, _IN PPOINT_DISPLACEMENT );
void PtDPrint(_IN PPOINT_DISPLACEMENT );
#endif
