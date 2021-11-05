/*******************************************************************************
*     File Name :                        common.h
*     Library/Module Name :              MatrixComputation
*     Author :                           Marc Pony(marc_pony@163.com)
*     Create Date :                      2021/6/28
*     Abstract Description :             矩阵运算库公用头文件
*******************************************************************************/

#ifndef  __COMMON_H__
#define  __COMMON_H__
/*******************************************************************************
* (1)Debug Switch Section
*******************************************************************************/


/*******************************************************************************
* (2)Include File Section
*******************************************************************************/
#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

/*******************************************************************************
* (3)Macro Define Section
*******************************************************************************/
#ifndef Macro
#define Macro
#define _IN
#define _OUT
#define _IN_OUT
#define MAX(x,y) (x) > (y) ? (x) : (y)
#define MIN(x,y) (x) < (y) ? (x) : (y)

#define _CRT_SECURE_NO_WARNINGS
#define PI 3.14159265358979323846
#define POSITIVE_INFINITY 999999999
#define NEGATIVE_INFINITY -999999999
#define _ERROR_NO_ERROR		                                        0X00000000   //无错误
#define _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY	                    0X00000001   //分配堆内存失败
#define _ERROR_SVD_EXCEED_MAX_ITERATIONS							0X00000002   //svd超过最大迭代次数
#define _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL	                    0X00000003   //矩阵行数或列数不相等
#define _ERROR_MATRIX_MULTIPLICATION								0X00000004   //矩阵乘法错误(第一个矩阵的列数不等于第二个矩阵行数)
#define _ERROR_MATRIX_MUST_BE_SQUARE								0X00000005   //矩阵必须为方阵
#define _ERROR_MATRIX_NORM_TYPE_INVALID								0X00000006   //矩阵模类型无效
#define _ERROR_MATRIX_EQUATION_HAS_NO_SOLUTIONS						0X00000007   //矩阵方程无解
#define _ERROR_MATRIX_EQUATION_HAS_INFINITY_MANNY_SOLUTIONS	        0X00000008   //矩阵方程有无穷多解
#define _ERROR_QR_DECOMPOSITION_FAILED								0X00000009   //QR分解失败
#define _ERROR_CHOLESKY_DECOMPOSITION_FAILED						0X0000000a   //cholesky分解失败
#define _ERROR_IMPROVED_CHOLESKY_DECOMPOSITION_FAILED				0X0000000b   //improved cholesky分解失败
#define _ERROR_LU_DECOMPOSITION_FAILED								0X0000000c   //LU分解失败
#define _ERROR_CREATE_MATRIX_FAILED									0X0000000d   //创建矩阵失败
#define _ERROR_MATRIX_TRANSPOSE_FAILED								0X0000000e   //矩阵转置失败
#define _ERROR_CREATE_VECTOR_FAILED									0X0000000f   //创建向量失败
#define _ERROR_VECTOR_DIMENSION_NOT_EQUAL 							0X00000010   //向量维数不相同
#define _ERROR_VECTOR_NORM_TYPE_INVALID								0X00000011   //向量模类型无效
#define _ERROR_VECTOR_CROSS_FAILED									0X00000012   //向量叉乘失败
#define _ERROR_PTR_ERROR                    						0X00000013   //指针错误
#define _ERROR_INDEX_ERROR                  						0x00000014   //下标越界
#define _ERROR_NO_FIND_POINT_ERROR                					0x00000015   //未能找到节点
#define _ERROR_INPUT_PARAMETERS_ERROR								0X00010000   //输入参数错误

#endif
/*******************************************************************************
* (4)Struct(Data Types) Define Section
*******************************************************************************/
typedef  unsigned int ERROR_ID;
typedef int INDEX;
typedef short FLAG;
typedef int INTEGER;
typedef double REAL;
typedef char* STRING;

typedef  struct matrix
{
	INTEGER rows;
	INTEGER columns;
	REAL* p;
}MATRIX;

typedef struct matrix_node
{
	MATRIX* ptr;
	struct matrix_node* next;
} MATRIX_NODE;

typedef struct matrix_element_node
{
	REAL* ptr;
	struct matrix_element_node* next;
} MATRIX_ELEMENT_NODE;

template<typename T>
struct stacks1
{
	T* Node;
};

template<typename T1,typename T2>
struct stacks2
{
	T1* Node;
	T2* ElementNode;
};

template<typename T1,typename T2,typename T3,typename T4>
struct stacks4
{
	T1* Node;
	T2* Element1Node;
	T3* Element2Node;
	T4* Element3Node;
};

using MATRIX_STACKS = stacks2<MATRIX_NODE,MATRIX_ELEMENT_NODE>;

/*******************************************************************************
* (5)Prototype Declare Section
*******************************************************************************/
/**********************************************************************************************
Function: init_stack
Description: 初始化栈
Input: 无
Output: 无
Input_Output: 栈指针
Return: 无
Author: Marc Pony(marc_pony@163.com),wwj(bbsy789@126.com)modify
***********************************************************************************************/

template<typename T>
void init_stack1(_IN_OUT stacks1<T>* S)
{
	if (S == nullptr)
	{
		return;
	}

	memset(S, 0, sizeof(stacks1<T>));
}

template<typename T1,typename T2>
void init_stack2(_IN_OUT stacks2<T1,T2>* S)
{
	if (S == nullptr)
	{
		return;
	}

	memset(S, 0, sizeof(stacks2<T1,T2>));
}

template<typename T1,typename T2,typename T3,typename T4>
void init_stack4(_IN_OUT stacks4<T1,T2,T3,T4>* S)
{
	if (S == nullptr)
	{
		return;
	}

	memset(S, 0, sizeof(stacks4<T1,T2,T3,T4>));
}

/**********************************************************************************************
Function: free_stack
Description: 释放栈
Input: 栈指针
Output: 无
Input_Output: 无
Return: 无
Author: Marc Pony(marc_pony@163.com),wwj(bbsy789@126.com)modify
***********************************************************************************************/
template<typename T>
void free_stack1(_IN stacks1<T>* S)
{
	T* Node = nullptr;

	if (S == nullptr)
	{
		return;
	}

	while (S->Node != nullptr)
	{
		Node = S->Node;
		S->Node = Node->next;

		free(Node->ptr);
		Node->ptr = nullptr;
		free(Node);
		Node = nullptr;
	}
}

template<typename T1,typename T2>
void free_stack2(_IN stacks2<T1,T2>* S)
{
	T1* Node = nullptr;
	T2* ElementNode = nullptr;

	if (S == nullptr)
	{
		return;
	}

	while (S->Node != nullptr)
	{
		Node = S->Node;
		S->Node = Node->next;

		free(Node->ptr);
		Node->ptr = nullptr;
		free(Node);
		Node = nullptr;
	}

	while (S->ElementNode != nullptr)
	{
		ElementNode = S->ElementNode;
		S->ElementNode = ElementNode->next;

		free(ElementNode->ptr);
		ElementNode->ptr = nullptr;
		free(ElementNode);
		ElementNode = nullptr;
	}
}

template<typename T1,typename T2,typename T3,typename T4>
void free_stack4(_IN stacks4<T1,T2,T3,T4>* S)
{
	T1* Node = nullptr;
	T2* Element1Node = nullptr;
	T3* Element2Node = nullptr;
	T4* Element3Node = nullptr;
	
	if (S == nullptr)
	{
		return;
	}

	while (S->Node != nullptr)
	{
		Node = S->Node;
		S->Node = Node->next;

		free(Node->ptr);
		Node->ptr = nullptr;
		free(Node);
		Node = nullptr;
	}

	while (S->Element1Node != nullptr)
	{
		Element1Node = S->Element1Node;
		S->Element1Node = Element1Node->next;

		free(Element1Node->ptr);
		Element1Node->ptr = nullptr;
		free(Element1Node);
		Element1Node = nullptr;
	}
	while (S->Element2Node != nullptr)
	{
		Element2Node = S->Element2Node;
		S->Element2Node = Element2Node->next;

		free(Element2Node->ptr);
		Element2Node->ptr = nullptr;
		free(Element2Node);
		Element2Node = nullptr;
	}
	while (S->Element3Node != nullptr)
	{
		Element3Node = S->Element3Node;
		S->Element3Node = Element3Node->next;

		free(Element3Node->ptr);
		Element3Node->ptr = nullptr;
		free(Element3Node);
		Element3Node = nullptr;
	}
}

#endif
