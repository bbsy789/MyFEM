#include <pre.h>
#include <matrix.h>

namespace pre
{
    template <typename T>
    ELEMENT_ATTRIBUTE* Input_E_A(_IN REAL A,_IN float E,_IN float G,_IN REAL I,_IN REAL L,_OUT ERROR_ID,_OUT stack<T>* S)
    {
        ELEMENT_ATTRIBUTE* element_attribute = NULL;//定义一个结构体指针，初始化为NULL
        ELEMENT_ATTRIBUTE_NODE* element_attribute_node = NULL;

        if(errorID == NULL)
        {
            return NULL;
        }
        
        *errorID = _ERROR_NO_ERROR;
        
        if(A <= 0)
        {
            *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
            return NULL;
        }

        element_attribute = (ELEMENT_ATTRIBUTE*)malloc(sizeof(ELEMENT_ATTRIBUTE));//分配内存空间，注意释放
        element_attribute_node = (ELEMENT_ATTRIBUTE_NODE*)malloc(sizeof(ELEMENT_ATTRIBUTE_NODE));
        if(element_attribute == NULL || element_attribute_node == NULL)
        {
            free(element_attribute);
            element_attribute == NULL;
            free(element_attribute_node);
            element_attribute_node = NULL;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return NULL;
        }    
        //赋值
        element_attribute->A = A;
        element_attribute->E = E;
        element_attribute->G = G;
        element_attribute->I = I;
        element_attribute->L = L;
        element_attribute_node->data = element_attribute;
        element_attribute_node->next = S->element_attribute_node;
        S->element_attribute_node = element_attribute_node;

        return element_attribute;
    }
    template <typename T>
    MATRIX* Compute_PBES_NS(_IN ELEMENT_ATTRIBUTE* element_attribute , _OUT ERROR_ID* errorID , _OUT stack<T>* S)
{
    // 1.直接计算EA/l，EI/I^3,EI/l^2,EI/l
    REAL E = element_attribute->E;
    REAL A = element_attribute->A;
    REAL L = element_attribute->L;
    REAL EA_L = E*I/l;
    REAL EI_L3 = E*I/l/l/l;
    REAL EI_L2 = E*I/l/l;
    REAL EI_L = E*I/l;
    //2.存放矩阵元素:              1            2            3            4            5            6
    REAL store_element[6*6] = {   EA_L        ,0           ,0           ,-EA_L       ,0            ,0           //1
                                 ,0           ,12*EI_L3    ,6*EI_L2     ,0           ,-12*EI_L3    ,6*EI_L2     //2
                                 ,0           ,6*EI_L2     ,4*EI_L      ,0           ,-6*EI_L2     ,2*EI_L      //3
                                 ,-EA_L       ,0           ,0           ,EA_L        ,0            ,0           //4
                                 ,0           ,-12*EI_L3   ,-6*EI_L2    ,0           ,12*EI_L3     ,-6*EI_L2    //5
                                 ,0           ,6*EI_L2     ,2*EI_L      ,0           ,-6*EI_L2     ,4*EI_L   }; //6
    //上述矩阵即为单元刚度矩阵的元素

    //3.定义传入create_matrix的参数
    INTEGER rows = 6;
    INTEGER columns = 6;

    m = create_matrix(rows,columns,errorID,S);//创建一个6X6的矩阵，返回矩阵指针，矩阵节点的指针被压入栈S中

    if(m == NULL) goto EXIT;//错误处理 

    m->p = store_element;
    print_matrix(m, "m");
    *errorID = _ERROR_NO_ERROR;//程序正常执行，无错误
    return m;
    
    EXIT:
    errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;//分配堆内存错误，此时主程序应该调用free_stacks函数释放堆内存防止内存泄露，野指针乱指
    return NULL;
}

} // namespace pre



