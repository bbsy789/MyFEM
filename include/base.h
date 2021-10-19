#ifndef _BASE_H
#define _BASE_H
//基本数据的定义


#define _IN
#define _OUT
#define _IN_OUT

typedef unsigned int NW;//定义总节点数NW
typedef unsigned int NR;//定义受约束的节点总数

typedef unsigned int NU;//定义总单元数NU
typedef unsigned int QQ;//定义总荷载数QQ
typedef unsigned int KE;//定义单元物理性质数KE

//为了不失一般性，使用3维坐标表示，当遇到平面问题时，某一个坐标轴值即为0。
typedef struct point
{
    unsigned int index;//节点号
    double X;//X轴坐标
    double Y;//Y轴坐标
    double Z;//Z轴坐标
}POINT;

typedef POINT* PPOINT;//定义指向POINT的指针类型为PPOINT

typedef struct element_attribute
{
    double A;//截面面积
    float E;//拉压弹性模量
    float G;//剪切弹性模量
    double I;//极惯性矩
    double L;//单元长度
}ELEMENT_ATTRIBUTE;//单元属性

typedef struct element
{
    //unsigned char KEYOPT;//关键选项
    unsigned char NODE_NUMBER;//节点数
    ELEMENT_ATTRIBUTE attribute;//单元材料属性
    char* ELEMENT_NAME;//单元名
    unsigned int index;//单元号
}ELEMENT;

typedef struct load
{
    unsigned int ET_index;//单元号
    unsigned char category;//载荷类型
    double load_set;//载荷集度
    unsigned int NODE_index;//节点号
    double load_x;//载荷位置X
    double load_y;//载荷位置Y
    double load_z;//载荷位置Z
    float load_tx;//载荷位置theta_x
    float load_ty;//载荷位置theta_y
    float load_tz;//载荷位置theta_z
}LOAD;


 #endif