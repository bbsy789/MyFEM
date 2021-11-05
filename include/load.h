//定义输入载荷的函数声明
#include <base.h>

namespace wwj
{
    //函数名Input_CONCENTRATED_FORCE重载1
    //输入:无
    //输出:错误ID，LOAD栈
    //返回类型:集中力结构体体指针
    LOAD_ELEMENT1_NODE* Input_CONCENTRATED_FORCE(_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks);

    //函数名Input_CONCENTRATED_FORCE重载2
    //输入:集中力矩的大小,集中力矩距离单元i端的长度，单元指针
    //输出:错误ID，LOAD栈
    //返回类型:集中力结构体体指针
    LOAD_ELEMENT1_NODE* Input_CONCENTRATED_FORCE(_IN double size, _IN double position,_IN ELEMENT* E,_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks);

    //函数名Input_CONCENTRATED_MOMENT重载1
    //输入:无
    //输出:错误ID，LOAD栈
    //返回类型:集中力结构体体指针
    LOAD_ELEMENT2_NODE* Input_CONCENTRATED_MOMENT(_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks);

    //函数名Input_CONCENTRATED_MOMENT重载2
    //输入:集中力矩的大小,集中力矩距离单元i端的长度，单元指针
    //输出:错误ID，LOAD栈
    //返回类型:集中力结构体体指针
    LOAD_ELEMENT2_NODE* Input_CONCENTRATED_MOMENT(_IN double size, _IN double position,_IN ELEMENT* E,_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks);

    //函数名Input_UNIFORM_LOAD重载1
    //输入:无
    //输出:错误ID，LOAD栈
    //返回类型:集中力结构体体指针
    LOAD_ELEMENT3_NODE* Input_UNIFORM_LOAD(_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks);

    //函数名Input_UNIFORM_LOAD重载2
    //输入:均布载荷的大小,均布载荷距离单元i端的长度，均布载荷距离单元j端的长度，单元指针E
    //输出:错误ID，LOAD栈
    //返回类型:集中力结构体体指针
    LOAD_ELEMENT3_NODE* Input_UNIFORM_LOAD(_IN double size, _IN double positioni,_IN double positionj,_IN ELEMENT* E,_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks);


}