#ifndef _PRE_H
#define _PRE_H
//pre.h 0.11

//包含头文件
#include <base.h>
#include <matrix.h>
#include <point.h>
#include <load.h>

#include <vector>

using std::vector;

std::vector<MATRIX*> V;//使用stl，vector模板类创建的矩阵指针数组

//pre.h头文件的架构

//提供多种单元
//提供一系列接口包括：
//建立笛卡尔坐标系，作为总体坐标系，单元的坐标系作为局部坐标系。
//单元材料属性，截面参数的输入；创建节点，编辑节点，删除节点等；
//创建单元的智能化，为创建单元的操作提供接口：创建单元，编辑单元，删除单元等；
//引入载荷和边界条件的智能化，为引入边界条件和载荷提供接口：
//为四元载荷提供不同的接口；
//边界条件接口：用于确定节点的自由度。

//前处理第一个模块：单元刚度矩阵形成

//梁单元属性的输入:
//输入：梁单元属性（包括E，A，I，l）
//输出：梁单元属性矩阵指针

ELEMENT_ATTRIBUTE* Input_E_A(double A,
                           float E,
                           float G,
                           double I,
                           double L);

//不考虑剪切变形的平面梁单元刚度矩阵计算：compute-plan-beam-element-stiffness-matrix-not-shear
//输入：梁单元属性结构体
//输出：不考虑剪切变形的平面梁单元刚度矩阵
MATRIX* Compute_PBES_NS(ELEMENT_ATTRIBUTE* );


//不考虑剪切变形的空间梁单元刚度矩阵计算：compute-space-beam-element-stiffness-matrix
//输入：梁单元属性（包括E，A，I，l）
//输出：不考虑剪切变形的空间单元刚度矩阵
MATRIX* Compute_SBES_NS(ELEMENT_ATTRIBUTE* );


//前处理第二个模块：坐标转换模块
//目的：将局部坐标系下的单元刚度矩阵转换为总体坐标系下的单元刚度矩阵。
//方法：采用SO（3）进行坐标变换

//计算坐标变换矩阵：compute-coordinate-transfer-matrix
//输入：梁单元两端节点的指针
//输出：该梁单元的局部坐标转整体坐标的SO（3）矩阵
MATRIX* Compute_CTM(POINT* i,POINT* j);

//前处理第三个模块：总体刚度矩阵形成: component-total-stiffness-matrix
//目的：组装所有的单元刚度矩阵，形成总体刚度矩阵。
//方法：采用编码法（自由度编号法）。
//规则：a = b*(k - 1) + c
//其中：b = 6;k-节点号；c-节点自由度号,[1-6]。
//由梁单元两个节点的单刚K12*12^e 组装成总刚 K6NW*6NW
//等带宽存储，DD=(节点号插值最大+1)*节点自由度号；变带宽存储和一维变带宽存储.目的是减少总刚矩阵在内存中存放的空间。本算例忽略
//输入：坐标变换后的总体坐标系下的单元刚度矩阵vector数组
//输出：总体刚度矩阵
MATRIX* Component_TSM(vector<MATRIX*> &V);

//前处理第四个模块
//节点载荷计算：compute-point-load
//按照四元载荷等效原理，等效到节点载荷，
//使用C++函数重载，匹配四种载荷的不同输入输出
//输入：某一单元结构体指针，该单元载荷结构体（四元荷载）指针
//输出：该单元节点载荷结构体指针


//节点载荷计算：compute-point-load
//按照四元载荷等效原理，等效到节点载荷，
//输入：某一单元结构体指针，该单元集中力结构体指针
//输出：该单元节点载荷结构体指针
POINT_LOAD* Compute_PL(ELEMENT* E,CONCENTRATED_FORCE* F);

//节点载荷计算：compute-point-load
//按照四元载荷等效原理，等效到节点载荷，
//输入：某一单元结构体指针，该单元集中力矩结构体指针
//输出：该单元节点载荷结构体指针
POINT_LOAD* Compute_PL(ELEMENT* E,CONCENTRATED_MOMENT* M);

//节点载荷计算：compute-point-load
//按照四元载荷等效原理，等效到节点载荷，
//输入：某一单元结构体指针，该单元均布载荷结构体指针
//输出：该单元节点载荷结构体指针
POINT_LOAD* Compute_PL(ELEMENT* E,UNIFORM_LOAD* Q);

#endif