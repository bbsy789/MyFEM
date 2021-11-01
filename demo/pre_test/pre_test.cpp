#include <pre.h>
#include <base.h>
#include <matrix.h>
#include <common.h>
#include <element.h>
#include <point.h>

using namespace wwj;

int main()
{
    ERROR_ID errorID = _ERROR_NO_ERROR;
    MATRIX_STACKS matrix_stacks;
    ELEMENT_STACKS element_stacks;

    init_stack2<MATRIX_NODE,MATRIX_ELEMENT_NODE>(&matrix_stacks);
    init_stack1<ELEMENT_NODE>(&element_stacks);

    POINT* p1 = nullptr;
    POINT* p2 = nullptr;
    ELEMENT_ATTRIBUTE* ea1 = nullptr;
    ELEMENT* e1 = nullptr;
    MATRIX* TSM = nullptr;

    p1 = PtCreate(0,0,1);
    p2 = PtCreate(10,0,2);

    ea1 = Input_E_A(10,20000,1000,1000,&errorID);
    e1 = Input_E(2,ea1,1,p1,p2,&errorID,&element_stacks);
    TSM = Component_TSM(e1,&errorID,&matrix_stacks);
    print_matrix(TSM,"TSM:");
    free_stack2<MATRIX_NODE,MATRIX_ELEMENT_NODE>(&matrix_stacks);
    free_stack1<ELEMENT_NODE>(&element_stacks);
}