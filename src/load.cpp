//提供输入载荷的函数实现
#include <load.h>
#include <base.h>

namespace wwj
{
    //无输入默认无集中力
    LOAD_ELEMENT1_NODE* Input_CONCENTRATED_FORCE(_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks)
    {
        if (errorID == nullptr)
	    {
		    return nullptr;
	    }
        if(*errorID != _ERROR_NO_ERROR)
        {
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

        concentrated_force->position = 0;
        concentrated_force->size = 0;

        concentrated_force_node->ptr = concentrated_force;
        concentrated_force_node->next = S->Element1Node;
        S->Element1Node = concentrated_force_node;

        return concentrated_force_node;
    }

    //有输入参数则输入参数
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

    LOAD_ELEMENT2_NODE* Input_CONCENTRATED_MOMENT(_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks)
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

    LOAD_ELEMENT3_NODE* Input_UNIFORM_LOAD(_OUT ERROR_ID* errorID, _OUT LOAD_STACKS* load_stacks)
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
} //namespace wwj