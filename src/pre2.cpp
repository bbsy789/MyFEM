MATRIX* Compute_PBES_NS(_IN ELEMENT_ATTRIBUTE* element_attribute , _OUT ERROR* errorID , _OUT pre::STACKS* S)
{
    //1.直接计算EA/l，EI/I^3,EI/l^2,EI/l
    double E = element_attribute->E;
    double A = element_attribute->A;
    double L = element_attribute->L;
    double EA_L = E*I/l;
    double EI_L3 = E*I/l/l/l;
    double EI_L2 = E*I/l/l;
    double EI_L = E*I/l;
    //2.定义一个一维数组存放矩阵元素:  1            2            3            4            5            6
    double store_element[6*6] = { EA_L        ,0           ,0           ,-EA_L       ,0            ,0           //1
                                 ,0           ,12*EI_L3    ,6*EI_L2     ,0           ,-12*EI_L3    ,6*EI_L2     //2
                                 ,0           ,6*EI_L2     ,4*EI_L      ,0           ,-6*EI_L2     ,2*EI_L      //3
                                 ,-EA_L       ,0           ,0           ,EA_L        ,0            ,0           //4
                                 ,0           ,-12*EI_L3   ,-6*EI_L2    ,0           ,12*EI_L3     ,-6*EI_L2    //5
                                 ,0           ,6*EI_L2     ,2*EI_L      ,0           ,-6*EI_L2     ,4*EI_L   }; //6
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