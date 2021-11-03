#ifndef _BASE_H
#define _BASE_H
//基本数据的定义

#define _IN
#define _OUT
#define _IN_OUT

#include <common.h>

extern unsigned int NW;//定义总节点数NW
extern unsigned int NR;//定义受约束的节点总数
extern unsigned int NU;//定义总单元数NU
extern unsigned int QQ;//定义总荷载数QQ

namespace wwj
{
    typedef double REAL;

    enum point_dof
    {   full_dof,
        no_ux,
        no_uy,
        no_rx,
        no_ux_uy,
        no_ux_rx,
        no_uy_rx,
        no_dof
    };

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
        PPOINT ptr;
        struct point_node* next;
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
        PPOINT_DISPLACEMENT ptr;
        struct point_displacement_node* next;
    }POINT_DISPLACEMENT_NODE;

    typedef struct element_attribute
    {
        double A;//截面面积
        double E;//拉压弹性模量
        //double G;//剪切弹性模量
        double I;//极惯性矩
        double L;//单元长度
    }ELEMENT_ATTRIBUTE;//单元属性

    typedef struct element
    {
        //unsigned char KEYOPT;//关键选项
        unsigned char NODE_NUMBER;//节点数
        struct element_attribute* attribute;//单元材料属性结构体指针
        //char* ELEMENT_NAME;//单元名
        unsigned int index;//单元号
        PPOINT ptri;//指向i端节点的指针
        PPOINT ptrj;//指向j端节点的指针
    }ELEMENT;

    typedef ELEMENT* PELEMENT;

    typedef struct element_node
    {
        PELEMENT ptr;
        struct element_node* next;
    }ELEMENT_NODE;

    typedef struct element_attribute_node
    {
        struct element_attribute* ptr;
        struct element_attribute_node* next;
    }ELEMENT_ATTRIBUTE_NODE;

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

    //四元载荷的实现
    //LOAD结构体封装了载荷作用的单元，载荷类型，载荷集度，载荷位置
    typedef struct load
    {
        unsigned int ET_index;//单元号
        CONCENTRATED_FORCE* CONCENTRATED_FORCE_ptr;//集中力的结构体指针
        CONCENTRATED_MOMENT* CONCENTRATED_MOMENT_ptr;//集中力矩的结构体指针
        UNIFORM_LOAD* UNIFORM_LOAD_ptr;//均布载荷的结构体指针
    }LOAD;
    
    typedef LOAD* PLOAD;

    typedef struct load_node
    {
        PLOAD ptr;
        struct load_node* next;
    }LOAD_NODE;

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

    typedef POINT_LOAD* PPOINT_LOAD;

    typedef struct point_load_node
    {
        PPOINT_LOAD ptr;
        struct point_load_node* next;
    }POINT_LOAD_NODE;

    //定义非节点载荷结构体： NO_POINT_LOAD
    typedef struct no_point_load
    {
        double ui;
        double vi;
        double thetai;
        double uj;
        double vj;
        double thetaj;
    }NO_POINT_LOAD;

    typedef NO_POINT_LOAD* PNO_POINT_LOAD;

    typedef struct no_point_load_node
    {
        PNO_POINT_LOAD ptr;
        struct no_point_load_node* next;
    }NO_POINT_LOAD_NODE;

    typedef struct total_load
    {
        double ui;
        double vi;
        double thetai;
        double uj;
        double vj;
        double thetaj;
    }TOTAL_LOAD;

    //使用using定义栈别名
    using POINT_STACKS = stacks1<POINT_NODE>;
    using ELEMENT_STACKS = stacks2<ELEMENT_NODE,ELEMENT_ATTRIBUTE_NODE>;
    using POINT_LOAD_STACKS = stacks1<POINT_LOAD_NODE>;
    using NO_POINT_LOAD_STACKS = stacks1<NO_POINT_LOAD_NODE>;
    using LOAD_STACKS = stacks1<LOAD_NODE>;
}
 #endif
