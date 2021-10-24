#ifndef _BASE_H
#define _BASE_H
//基本数据的定义

#define _IN
#define _OUT
#define _IN_OUT
namespace base
{
typedef double REAL;//

typedef unsigned int NW;//定义总节点数NW
typedef unsigned int NR;//定义受约束的节点总数

typedef unsigned int NU;//定义总单元数NU
typedef unsigned int QQ;//定义总荷载数QQ
typedef unsigned int KE;//定义单元物理性质数KE

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
    char* ELEMENT_NAME;//单元名
    unsigned int index;//单元号
    PPOINT ptri;//指向i端节点的指针
    PPOINT ptrj;//指向j端节点的指针
    ELEMENT* next;
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

template <typename T>
using LOAD = load<T>;

}
 #endif
