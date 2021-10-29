#ifndef _BASE_H
#define _BASE_H
//基本数据的定义

#define _IN
#define _OUT
#define _IN_OUT

#include <common.h>

namespace base
{
    typedef double REAL;//

    static unsigned int NW;//定义总节点数NW
    static unsigned int NR;//定义受约束的节点总数

    static unsigned int NU;//定义总单元数NU
    static unsigned int QQ;//定义总荷载数QQ
    static unsigned int KE;//定义单元物理性质数KE

    typedef struct element_attribute
    {
        double A;//截面面积
        double E;//拉压弹性模量
        //double G;//剪切弹性模量
        double I;//极惯性矩
        double L;//单元长度
    }ELEMENT_ATTRIBUTE;//单元属性

    typedef ELEMENT_ATTRIBUTE* PELEMENT_ATTRIBUTE;

    typedef struct element_attribute_node
    {
        PELEMENT_ATTRIBUTE data;
        ELEMENT_ATTRIBUTE_NODE* next;
    }ELEMENT_ATTRIBUTE_NODE;

    typedef struct point
    {
        unsigned int index;//节点号
        double X;//X轴坐标
        double Y;//Y轴坐标
        //double Z;//Z轴坐标
    }POINT;

    typedef POINT* PPOINT;//定义指向POINT的指针类型为PPOINT

    typedef struct point_node
    {
        PPOINT data;
        POINT_NODE* next;
    }POINT_NODE;

    //定义节点位移，包含编号，六个自由度
    typedef struct point_displacement
    {
        unsigned int index;//节点号
        double u;//X方向位移
        double v;//Y方向位移
        double Thetax;//关于x的转角
        
    }POINT_DISPLACEMENT;

    typedef POINT_DISPLACEMENT* PPOINT_DISPLACEMENT;//定义指向POINT_DISPLACEMEN的指针类型PPOINT_DISPLACEMENT

    typedef struct point_displacement_node
    {
        PPOINT_DISPLACEMENT data;
        POINT_DISPLACEMENT_NODE* next;
    }POINT_DISPLACEMENT_NODE;

    typedef struct element
    {
        //unsigned char KEYOPT;//关键选项
        unsigned char NODE_NUMBER;//节点数
        ELEMENT_ATTRIBUTE* attribute;//单元材料属性结构体指针
        //char* ELEMENT_NAME;//单元名
        unsigned int index;//单元号
        PPOINT ptri;//指向i端节点的指针
        PPOINT ptrj;//指向j端节点的指针
    }ELEMENT;

    typedef ELEMENT* PELEMENT;

    typedef struct element_node
    {
        PELEMENT data;
        ELEMENT_NODE* next;
    }ELEMENT_NODE;

    //四元载荷
    template<typename T>
    struct load
    {
        unsigned int ET_index;//单元号
        struct T category;//载荷类型的结构体指针
    };
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

    template <typename T>
    using LOAD = load<T>;

    using POINT_STACKS = stacks<POINT,POINT_NODE>;
    using ELEMENT_ATTRIBUTE_STACKS = stacks<ELEMENT_ATTRIBUTE,ELEMENT_ATTRIBUTE_NODE>;
    using ELEMENT_STACKS = stacks<ELEMENT,ELEMENT_NODE>;
    using POINT_LOAD_STACKS = stacks<POINT_LOAD,POINT_LOAD_NODE>;
}
 #endif
