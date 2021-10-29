#include <element.h>

using namespace base;

//梁单元属性的输入:
//输入：平面梁单元属性（包括E，A，I，l）
//输出：平面梁单元属性矩阵指针，错误代码，堆栈指针。
ELEMENT_ATTRIBUTE* Input_E_A(_IN REAL A,_IN REAL E,_IN REAL I,_IN REAL L,_OUT ERROR_ID* errorID,_OUT ELEMENT_ATTRIBUTE_STACKS* S)

    {
        ELEMENT_ATTRIBUTE* element_attribute = nullptr;//定义一个结构体指针，初始化为nullptr
        ELEMENT_ATTRIBUTE_NODE* element_attribute_node = nullptr;

        if(errorID == nullptr)
        {
            return nullptr;//errorID野指针
        }
        
        *errorID = _ERROR_NO_ERROR;
        
        if(A <= 0)
        {
            *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
            return nullptr;//输入参数错误
        }

        element_attribute = (ELEMENT_ATTRIBUTE*)malloc(sizeof(ELEMENT_ATTRIBUTE));//分配内存空间，注意释放
        element_attribute_node = (ELEMENT_ATTRIBUTE_NODE*)malloc(sizeof(ELEMENT_ATTRIBUTE_NODE));

        if(element_attribute == nullptr || element_attribute_node == nullptr)
        {
            free(element_attribute);
            element_attribute == nullptr;
            free(element_attribute_node);
            element_attribute_node = nullptr;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }    
        //赋值
        element_attribute->A = A;
        element_attribute->E = E;
        element_attribute->I = I;
        element_attribute->L = L;
        
        element_attribute_node->data = element_attribute;
        element_attribute_node->next = S->ElementNode;
        S->ElementNode = element_attribute_node;

        return element_attribute;
    }
    
//平面梁单元的输入：
//输入：平面梁单元的属性
//输出：平面梁单元属性指针，错误代码，堆栈指针。
ELEMENT* Input_E(_IN unsigned char NODE_NUMBER,_IN ELEMENT_ATTRIBUTE* attribute,_IN unsigned int index,_IN PPOINT ptri,_IN PPOINT ptrj,_OUT ERROR_ID* errorID,_OUT ELEMENT_STACKS* S)