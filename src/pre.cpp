#include <pre.h>
#include <matrix.h>

namespace pre
{
        void init_stack(_IN_OUT pre::STACKS* S)
        {
            if (S == NULL)
        	{
		        return;
	        }

	        memset(S, 0, sizeof(pre::STACKS));
        }
        ELEMENT_ATTRIBUTE* Input_E_A(_IN double A,_IN float E,_IN float G,_IN double I,_IN double L,_OUT ERROR_ID* errorID,_OUT pre::STACKS* S)
        {
            pre::STACKS S;
            ELEMENT_ATTRIBUTE* ptr = NULL;//定义一个结构体指针，初始化为NULL

            if(errorID == NULL)
            {
                return NULL;
            }

            ptr = (ELEMENT_ATTRIBUTE*)malloc(sizeof(ELEMENT_ATTRIBUTE));//分配内存空间，注意释放
            if(!ptr)
            {
                //赋值
                ptr->A = A;
                ptr->E = E;
                ptr->G = G;
                ptr->I = I;
                ptr->L = L;
                *errorID = _ERROR_NO_ERROR	;
                
                return ptr;
            }
            else
            {
                free(ptr);
                ptr == NULL;
                *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
		        return NULL;
            }
        }

        MATRIX* Compute_PBES_NS(ELEMENT_ATTRIBUTE* ptr)
        {
            
        }

} // namespace pre

