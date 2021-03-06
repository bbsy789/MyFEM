#ifndef _PRE_H
#define _PRE_H

//pre.h 1.0

//包含头文件
#include <base.h>
#include <matrix.h>
#include <common.h>
#include <fast_io.h>

namespace wwj
{
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

    //不考虑剪切变形的平面梁单元刚度矩阵计算：compute-plan-beam-element-stiffness-matrix-not-shear
    //输入：梁单元属性结构体，已分配好空间的数组指针
    //输出：不考虑剪切变形的平面梁单元刚度矩阵
    MATRIX* Compute_PBES_NS(_IN const ELEMENT_ATTRIBUTE* element_attribute , _IN REAL* ESM_element, _OUT ERROR_ID* errorID , _OUT MATRIX_STACKS* S);


    /* //不考虑剪切变形的空间梁单元刚度矩阵计算：compute-space-beam-element-stiffness-matrix
    //输入：梁单元属性（包括E，A，I，l）
    //输出：不考虑剪切变形的空间单元刚度矩阵
    template<typename T1,typename T2>
    MATRIX* Compute_SBES_NS(_IN ELEMENT_ATTRIBUTE* ,_OUT ERROR_ID,_OUT stacks<T1,T2>* S); */


    //前处理第二个模块：坐标转换模块
    //目的：将局部坐标系下的单元刚度矩阵转换为总体坐标系下的单元刚度矩阵。
    //方法：采用SO（3）进行坐标变换

    //计算坐标变换矩阵：compute-coordinate-transfer-matrix
    //输入：梁单元的指针,已分配好空间的数组指针
    //输出：该梁单元的局部坐标转整体坐标的SO（3）矩阵
    MATRIX* Compute_CTM(_IN const ELEMENT* e,_IN REAL* rotation_matrix_element, _IN const MATRIX* ESM, _OUT ERROR_ID* errorID, _OUT MATRIX_STACKS* S);

    //对单元刚度矩阵进行坐标变换的函数：Transform-element-stiffness-matrix
    //输入：该单元的坐标转换矩阵，该单元局部坐标系下的单元刚度矩阵
    //输出：该单元整体坐标系下的单元刚度矩阵
    MATRIX* Transform_ESM(_IN MATRIX* T , _IN MATRIX* ESM, _OUT ERROR_ID* errorID, _OUT MATRIX_STACKS* S);
    

    //前处理第三个模块：总体刚度矩阵形成: component-total-stiffness-matrix
    //目的：组装所有的单元刚度矩阵，形成总体刚度矩阵。
    //方法：采用编码法（自由度编号法）。
    //规则：a = b*(k - 1) + c
    //其中：b = 6;k-节点号；c-节点自由度号,[1-6]。
    //由梁单元两个节点的单刚K12*12^e 组装成总刚 K6NW*6NW
    //等带宽存储，DD=(节点号插值最大+1)*节点自由度号；变带宽存储和一维变带宽存储.目的是减少总刚矩阵在内存中存放的空间。本算例忽略
    //输入：坐标变换后的总体坐标系下的单元刚度矩阵vector数组
    //输出：总体刚度矩阵
    MATRIX* Component_TSM(_IN ELEMENT_STACKS* element_stacks, _OUT ERROR_ID* errorID , _OUT MATRIX_STACKS* S);

    //前处理第四个模块
    //非节点节点载荷计算：compute-no-point-load
    //按照四元载荷等效原理，等效到单元节点载荷，
    //使用C++函数重载，匹配四种载荷的不同输入输出
    //输入：某一单元结构体指针，该单元载荷结构体（四元载荷）指针
    //输出：该单元节点载荷结构体指针
    
    //非节点载荷计算：compute-no-point-load
    //按照四元载荷等效原理，等效到节点载荷，
    //输入：某一单元结构体指针，该单元集中力结构体指针
    //输出：该单元节点载荷结构体指针
    NO_POINT_LOAD* Compute_PL(_IN const ELEMENT* E , _IN CONCENTRATED_FORCE* F , _OUT ERROR_ID* errorID , _OUT POINT_LOAD_STACKS* S);
    
    //非节点载荷计算：compute-no-point-load
    //按照四元载荷等效原理，等效到节点载荷，
    //输入：某一单元结构体指针，该单元集中力矩结构体指针
    //输出：该单元节点载荷结构体指针
    NO_POINT_LOAD* Compute_PL(_IN const ELEMENT* E,CONCENTRATED_MOMENT* M,_OUT ERROR_ID* errorID, _OUT POINT_LOAD_STACKS* S);

    //节点载荷计算：compute-point-load
    //按照四元载荷等效原理，等效到节点载荷，
    //输入：某一单元结构体指针，该单元均布载荷结构体指针
    //输出：该单元节点载荷结构体指针
    NO_POINT_LOAD* Compute_PL(_IN const ELEMENT* E,UNIFORM_LOAD* Q,_OUT ERROR_ID* errorID,_OUT POINT_LOAD_STACKS* S);
    
    //总载荷向量{P}计算: compute-total-load
    //函数名：Compute_TL
    //输入：1.单元栈指针，2.载荷栈指针
    //输出：1.错误变量
    //返回类型：1.总节点载荷向量
    //循环遍历整个单元数组
    //每一次遍历进行如下操作：1.节点载荷直接进行坐标转换，再按照自由度编号法，赋值累加进总节点载荷向量。
    //                      2.非节点载荷先进行等效转换，再进行坐标转换，再按照自由度编号法，赋值累加进总节点载荷向量。
    //最后输出总节点载荷向量。
    TOTAL_LOAD* Compute_TL(_IN const ELEMENT_STACKS* element_stacks,_IN const LOAD_STACKS* load_stacks,_OUT ERROR_ID* errorID);

    //前处理第五个模块
    //在结构整体刚度方程中引入边界条件。一般有限元求解中引入的是位移边界条件。
    //位移边界条件就需要特别注意结构自由度的问题，避免无法求解。
    //选取适当方法求解平衡方程得到节点位移.
    //有两种方法:直接引入法与置大数法。
    //直接引入法：为了保证方程具有唯一解，需要足够的边界条件。
    //引入后，将方程进行处理，消零，整理，最终得到
    //置大数法：和直接引入法不同，这是数值分析中的一种近似解法：
    //该方法无需对刚度矩阵的行和列做任何调整或删去，
    //只要将初始刚度矩阵中已知位移项所对应的主元素乘以一个大系数或用更高数量级的某个大数代替，
    //同时将对应的载荷项作适当的变化，即可直接对方程求解。

    // //已知位移边界条件修改位移向量displacement
    // //输入：初始化的位移向量引用
    // //输出：添加了位移边界条件的位移向量
    // template <typename T>
    // vector<double>& D_ADD_boundary_condition(_IN ,_OUT ERROR_ID* errorID);

    // //总体刚度矩阵引入边界条件
    // //方法：置大数法，n个方程，i行i列主对角元素置大数、右端项修改为大数和已知位移的乘积。
    // //目的：根据约束信息改变相应刚度系数（主元素）和载荷项。
    // //输入：总体刚度矩阵指针，载荷项向量，约束节点的结构体（编号，六个自由度的位移)
    // //输出：引入边界条件后的总体刚度矩阵指针，载荷项向量
    // template <typename T>
    // ERROR_ID TSM_ADD_boundary_condition(_IN MATRIX* K,_IN ,_IN PPOINT_DISPLACEMENT,_OUT ERROR_ID* errorID);

    // //总体刚度矩阵引入边界条件
    // //方法：置大数法，n个方程，i行i列主对角元素置大数、右端项修改为大数和已知位移的乘积。
    // //目的：根据约束信息改变相应刚度系数（主元素）和载荷项。
    // //输入：总体刚度矩阵指针，载荷项向量，约束节点的结构体（编号，六个自由度的位移)vector数组
    // //输出：引入边界条件后的总体刚度矩阵指针，载荷项向量
    // template <typename T>
    // ERROR_ID TSM_ADD_boundary_condition(_IN MATRIX* K,_IN ,_IN vector<PPOINT_DISPLACEMENT>&,_OUT ERROR_ID* errorID);
} //namespace pre

#endif
