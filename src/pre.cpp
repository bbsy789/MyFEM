#include <pre.h>
#include <matrix.h>
#include <common.h>
#include <cmath>

namespace wwj
{    
    //不考虑剪切变形的平面梁单元刚度矩阵计算：compute-plan-beam-element-stiffness-matrix-not-shear
    //输入：梁单元属性结构体
    //输出：不考虑剪切变形的平面梁单元刚度矩阵
    MATRIX* Compute_PBES_NS(_IN ELEMENT_ATTRIBUTE* element_attribute , _OUT ERROR_ID* errorID , _OUT MATRIX_STACKS* S)
    {
        if(element_attribute == nullptr)
        {
            *errorID = _ERROR_PTR_ERROR;
            return nullptr;
        }
        // 1.直接计算EA/l，EI/I^3,EI/l^2,EI/l
        const REAL E = element_attribute->E;
        const REAL I = element_attribute->L;
        const REAL A = element_attribute->A;
        const REAL L = element_attribute->L;
        const REAL EA_L = E*I/L;
        const REAL EI_L3 = E*I/pow(L,3);
        const REAL EI_L2 = E*I/pow(L,2);
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
        MATRIX* m = nullptr;

        m = creat_matrix(rows,columns,errorID,S);//创建一个6X6的矩阵，返回矩阵指针，此处矩阵链表已压入栈S中

        if(m == nullptr) goto EXIT;//错误处理 

        m->p = store_element;
        print_matrix(m, "m");
        *errorID = _ERROR_NO_ERROR;//程序正常执行，无错误
        return m;
        
        EXIT:
        *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;//分配堆内存错误，此时主程序应该调用free_stacks函数释放堆内存防止内存泄露，野指针乱指
        return nullptr;
    }

    //计算坐标变换矩阵：compute-coordinate-transfer-matrix
    //输入：梁单元的指针
    //输出：该梁单元的局部坐标转整体坐标的SO（3）矩阵
    MATRIX* Compute_CTM(_IN ELEMENT* e,_OUT ERROR_ID* errorID,_OUT MATRIX_STACKS* S)
    {
        //1.判断野指针
        if(e == nullptr)
        {
            *errorID = _ERROR_PTR_ERROR;
            return nullptr;
        }
        if(e->ptri == nullptr || e->ptrj == nullptr || e->attribute == nullptr)
        {
            *errorID = _ERROR_PTR_ERROR;
            return nullptr;
        }
        //2.计算
        const REAL xi = e->ptri->X;
        const REAL yi = e->ptri->Y;
        const REAL xj = e->ptrj->X;
        const REAL yj = e->ptrj->Y;
        const REAL Le = e->attribute->data->L;
        const REAL a11 = (xj - xi) / Le;
        const REAL a12 = (yj - yi) / Le;
        const REAL a21 = -a12;
        const REAL a22 = a11;

        
        //3.得到旋转矩阵               1            2            3            4            5             6
        REAL store_element[6*6] = {   a11         ,a12         ,0           ,0           ,0            ,0           //1
                                     ,a21         ,a22         ,0           ,0           ,0            ,0           //2
                                     ,0           ,0           ,1           ,0           ,0            ,0           //3
                                     ,0           ,0           ,0           ,a11         ,a12          ,0           //4
                                     ,0           ,0           ,0           ,a21         ,a22          ,0           //5
                                     ,0           ,0           ,0           ,0           ,0            ,1   };      //6

        const INTEGER rows = 6;
        const INTEGER columns = 6;
        MATRIX* Rotation_Matrix = nullptr;
        Rotation_Matrix = creat_matrix(rows,columns,errorID,S);//创建一个6X6的矩阵，返回矩阵指针，矩阵节点的指针被压入栈S中
        if(Rotation_Matrix == nullptr) goto EXIT;//错误处理 

        Rotation_Matrix->p = store_element;
        print_matrix(Rotation_Matrix, "Rotation_Matrix");
        *errorID = _ERROR_NO_ERROR;//程序正常执行，无错误
        return Rotation_Matrix;
        
        EXIT:
        *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;//分配堆内存错误，此时主程序应该调用free_stacks函数释放堆内存防止内存泄露，野指针乱指
        return nullptr;
        }   
    
    //对单元刚度矩阵进行坐标变换的函数：Transform-element-stiffness-matrix
    //输入：该单元的坐标转换矩阵，该单元局部坐标系下的单元刚度矩阵
    //输出：该单元整体坐标系下的单元刚度矩阵
    MATRIX* Transform_ESM(_IN MATRIX* T , _IN MATRIX* ESM, _OUT ERROR_ID* errorID, _OUT MATRIX_STACKS* S)
    {
        //1.创建两个零矩阵存放转换后的矩阵，注意这里分配了内存
        MATRIX* Process_Matrix = nullptr;
        MATRIX* Transformed_Matrix = nullptr;
        const INTEGER rows = 6;
        const INTEGER columns = 6;

        Process_Matrix = creat_zero_matrix(rows,columns,errorID,S);//已入栈
        Transformed_Matrix = creat_zero_matrix(rows,columns,errorID,S);//已入栈

        if(Transformed_Matrix == nullptr || Process_Matrix)
        {
            *errorID = _ERROR_CREATE_MATRIX_FAILED;//创建矩阵失败
            return nullptr;
        }
        //2.执行两步矩阵乘法，分别用变换矩阵左乘和右乘单元刚度矩阵
        *errorID = matrix_multiplication(T,ESM,Process_Matrix);
        if(*errorID == _ERROR_INPUT_PARAMETERS_ERROR || *errorID == _ERROR_INPUT_PARAMETERS_ERROR)
        {
            return nullptr;
        }
        *errorID = matrix_multiplication(Process_Matrix,T,Transformed_Matrix);
        if(*errorID == _ERROR_INPUT_PARAMETERS_ERROR || *errorID == _ERROR_INPUT_PARAMETERS_ERROR)
        {
            return nullptr;
        }
        //返回变换后的矩阵
        return Transformed_Matrix;
    }
    
    //前处理第三个模块：总体刚度矩阵形成: component-total-stiffness-matrix
    //目的：组装所有的单元刚度矩阵，形成总体刚度矩阵。
    //方法：采用编码法（自由度编号法）。
    //规则：a = b*(k - 1) + c
    //其中：b = 6;k-节点号；c-节点自由度号,[1-6]。
    //由梁单元两个节点的单刚K12*12^e 组装成总刚 K6NW*6NW
    //等带宽存储，DD=(节点号插值最大+1)*节点自由度号；变带宽存储和一维变带宽存储.目的是减少总刚矩阵在内存中存放的空间。本算例忽略
    //输入：坐标变换后的总体坐标系下的单元刚度矩阵vector数组
    //输出：总体刚度矩阵
    MATRIX* Component_TSM(_IN ELEMENT* E , _OUT ERROR_ID* errorID , _OUT MATRIX_STACKS* S)
    {
            //1.创建零矩阵矩阵，行列数位节点数的3倍。
            MATRIX* TSM = nullptr;//定义总体刚度矩阵的结构体指针
            INTEGER rows = 3 * NW;//定义总体刚度矩阵的行数
            INTEGER columns = 3 * NW;//定义总体刚度矩阵的列数

            MATRIX* matrix_ptr = nullptr;//定义指向单元刚度矩阵的指针
            REAL* matrix_element_ptr = nullptr;//定义指向单元刚度矩阵元素的指针
            REAL* TSM_element_ptr = nullptr;//定义指向总体刚度矩阵元素的指针

            //2.创建总体刚度矩阵，零矩阵，检查TSM指针
            
            TSM = creat_zero_matrix(rows,columns,errorID,S);//已入栈
            if(TSM == nullptr || TSM->p == nullptr)
            {
                *errorID = _ERROR_CREATE_MATRIX_FAILED;
                return nullptr;
            }
            //3.创建单元刚度矩阵并转换为整体坐标系下的单元刚度矩阵再成整体坐标系下的总刚度矩阵。
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
            for(int n = 1 ; n <= NW ; n++)
            {
                //1.创建单元刚度矩阵                
                matrix_ptr = Compute_PBES_NS(((E + n - 1)->attribute->data),errorID,S);//入栈
                if( matrix_ptr == nullptr || matrix_ptr->p == nullptr)
                {
                    *errorID = _ERROR_CREATE_MATRIX_FAILED;
                    return nullptr;
                }
                matrix_element_ptr = matrix_ptr->p;//得到单元刚度矩阵的元素指针
                TSM_element_ptr = TSM->p;//得到总体刚度矩阵的元素指针
                
                //2.取Kii分块矩阵，也就是单元刚度矩阵的左上角矩阵。
                for(int i = 1 ; i <= 3 ; i++)
                {
                    unsigned int i_index = (E + n - 1)->ptri->index;
                    for(int j = 1 ; j <= 3 ; j++ )
                    {
                        unsigned int j_index = (E + n - 1)->ptrj->index;
                        *( TSM_element_ptr + 12 * i_index * NW - 12 * NW + 4 * i_index - 4 ) 
                        = *( matrix_element_ptr + 6 * i + j - 7 );//核心算法
                        j_index++;
                    } 
                    i_index++;
                }
                
                //3.取Kij分块矩阵，也就是单元刚度矩阵的右上角矩阵。
                for(int i = 1 ; i <= 3 ; i++)
                {
                    unsigned int i_index = (E + n - 1)->ptri->index;
                    for(int j = 1 ; j <= 3 ; j++ )
                    {
                        unsigned int j_index = (E + n - 1)->ptrj->index;
                        *( TSM_element_ptr + 12 * j_index * NW - 12 * NW + 4 * i_index - 4 ) 
                        = *( matrix_element_ptr + 6 * i + j - 7 );//核心算法
                        j_index++;
                    } 
                    i_index++;
                }

                //4.取Kji分块矩阵，也就是单元刚度矩阵的左下角矩阵。
                for(int i = 1 ; i <= 3 ; i++)
                {
                    unsigned int i_index = (E + n - 1)->ptri->index;
                    for(int j = 1 ; j <= 3 ; j++ )
                    {
                        unsigned int j_index = (E + n - 1)->ptrj->index;
                        *( TSM_element_ptr + 12 * i_index * NW - 12 * NW + 4 * j_index - 4 ) 
                        = *( matrix_element_ptr + 6 * i + j - 7 );//核心算法
                        j_index++;
                    } 
                    i_index++;
                }

                //5.取Kjj分块矩阵，也就是单元刚度矩阵的右下角矩阵。
                for(int i = 1 ; i <= 3 ; i++)
                {
                    unsigned int i_index = (E + n - 1)->ptri->index;
                    for(int j = 1 ; j <= 3 ; j++ )
                    {
                        unsigned int j_index = (E + n - 1)->ptrj->index;
                        *( TSM_element_ptr + 12 * j_index * NW - 12 * NW + 4 * j_index - 4 ) 
                        = *( matrix_element_ptr + 6 * i + j - 7 );//核心算法
                        j_index++;
                    } 
                    i_index++;
                }
                //这里需要调整栈指针（出栈）！！！！！！！！！10.28还未实现
                //出栈后释放内存
                free(matrix_element_ptr);
                matrix_element_ptr = nullptr;
                free(matrix_ptr);//赋值完毕立刻释放
                matrix_ptr = nullptr;//每次循环结束变为nullptr
            }
            *errorID = _ERROR_NO_ERROR;
            return TSM;
    }
    
    //节点载荷计算：compute-point-load
    //按照四元载荷等效原理，等效到节点载荷，
    //输入：某一单元结构体指针，该单元集中力结构体指针
    //输出：该单元节点载荷结构体指针
    NO_POINT_LOAD* Compute_PL(_IN ELEMENT* E , _IN CONCENTRATED_FORCE* F , _OUT ERROR_ID* errorID , _OUT NO_POINT_LOAD_STACKS* S)
    {
        double L = E->attribute->data->L;//取单元长度
        double P = F->size;//取集中力大小
        double a = F->position;//取集中力距离i端的长度
        double b = L - a;
        
        double qeix = 0;
        double qeiy = -P*b*b*(L+2*a)/pow(L,3);
        double qei  = -P*a*b*b/pow(L,2);
        double qejx = 0;
        double qejy = -P*a*a*(L+2*b)/pow(L,3);
        double qej  = -P*a*a*b/pow(L,2);
        
        NO_POINT_LOAD* no_point_load = nullptr;
        NO_POINT_LOAD_NODE* no_point_load_node = nullptr;
        
        no_point_load = (NO_POINT_LOAD*)malloc(sizeof(NO_POINT_LOAD));
        no_point_load_node = (NO_POINT_LOAD_NODE*)malloc(sizeof(NO_POINT_LOAD_NODE));
        
        if(no_point_load == nullptr || no_point_load_node == nullptr)
        {
            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }
        
        no_point_load->ui = qeix;
        no_point_load->vi = qeiy;
        no_point_load->thetai = qei;
        no_point_load->uj = qejx;
        no_point_load->vj = qejy;
        no_point_load->thetaj = qej;
        
        no_point_load_node->data = no_point_load;
        no_point_load_node->next = S->Node;
        S->Node = no_point_load_node;

        return no_point_load;
    }

    //节点载荷计算：compute-point-load
    //按照四元载荷等效原理，等效到节点载荷，
    //输入：某一单元结构体指针，该单元集中力矩结构体指针
    //输出：该单元节点载荷结构体指针
    NO_POINT_LOAD* Compute_PL(_IN ELEMENT* E,CONCENTRATED_MOMENT* CM,_OUT ERROR_ID* errorID, _OUT NO_POINT_LOAD_STACKS* S)
    {
        double L = E->attribute->data->L;///取单元长度
        double M = CM->size;//取集中力矩大小
        double a = CM->position;//取集中力距离i端的长度
        double b = L - a;
        
        double qeix = 0;
        double qeiy = 6*a*b*M/pow(L,3);
        double qei  = -b*(3*a-L)*M/pow(L,2);
        double qejx = 0;
        double qejy = -qeiy;
        double qej  = -a*(3*b-L)*M/pow(L,2);
        
        NO_POINT_LOAD* no_point_load = nullptr;
        NO_POINT_LOAD_NODE* no_point_load_node = nullptr;
        
        no_point_load = (NO_POINT_LOAD*)malloc(sizeof(NO_POINT_LOAD));
        no_point_load_node = (NO_POINT_LOAD_NODE*)malloc(sizeof(NO_POINT_LOAD_NODE));
        
        if(no_point_load == nullptr || no_point_load_node == nullptr)
        {
            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }
        
        no_point_load->ui = qeix;
        no_point_load->vi = qeiy;
        no_point_load->thetai = qei;
        no_point_load->uj = qejx;
        no_point_load->vj = qejy;
        no_point_load->thetaj = qej;
        
        no_point_load_node->data = no_point_load;
        no_point_load_node->next = S->Node;
        S->Node = no_point_load_node;

        return no_point_load;
    }

    //节点载荷计算：compute-point-load
    //按照四元载荷等效原理，等效到节点载荷，
    //输入：某一单元结构体指针，该单元均布载荷结构体指针
    //输出：该单元节点载荷结构体指针
    NO_POINT_LOAD* Compute_PL(_IN ELEMENT* E,UNIFORM_LOAD* Q,_OUT ERROR_ID* errorID,_OUT NO_POINT_LOAD_STACKS* S)
     {
        double L = E->attribute->data->L;///取单元长度
        double q = Q->size;//取均布载荷大小
        double Li = Q->positioni;//取集中力距离i端的长度
        double Lj = Q->positionj;//取集中力距离i端的长度
        double a = L - Lj;//默认Li = 0
        double b = Lj;
        
        double qeix = 0;
        double qeiy = -q*a*(2*pow(L,3)-2*L*pow(a,2)+pow(a,3))/pow(L,3);
        double qei  = -q*pow(a,2)*(6*pow(L,2)-8*a*L+3*pow(a,2))/12/pow(L,2);
        double qejx = 0;
        double qejy = -q*pow(a,3)*(2*L - a)/2/pow(L,3);
        double qej  = q*pow(a,3)*(4*L - 3*a)/12/pow(L,2);
        
        NO_POINT_LOAD* no_point_load = nullptr;
        NO_POINT_LOAD_NODE* no_point_load_node = nullptr;
        
        no_point_load = (NO_POINT_LOAD*)malloc(sizeof(NO_POINT_LOAD));
        no_point_load_node = (NO_POINT_LOAD_NODE*)malloc(sizeof(NO_POINT_LOAD_NODE));
        
        if(no_point_load == nullptr || no_point_load_node == nullptr)
        {
            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return nullptr;
        }
        
        no_point_load->ui = qeix;
        no_point_load->vi = qeiy;
        no_point_load->thetai = qei;
        no_point_load->uj = qejx;
        no_point_load->vj = qejy;
        no_point_load->thetaj = qej;
        
        no_point_load_node->data = no_point_load;
        no_point_load_node->next = S->Node;
        S->Node = no_point_load_node;

        return no_point_load;
    }
} //namespace wwj

