//提供输入载荷的函数实现
#include <load.h>
#include <base.h>

namespace wwj
{
    //无输入默认无集中力
    void Input_CONCENTRATED_FORCE(_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks)
    {
        if (errorID == nullptr)
	    {
		    return;
	    }
        if(*errorID != _ERROR_NO_ERROR)
        {
            return;
        }
        CONCENTRATED_FORCE* concentrated_force = nullptr;
        LOAD_ELEMENT1_NODE* concentrated_force_node = nullptr;
        
        concentrated_force = (CONCENTRATED_FORCE*)malloc(sizeof(CONCENTRATED_FORCE));
        concentrated_force_node = (LOAD_ELEMENT1_NODE*)malloc(sizeof(LOAD_ELEMENT1_NODE));

        if (concentrated_force == nullptr || concentrated_force_node == nullptr)
        {
            free(concentrated_force);
            concentrated_force = nullptr;
            free(concentrated_force_node);
            concentrated_force_node = nullptr;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }

        concentrated_force->position = 0;
        concentrated_force->size = 0;

        concentrated_force_node->ptr = concentrated_force;
        concentrated_force_node->next = S->Element1Node;
        S->Element1Node = concentrated_force_node;

        return;
    }

    //有载荷则输入参数
    LOAD_ELEMENT1_NODE* Input_CONCENTRATED_FORCE(_IN double size, _IN double position, _IN ELEMENT* E, _OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks)
    {
        if (errorID == nullptr)
	    {
		    return nullptr;
	    }

        if(*errorID != _ERROR_NO_ERROR)
        {
            return nullptr;
        }
        
        *errorID = _ERROR_NO_ERROR;
        if(position < 0 || position > E->attribute->L)
        {
            *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		    return nullptr;
        }
        CONCENTRATED_FORCE* concentrated_force = nullptr;
        LOAD_ELEMENT1_NODE* concentrated_force_node = nullptr;
        
        concentrated_force = (CONCENTRATED_FORCE*)malloc(sizeof(CONCENTRATED_FORCE));
        concentrated_force_node = (LOAD_ELEMENT1_NODE*)malloc(sizeof(LOAD_ELEMENT1_NODE));

        if (concentrated_force == nullptr || concentrated_force_node == nullptr)
        {
            free(concentrated_force);
            concentrated_force = nullptr;
            free(concentrated_force_node);
            concentrated_force_node = nullptr;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }

        concentrated_force->position = position;
        concentrated_force->size = size;

        concentrated_force_node->ptr = concentrated_force;
        concentrated_force_node->next = S->Element1Node;
        S->Element1Node = concentrated_force_node;

        return concentrated_force_node;
    }

    void Input_CONCENTRATED_MOMENT(_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks)
    {
        if (errorID == nullptr)
	    {
		    return nullptr;
	    }
        if(*errorID != _ERROR_NO_ERROR)
        {
            return nullptr;
        }
        CONCENTRATED_MOMENT* concentrated_moment = nullptr;
        LOAD_ELEMENT2_NODE* concentrated_moment_node = nullptr;
        
        concentrated_moment = (CONCENTRATED_MOMENT*)malloc(sizeof(CONCENTRATED_MOMENT));
        concentrated_moment_node = (LOAD_ELEMENT2_NODE*)malloc(sizeof(LOAD_ELEMENT2_NODE));

        if (concentrated_moment == nullptr || concentrated_moment_node == nullptr)
        {
            free(concentrated_moment);
            concentrated_moment = nullptr;
            free(concentrated_moment_node);
            concentrated_moment_node = nullptr;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }

        concentrated_moment->position = 0;
        concentrated_moment->size = 0;

        concentrated_moment_node->ptr = concentrated_moment;
        concentrated_moment_node->next = S->Element2Node;
        S->Element2Node = concentrated_moment_node;

        return concentrated_moment_node;
    }

    LOAD_ELEMENT2_NODE* Input_CONCENTRATED_MOMENT(_IN double size, _IN double position, _IN ELEMENT* E,_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks)
    {
        if (errorID == nullptr)
	    {
		    return nullptr;
	    }

        if(*errorID != _ERROR_NO_ERROR)
        {
            return nullptr;
        }
        
        *errorID = _ERROR_NO_ERROR;
        if(position < 0 || position > E->attribute->L)
        {
            *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		    return nullptr;
        }
        CONCENTRATED_MOMENT* concentrated_moment = nullptr;
        LOAD_ELEMENT2_NODE* concentrated_moment_node = nullptr;
        
        concentrated_moment = (CONCENTRATED_MOMENT*)malloc(sizeof(CONCENTRATED_MOMENT));
        concentrated_moment_node = (LOAD_ELEMENT2_NODE*)malloc(sizeof(LOAD_ELEMENT2_NODE));

        if (concentrated_moment == nullptr || concentrated_moment_node == nullptr)
        {
            free(concentrated_moment);
            concentrated_moment = nullptr;
            free(concentrated_moment_node);
            concentrated_moment_node = nullptr;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }

        concentrated_moment->position = position;
        concentrated_moment->size = size;

        concentrated_moment_node->ptr = concentrated_moment;
        concentrated_moment_node->next = S->Element2Node;
        S->Element2Node = concentrated_moment_node;

        return concentrated_moment_node;
    }

    void Input_UNIFORM_LOAD(_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks)
    {
        if (errorID == nullptr)
	    {
		    return nullptr;
	    }
        if(*errorID != _ERROR_NO_ERROR)
        {
            return nullptr;
        }
        UNIFORM_LOAD* uniform_load = nullptr;
        LOAD_ELEMENT3_NODE* uniform_load_node = nullptr;
        
        uniform_load = (UNIFORM_LOAD*)malloc(sizeof(UNIFORM_LOAD));
        uniform_load_node = (LOAD_ELEMENT3_NODE*)malloc(sizeof(LOAD_ELEMENT3_NODE));

        if (uniform_load == nullptr || uniform_load_node == nullptr)
        {
            free(uniform_load);
            uniform_load = nullptr;
            free(uniform_load_node);
            uniform_load_node = nullptr;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }

        uniform_load->position = 0;
        uniform_load->size = 0;

        uniform_load_node->ptr = uniform_load;
        uniform_load_node->next = S->Element3Node;
        S->Element3Node = uniform_load_node;

        return uniform_load_node;
    }

    LOAD_ELEMENT3_NODE* Input_UNIFORM_LOAD(_IN double size, _IN double positioni,_IN double positionj, _IN ELEMENT* E,_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks)
    {
        if (errorID == nullptr)
	    {
		    return nullptr;
	    }

        if(*errorID != _ERROR_NO_ERROR)
        {
            return nullptr;
        }
        
        *errorID = _ERROR_NO_ERROR;
        if(position < 0 || position > E->attribute->L)
        {
            *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		    return nullptr;
        }
        UNIFORM_LOAD* uniform_load = nullptr;
        LOAD_ELEMENT3_NODE* uniform_load_node = nullptr;
        
        uniform_load = (UNIFORM_LOAD*)malloc(sizeof(UNIFORM_LOAD));
        uniform_load_node = (LOAD_ELEMENT3_NODE*)malloc(sizeof(LOAD_ELEMENT3_NODE));

        if (uniform_load == nullptr || uniform_load_node == nullptr)
        {
            free(uniform_load);
            uniform_load = nullptr;
            free(uniform_load_node);
            uniform_load_node = nullptr;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }

        uniform_load->size = size;
        uniform_load->positioni = positioni;
        uniform_load->positionj = positionj;

        uniform_load_node->ptr = uniform_load;
        uniform_load_node->next = S->Element3Node;
        S->Element3Node = uniform_load_node;

        return uniform_load_node;
    }

    _CRT_STDIO_INLINE int __CRTDECL myscanf(_In_z_ _Scanf_format_string_ char const* const _Format, ...)
    {
        int _Result = 0;
        va_list _ArgList;//va_list 定义参数表
        __crt_va_start(_ArgList, _Format);//va_start

        std::string sFormat = _Format;
        void* ptr = _ArgList;
        int nPos = sFormat.find('%');
        while (nPos != -1) {//遍历参数表，寻找格式化输入参数
            if (sFormat[nPos + 1] == 'f') {
                CONCENTRATED_FORCE** p = (CONCENTRATED_FORCE**)ptr;//p指向当前参数
                (*p)->position = 1;
                (*p)->size = 1;
                ptr = (char*)ptr + sizeof(CONCENTRATED_FORCE**);//更新ptr指针
            }
            else if (sFormat[nPos + 1] == 'm') {
                CONCENTRATED_MOMENT** p = (CONCENTRATED_MOMENT**)ptr;
                (*p)->position = 2;
                (*p)->size = 2;
                ptr = (char*)ptr + sizeof(CONCENTRATED_MOMENT**);
            }
            else if (sFormat[nPos + 1] == 'p') {
                UNIFORM_LOAD** p = (UNIFORM_LOAD**)ptr;
                (*p)->positioni = 3;
                (*p)->positionj = 3;
                (*p)->size = 3;
                ptr = (char*)ptr + sizeof(UNIFORM_LOAD**);
            } //...
            else if (1)
            {

            }
            nPos = sFormat.find('%', nPos + 1);
        }
        __crt_va_end(_ArgList);
        return _Result;   
    }

    //函数名Input_LOAD
    //输入：单元指针
    //输出：错误ID，LOAD栈
    //返回类型：无
    LOAD_NODE* Input_LOAD(_IN ELEMENT* e,_In_z_ _Scanf_format_string_ char const* const _Format, _OUT ERROR_ID* errorID,_OUT LOAD_STACKS* load_stacks)
    {
        if (errorID == nullptr)
	    {
		    return nullptr;
	    }

        if(*errorID != _ERROR_NO_ERROR)
        {
            return nullptr;
        }
        LOAD_ELEMENT1_NODE* load_element1_node = nullptr;
        LOAD_ELEMENT2_NODE* load_element2_node = nullptr;
        LOAD_ELEMENT3_NODE* load_element3_node = nullptr;
        
        load_element1_node = Input_CONCENTRATED_FORCE(errorID,load_stacks);
        if(*errorID == _ERROR_INPUT_PARAMETERS_ERROR)
        {
            printf("输入参数有误！")；
            return nullptr;
        }
        LOAD_ELEMENT2_NODE* load_element2_node = nullptr;
        load_element2_node = Input_CONCENTRATED_MOMENT(errorID,load_stacks);
        if(*errorID == _ERROR_INPUT_PARAMETERS_ERROR)
        {
            printf("输入参数有误！");
            return nullptr;
        } 
        LOAD_ELEMENT3_NODE* load_element3_node = nullptr;
        load_element3_node = Input_UNIFORM_LOAD(errorID,load_stacks);
        if(*errorID == _ERROR_INPUT_PARAMETERS_ERROR)
        {
            printf("输入参数有误！");
            return nullptr;
        }
        
    }
} //namespace wwj