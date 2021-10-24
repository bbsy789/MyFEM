#include <pre.h>
#include <matrix.h>

namespace pre
{
    template <typename T>
    void init_stack(_IN_OUT pre::STACKS<T>* S)
    {

    }

    template <typename T>
    void free_stack(_IN pre::STACKS<T>* S)
    {

    }
    template <typename T>
    ELEMENT_ATTRIBUTE* Input_E_A(_IN double A,_IN float E,_IN float G,_IN double I,_IN double L,_OUT ERROR_ID,_OUT pre::STACKS<T>* S)
    {
        ELEMENT_ATTRIBUTE* element_attribute = NULL;//定义一个结构体指针，初始化为NULL
        ELEMENT_ATTRIBUTE_NODE* element_attribute_node = NULL;
        double land = 0;

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

    MATRIX* Compute_PBES_NS(_IN ELEMENT_ATTRIBUTE* element_attribute,_OUT ERROR_ID* error_ID,_OUT pre::STACKS* S)
    {
        
    }

} // namespace pre

MATRIX* Compute_PBES_NS(ELEMENT_ATTRIBUTE* )
{
    
}

