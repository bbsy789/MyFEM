#ifndef LOAD_H
#define LOAD_H

//定义节点载荷结构体： POINT_LOAD
typedef struct point_load
{
    double ui;
    double vi;
    double thetai;
    double uj;
    double vj;
    double thetaj;
}POINT_LOAD;

//定义集中力载荷结构体：Concentrated force
typedef struct concentrated_force
{
    double size;//集中力的大小
    double position;//集中力距离单元i端的长度
}CONCENTRATED_FORCE;

//定义集中力矩结构体：Concentrated moment
typedef struct concentrated_moment
{
    double size;//集中力矩的大小
    double position;//集中力矩距离单元i端的长度
}CONCENTRATED_MOMENT;

//定义均布荷载结构体：uniform load
typedef struct uniform_load
{
    double size;//均布荷载大小
    double positioni;//均布荷载距离单元i端的长度
    double positionj;//均布荷载距离单元j端的长度
}UNIFORM_LOAD;


#endif 