//定义输入载荷的函数声明
#include <base.h>

namespace wwj
{
    //函数名Input_CONCENTRATED_FORCE重载1
    //输入:无
    //输出:无
    //返回类型:集中力结构体体指针
    LOAD_ELEMENT1_NODE* Input_CONCENTRATED_FORCE(void);

    //函数名Input_CONCENTRATED_FORCE重载2
    //输入:集中力矩的大小,集中力矩距离单元i端的长度
    //输出:无
    //返回类型:集中力结构体体指针
    LOAD_ELEMENT1_NODE* Input_CONCENTRATED_FORCE(_IN double size, _IN double position);

    //下列同理

    LOAD_ELEMENT2_NODE* Input_CONCENTRATED_MOMENT(void);

    LOAD_ELEMENT2_NODE* Input_CONCENTRATED_MOMENT(_IN double size, _IN double position);

    LOAD_ELEMENT3_NODE* Input_UNIFORM_LOAD(void);

    LOAD_ELEMENT3_NODE* Input_UNIFORM_LOAD(_IN double size, _IN double position,_IN double positionj);


}