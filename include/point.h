#ifndef POINT_H
#define POINT_H

#include <base.h>

namespace wwj
{
    POINT* PtCreate(_IN int x, _IN int y, _IN unsigned int index);
    void PtDestroy(_IN POINT* point);
    void PtGetValue(_IN POINT* point, _OUT int *x,
                                    _OUT int *y,
                                    _OUT unsigned int* index);
    void PtSetValue(_IN POINT* point, _IN int x, _IN int y, _IN unsigned int index);
    bool PtCompare(_IN POINT* point1,_IN POINT* point2);//只比较两个点坐标是否相等
    char const* PtTransformIntoString(_IN const char *format, _IN POINT* point);
    void PtPrint(_IN POINT* point);

    POINT_DISPLACEMENT* PtDCreate(_IN double Xd, _IN double Yd, _IN double Zd, _IN float Xr, _IN float Yr, _IN float Zr, _IN unsigned int index);
    void PtDDestroy( _IN POINT_DISPLACEMENT* );
    void PtDGetValue( _IN POINT_DISPLACEMENT* ,_OUT unsigned int* index,
                                            _OUT double* Yd, 
                                            _OUT double* Zd, 
                                            _OUT float* Xr, 
                                            _OUT float* Yr, 
                                            _OUT float* Zr);
    void PtDSetValue( _IN POINT_DISPLACEMENT* ,_IN double Xd, _IN double Yd, _IN double Zd, _IN float Xr, _IN float Yr, _IN float Zr, _IN unsigned int index);
    bool PtDCompare(_IN POINT_DISPLACEMENT* p1, _IN POINT_DISPLACEMENT* p2);
    char const* PtDTransformIntoString(_IN const char *format, _IN POINT_DISPLACEMENT* );
    void PtDPrint(_IN POINT_DISPLACEMENT* );
}
#endif
