#include <pre.h>
#include <matrix.h>

namespace pre
{
    ELEMENT_ATTRIBUTE* Input_E_A(_IN REAL A,_IN REAL E,_IN REAL I,_IN REAL L,_OUT ERROR_ID* errorID,_OUT ELEMENT_ATTRIBUTE_STACKS* S)
    {
        ELEMENT_ATTRIBUTE* element_attribute = NULL;//定义一个结构体指针，初始化为NULL
        ELEMENT_ATTRIBUTE_NODE* element_attribute_node = NULL;

        if(errorID == NULL)
        {
            return NULL;//errorID野指针
        }
        
        *errorID = _ERROR_NO_ERROR;
        
        if(A <= 0)
        {
            *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
            return NULL;//输入参数错误
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
        element_attribute->I = I;
        element_attribute->L = L;
        
        element_attribute_node->data = element_attribute;
        element_attribute_node->next = S->ElementNode;
        S->ElementNode = element_attribute_node;

        return element_attribute;
    }

    MATRIX* Compute_PBES_NS(_IN ELEMENT_ATTRIBUTE* element_attribute , _OUT ERROR_ID* errorID , _OUT MATRIX_STACKS* S)
    {
        if(element_attribute == NULL)
        {
            *errorID = _ERROR_PTR_ERROR;
            return NULL;
        }
        // 1.直接计算EA/l，EI/I^3,EI/l^2,EI/l
        const REAL E = element_attribute->E;
        const REAL I = element_attribute->L;
        const REAL A = element_attribute->A;
        const REAL L = element_attribute->L;
        const REAL EA_L = E*I/L;
        const REAL EI_L3 = E*I/L/L/L;
        const REAL EI_L2 = E*I/L/L;
        const REAL EI_L = E*I/L;
        //2.存放矩阵元素:              1            2            3            4            5             6
        REAL store_element[6*6] = {  EA_L        ,0           ,0           ,-EA_L       ,0            ,0           //1
                                    ,0           ,12*EI_L3    ,6*EI_L2     ,0           ,-12*EI_L3    ,6*EI_L2     //2
                                    ,0           ,6*EI_L2     ,4*EI_L      ,0           ,-6*EI_L2     ,2*EI_L      //3
                                    ,-EA_L       ,0           ,0           ,EA_L        ,0            ,0           //4
                                    ,0           ,-12*EI_L3   ,-6*EI_L2    ,0           ,12*EI_L3     ,-6*EI_L2    //5
                                    ,0           ,6*EI_L2     ,2*EI_L      ,0           ,-6*EI_L2     ,4*EI_L   }; //6
        //上述矩阵即为单元刚度矩阵的元素

        //3.定义传入create_matrix的参数
        const INTEGER rows = 6;
        const INTEGER columns = 6;
        MATRIX* m = NULL;

        m = creat_matrix(rows,columns,errorID,S);//创建一个6X6的矩阵，返回矩阵指针，此处矩阵链表已压入栈S中

        if(m == NULL) goto EXIT;//错误处理 

        m->p = store_element;
        print_matrix(m, "m");
        *errorID = _ERROR_NO_ERROR;//程序正常执行，无错误
        return m;
        
        EXIT:
        *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;//分配堆内存错误，此时主程序应该调用free_stacks函数释放堆内存防止内存泄露，野指针乱指
        return NULL;
    }
    MATRIX* Compute_CTM(_IN ELEMENT* e,_OUT ERROR_ID* errorID,_OUT MATRIX_STACKS* S)
    {
        //1.判断野指针
        if(e == NULL)
        {
            *errorID = _ERROR_PTR_ERROR;
            return NULL;
        }
        if(e->ptri == NULL || e->ptrj == NULL || e->attribute == NULL)
        {
            *errorID = _ERROR_PTR_ERROR;
            return NULL;
        }
        //2.计算
        const REAL xi = e->ptri->X;
        const REAL yi = e->ptri->Y;
        const REAL xj = e->ptrj->X;
        const REAL yj = e->ptrj->Y;
        const REAL Le = e->attribute->L;
        const REAL a11 = (xj - xi) / Le;
        const REAL a12 = (yj - yi) / Le;
        const REAL a21 = -a12;
        const REAL a22 = a11;

        
        //3.得到旋转矩阵                1            2            3            4            5             6
        REAL store_element[6*6] = {   a11         ,a12         ,0           ,0           ,0            ,0           //1
                                     ,a21         ,a22         ,0           ,0           ,0            ,0           //2
                                     ,0           ,0           ,1           ,0           ,0            ,0           //3
                                     ,0           ,0           ,0           ,a11         ,a12          ,0           //4
                                     ,0           ,0           ,0           ,a21         ,a22          ,0           //5
                                     ,0           ,0           ,0           ,0           ,0            ,1   };      //6

        const INTEGER rows = 6;
        const INTEGER columns = 6;
        MATRIX* Rotation_Matrix = NULL;
        Rotation_Matrix = creat_matrix(rows,columns,errorID,S);//创建一个6X6的矩阵，返回矩阵指针，矩阵节点的指针被压入栈S中
        if(Rotation_Matrix == NULL) goto EXIT;//错误处理 

        Rotation_Matrix->p = store_element;
        print_matrix(Rotation_Matrix, "Rotation_Matrix");
        *errorID = _ERROR_NO_ERROR;//程序正常执行，无错误
        return Rotation_Matrix;
        
        EXIT:
        *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;//分配堆内存错误，此时主程序应该调用free_stacks函数释放堆内存防止内存泄露，野指针乱指
        return NULL;
        }   
    
    MATRIX* Transform_ESM(_IN MATRIX* T , _IN MATRIX* ESM, _OUT ERROR_ID* errorID, _OUT MATRIX_STACKS* S)
    {
        //1.创建两个零矩阵存放转换后的矩阵，注意这里分配了内存
        MATRIX* Process_Matrix = NULL;
        MATRIX* Transformed_Matrix = NULL;
        const INTEGER rows = 6;
        const INTEGER columns = 6;

        Process_Matrix = creat_zero_matrix(rows,columns,errorID,S);//已入栈
        Transformed_Matrix = creat_zero_matrix(rows,columns,errorID,S);//已入栈

        if(Transformed_Matrix == NULL || Process_Matrix)
        {
            *errorID = _ERROR_CREATE_MATRIX_FAILED;//创建矩阵失败
            return NULL;
        }
        //2.执行两步矩阵乘法，分别用变换矩阵左乘和右乘单元刚度矩阵
        *errorID = matrix_multiplication(T,ESM,Process_Matrix);
        if(*errorID == _ERROR_INPUT_PARAMETERS_ERROR || *errorID == _ERROR_INPUT_PARAMETERS_ERROR)
        {
            return NULL;
        }
        *errorID = matrix_multiplication(Process_Matrix,T,Transformed_Matrix);
        if(*errorID == _ERROR_INPUT_PARAMETERS_ERROR || *errorID == _ERROR_INPUT_PARAMETERS_ERROR)
        {
            return NULL;
        }
        //返回变换后的矩阵
        return Transformed_Matrix;
    }
    
    MATRIX* Component_TSM(_IN vector<ELEMENT*> E)
        {
            //1.创建零矩阵矩阵，行列数位节点数的3倍。
            MATRIX* TSM = NULL;//定义总体刚度矩阵的结构体指针
            INTEGER rows = 3 * NW;//定义总体刚度矩阵的行数
            INTEGER columns = 3 * NW;//定义总体刚度矩阵的列数

            REAL* matrix_element_ptr = NULL;//定义指向矩阵元素的头地址的指针
            unsigned int element_index = 0;//单元号
            unsigned int i_index = 0;
            unsigned int j_index = 0;

            TSM = creat_zero_matrix(rows,columns,errorID,S);//已入栈

            //2.组装矩阵。
            //假设元素为i行j列，
            //提取左上角3*3矩阵Kii元素的数组下标即为：6 * (i - 1) + j - 1 = 6 * i + j - 7(此式也是提取矩阵任意元素的公式)
            //提取右上角3*3矩阵Kij元素的数组下标即为：6 * (i - 1) + (j + 3) - 1 = 6 * i + j - 4
            //提取左下角3*3矩阵Kji元素的数组下标即为：6 * (i + 3 - 1) + (j + 3) - 1 = 6 * i + j + 11
            //提取右下角3*3矩阵Kjj元素的数组下标即为：6 * (i + 3 - 1) + (j + 3) - 1 = 6 * i + j - 10
            //提取总体刚度矩阵的数组下标即为：(3 * NW) * (B - 1) + C - 1
            //式中:
            //当取左上角分块矩阵Ki_indexi_index时：B = 4*i_index -3 , C = 4*i_index-3
            //当取右上角分块矩阵Ki_indexj_index时：B = 4*j_index -3 , C = 4*i_index-3
            //当取左下角分块矩阵Kj_indexi_index时：B = 4*i_index -3 , C = 4*j_index-3
            //当取右下角分块矩阵Kj_indexj_index时：B = 4*j_index -3 , C = 4*j_index-3
            //分别带入后可得，映射函数为：
            //Ki_indexi_index:12 * i_index * NW - 12 * NW + 4 * i_index - 4
            //Ki_indexj_index:12 * j_index * NW - 12 * NW + 4 * i_index - 4
            //Kj_indexi_index:12 * i_index * NW - 12 * NW + 4 * j_index - 4
            //Kj_indexj_index:12 * j_index * NW - 12 * NW + 4 * j_index - 4           
            //Vscode部分替换方法：1.选中区域，2.cmd+opt+L
            //第n个单元的左上角矩阵
            for(n = 1;n <= NW;i++)
            {
                //1.取单元号
                element_index = E[n-1]->index;
                //2.取节点号
                i_index = E[n-1]->ptri->index;
                j_index = E[n-1]->ptrj->index;
                
                matrix_element_ptr = NULL;//每次循环变为NULL
                matrix_element_ptr = E[n-1]->ESM->p;//取矩阵的元素的地址
                TSM_element_ptr = TSM->p;

                //3.取Kii分块矩阵，也就是单元刚度矩阵的左上角矩阵。
                for(int i = 1 ;i <= 3 ; i++)
                {
                    for(int j = 1;j <= 3 ; j++)
                    {
                        *( TSM_element_ptr + 12 * i_index * NW - 12 * NW + 4 * i_index - 4 ) 
                        = *( matrix_element_ptr + 6 * i + j - 7 );//核心算法
                    } 
                }
                
                //4.取Kij分块矩阵，也就是单元刚度矩阵的右上角矩阵。
                for(int i = 1 ;i <= 3 ; i++)
                {
                    for(int j = 1;j <= 3 ; j++)
                    {
                        *( TSM_element_ptr + 12 * j_index * NW - 12 * NW + 4 * i_index - 4 ) 
                        = *( matrix_element_ptr + 6 * i + j - 7 );//核心算法
                    } 
                }

                //5.取Kji分块矩阵，也就是单元刚度矩阵的左下角矩阵。
                for(int i = 1 ;i <= 3 ; i++)
                {
                    for(int j = 1;j <= 3 ; j++)
                    {
                        *( TSM_element_ptr + 12 * i_index * NW - 12 * NW + 4 * j_index - 4 ) 
                        = *( matrix_element_ptr + 6 * i + j - 7 );//核心算法
                    } 
                }

                //6.取Kjj分块矩阵，也就是单元刚度矩阵的右下角矩阵。
                for(int i = 1 ;i <= 3 ; i++)
                {
                    for(int j = 1;j <= 3 ; j++)
                    {
                        *( TSM_element_ptr + 12 * j_index * NW - 12 * NW + 4 * j_index - 4 ) 
                        = *( matrix_element_ptr + 6 * i + j - 7 );//核心算法
                    } 
                }

            }
            return TSM;
        }
} // namespace pre



