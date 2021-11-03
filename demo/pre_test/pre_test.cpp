#include <pre.h>
#include <base.h>
#include <matrix.h>
#include <common.h>
#include <element.h>
#include <point.h>
#include <cstring>

using namespace wwj;

unsigned int NW;//定义总节点数NW
unsigned int NR;//定义受约束的节点总数
unsigned int NU;//定义总单元数NU
unsigned int QQ;//定义总荷载数QQ

int main()
{
    NW = 0;
    NU = 0;
    QQ = 0;
    NR = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;
    MATRIX_STACKS matrix_stacks;
    ELEMENT_STACKS element_stacks;

    init_stack2<MATRIX_NODE,MATRIX_ELEMENT_NODE>(&matrix_stacks);
    init_stack2<ELEMENT_NODE,ELEMENT_ATTRIBUTE_NODE>(&element_stacks);
    
    POINT* p1 = nullptr;
    POINT* p2 = nullptr;
    POINT* p3 = nullptr;

    ELEMENT_ATTRIBUTE_NODE* ea1 = nullptr;
    ELEMENT_ATTRIBUTE_NODE* ea2 = nullptr;

    ELEMENT* e1 = nullptr;
    ELEMENT* e2 = nullptr;
    MATRIX* TSM = nullptr;

    p1 = PtCreate(0 , 5 , 1);
    p2 = PtCreate(5 , 5 , 2);
    p3 = PtCreate(0 , 0 , 3);
    //单位：A:m^2,E:kN/m^2,L:mm,Iz:m^-4
    ea1 = Input_E_A(0.5, 3*pow(10,7), pow(24,-1), 5, &errorID,&element_stacks);
    ea2 = Input_E_A(0.5, 3*pow(10,7), pow(24,-1), 5, &errorID,&element_stacks);

    e1 = Input_E(2, ea1, 1, p1, p2, &errorID, &element_stacks);
    e2 = Input_E(2, ea2, 2, p1, p3, &errorID, &element_stacks);

    TSM = Component_TSM(&element_stacks,&errorID,&matrix_stacks);

    print_matrix(TSM,(char *)"TSM");

    free_stack2<MATRIX_NODE,MATRIX_ELEMENT_NODE>(&matrix_stacks);
    free_stack2<ELEMENT_NODE,ELEMENT_ATTRIBUTE_NODE>(&element_stacks);
    
    PtDestroy(p1);
    PtDestroy(p2);
    PtDestroy(p3);

    system("pause");
    return 0;
}