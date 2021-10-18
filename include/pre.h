#ifndef _PRE_H
#define _PRE_H

#include <base.h>
#include <matrix.h>
//pre.h头文件的架构

//提供多种单元
//提供一系列接口包括：
//建立笛卡尔坐标系，作为总体坐标系，单元的坐标系作为局部坐标系。
//单元材料属性，截面参数的输入；创建结点，编辑结点，删除结点等；
//创建单元的智能化，为创建单元的操作提供接口：创建单元，编辑单元，删除单元等；
//引入载荷和边界条件的智能化，为引入边界条件和载荷提供接口：
//为四元载荷（集中力，集中力矩，均布载荷，依靠函数确定的载荷）提供不同的接口；
//边界条件接口：用于确定结点的自由度，

//前处理第一个模块：单元刚度矩阵形成

//梁单元属性的输入:
//输入：梁单元属性（包括E，A，I，l）
//输出：梁单元属性矩阵指针

ELEMENT_ATTRIBUTE* Input_E_A(double A,
                           float E,
                           float G,
                           double I,
                           double L);

//平面梁单元刚度矩阵计算：createplanbeamelementstiffnessmatrix
//输入：梁单元属性结构体
//输出：平面单元刚度矩阵
Matrix* CrPBES(ELEMENT_ATTRIBUTE* );


//空间梁单元刚度矩阵计算：createplanbeamelementstiffnessmatrix
//输入：梁单元属性（包括E，A，I，l）
//输出：空间单元刚度矩阵
Matrix* CrPBES(ELEMENT_ATTRIBUTE* );


//前处理第二个模块：坐标转换模块
//目的：将局部坐标系下的单元刚度矩阵转换为总体坐标系下的单元刚度矩阵。
//方法：采用SO（3）进行坐标变换

//得到单元与总体坐标系的夹角
//输入：两单元梁两端结点的指针
//输出：X,Y,Z的欧拉角矩阵



//前处理第三个模块：总体刚度矩阵形成
//目的：组装所有的单元刚度矩阵，形成总体刚度矩阵。
//方法：采用编码法（自由度编号法）。






#endif