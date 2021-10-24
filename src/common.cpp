/*******************************************************************************
*     File Name :                        common.c
*     Library/Module Name :              MatrixComputation
*     Author :                           Marc Pony(marc_pony@163.com)
*     Create Date :                      2021/7/16
*     Abstract Description :            矩阵运算库公用源文件
*******************************************************************************/

/*******************************************************************************
* (1)Debug Switch Section
*******************************************************************************/


/*******************************************************************************
* (2)Include File Section
*******************************************************************************/
#include "common.h"

/*******************************************************************************
* (3)Macro Define Section
*******************************************************************************/


/*******************************************************************************
* (4)Struct(Data Types) Define Section
*******************************************************************************/


/*******************************************************************************
* (5)Prototype Declare Section
*******************************************************************************/


/*******************************************************************************
* (6)Global Variable Declare Section
*******************************************************************************/


/*******************************************************************************
* (7)File Static Variable Define Section
*******************************************************************************/


/*******************************************************************************
* (8)Function Define Section
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
template<typename T1,typename T2>
VOID init_stack(_IN_OUT stacks<T1,T2>* S)
{
	if (S == NULL)
	{
		return;
	}

	memset(S, 0, sizeof(stacks<T1,T2>));
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
template<typename T1,typename T2>
VOID free_stack(_IN stacks<T1,T2>* S)
{
	T1* Node = NULL;
	T2* ElementNode = NULL;

	if (S == NULL)
	{
		return;
	}

	while (S->Node != NULL)
	{
		Node = S->Node;
		S->Node = Node->next;

		free(Node->ptr);
		Node->ptr = NULL;
		free(Node);
		Node = NULL;
	}

	while (S->ElementNode != NULL)
	{
		ElementNode = S->ElementNode;
		S->ElementNode = ElementNode->next;

		free(ElementNode->ptr);
		ElementNode->ptr = NULL;
		free(ElementNode);
		ElementNode = NULL;
	}

	// ...
	// 释放其他指针
}