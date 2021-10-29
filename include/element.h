#ifndef _ELEMENT_H
#define _ELEMENT_H

#include <base.h>
#include <common.h>

//element.h
//给出输入单元数据的相关函数的原型

//平面梁单元属性的输入:
//输入：平面梁单元属性（包括E，A，I，l）
//输出：平面梁单元属性矩阵指针，错误代码，堆栈指针。
ELEMENT_ATTRIBUTE* Input_E_A(_IN REAL A,_IN REAL E,_IN REAL I,_IN REAL L,_OUT ERROR_ID* errorID,_OUT ELEMENT_ATTRIBUTE_STACKS* S);

//平面梁单元的输入：
//输入：平面梁单元的属性
//输出：平面梁单元属性指针，错误代码，堆栈指针。
ELEMENT* Input_E(_IN unsigned char NODE_NUMBER,_IN ELEMENT_ATTRIBUTE* attribute,_IN unsigned int index,_IN PPOINT ptri,_IN PPOINT ptrj,_OUT ERROR_ID* errorID,_OUT ELEMENT_STACKS* S);
#endif