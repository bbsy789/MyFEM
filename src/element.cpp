#include <element.h>

namespace wwj
{

    //梁单元属性的输入:
    //输入：平面梁单元属性  (包括E,  A,  I,  l)  
    //输出：平面梁单元属性矩阵指针,  错误代码,  堆栈指针。
    ELEMENT_ATTRIBUTE_NODE *Input_E_A(_IN REAL A, _IN REAL E, _IN REAL I, _IN REAL L, _OUT ERROR_ID *errorID,_OUT ELEMENT_STACKS* S)
    {
        ELEMENT_ATTRIBUTE *element_attribute = nullptr; //定义一个结构体指针,  初始化为nullptr
        ELEMENT_ATTRIBUTE_NODE* element_attribute_node = nullptr;

        if (errorID == nullptr)
        {
            return nullptr; // errorID野指针
        }

        *errorID = _ERROR_NO_ERROR;

        if (A <= 0.0 || E <= 0.0 || I <= 0.0 || L <= 0.0 )
        {
            *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
            return nullptr; //输入参数错误
        }

        element_attribute = (ELEMENT_ATTRIBUTE *)malloc(sizeof(ELEMENT_ATTRIBUTE)); //分配内存空间,  注意释放
        element_attribute_node = (ELEMENT_ATTRIBUTE_NODE*)malloc(sizeof(ELEMENT_ATTRIBUTE_NODE));

        if (element_attribute == nullptr || element_attribute_node == nullptr)
        {
            free(element_attribute);
            element_attribute = nullptr;
            free(element_attribute_node);
            element_attribute_node = nullptr;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }

        //赋值
        element_attribute->A = _IN A;
        element_attribute->E = _IN E;
        element_attribute->I = _IN I;
        element_attribute->L = _IN L;

        element_attribute_node->ptr = element_attribute;
	    element_attribute_node->next = S->ElementNode;
	    S->ElementNode = element_attribute_node;

        return element_attribute_node;
    }

    //平面梁单元的输入：
    //输入：平面梁单元的属性
    //输出： 错误代码,  堆栈指针。
    //返回类型：ELEMENT*
    ELEMENT *Input_E(_IN unsigned char NODE_NUMBER, _IN ELEMENT_ATTRIBUTE_NODE* element_attribute_node, _IN unsigned int index, _IN PPOINT ptri, _IN PPOINT ptrj, _OUT ERROR_ID *errorID, _OUT ELEMENT_STACKS *S)
    {
        ELEMENT * element  = nullptr;
        ELEMENT_NODE * element_node = nullptr;

        if (*errorID != _ERROR_NO_ERROR)
        {
            return nullptr;
        }

        *errorID = _ERROR_NO_ERROR;
        element = (ELEMENT *)malloc(sizeof(ELEMENT)); //分配内存空间,  注意释放
        element_node = (ELEMENT_NODE *)malloc(sizeof(ELEMENT_NODE));

        if (element == nullptr || element_node == nullptr)
        {
            free(element);
            element = nullptr;
            free(element_node);
            element_node = nullptr;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }

        //赋值
        element->attribute   = _IN element_attribute_node->ptr;
        element->index       = _IN index;
        element->NODE_NUMBER = _IN NODE_NUMBER;
        element->ptri        = _IN ptri;
        element->ptrj        = _IN ptrj;

        NU++;

        element_node->ptr = element;
        element_node->next = S->Node;
        S->Node = element_node;

        return element;
    }

    //后续设计类封装后考虑进行模板类实现,  以及运算符重载实现多态。
    /* template<typename T1,typename T2>
    T1 *Input_structtype(_IN T1* struct_ptr, _OUT ERROR_ID *errorID, _OUT stacks<T1,T2> *S)
    {
        T1 * t1 = nullptr; //定义一个结构体指针,  初始化为nullptr
        T2 * t2 = nullptr;

        if (errorID != _ERROR_NO_ERROR)
        {
            return nullptr; // errorID野指针
        }

        *errorID = _ERROR_NO_ERROR;

        t1 = (T1 *)malloc(sizeof(T1)); //分配内存空间,  注意释放
        t2 = (T2 *)malloc(sizeof(T2));

        if (t1 == nullptr || t2 == nullptr)
        {
            free(t1);
            t1 == nullptr;
            free(t2);
            t2 = nullptr;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }
        //赋值需要重载多种 = 运算符


        t2->data = t1;
        t2->next = S->Node;
        S->Node = t2;

        return t1;
    } */
} //namespace wwj