#include <pre.h>
#include <base.h>
#include <matrix.h>
#include <common.h>
#include <element.h>
#include <point.h>

using namespace wwj;

unsigned int NW;//�����ܽڵ���NW
unsigned int NR;//������Լ���Ľڵ�����
unsigned int NU;//�����ܵ�Ԫ��NU
unsigned int QQ;//�����ܺ�����QQ


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
    init_stack1<ELEMENT_NODE>(&element_stacks);

    POINT* p1 = nullptr;
    POINT* p2 = nullptr;
    POINT* p3 = nullptr;

    ELEMENT_ATTRIBUTE* ea1 = nullptr;
    ELEMENT_ATTRIBUTE* ea2 = nullptr;

    ELEMENT* e1 = nullptr;
    ELEMENT* e2 = nullptr;
    MATRIX* TSM = nullptr;

    p1 = PtCreate(0 , 5 , 1);
    p2 = PtCreate(5 , 5 , 2);
    p3 = PtCreate(0 , 0 , 3);
    //单位：A:m^2,E:kN/m^2,L:mm,Iz:m^-4
    ea1 = Input_E_A(0.5, 3*pow(10,7), pow(24,-1), 5, &errorID);
    ea2 = Input_E_A(0.5, 3*pow(10,7), pow(24,-1), 5, &errorID);

    e1 = Input_E(2, ea1, 1, p1, p2, &errorID, &element_stacks);
    e2 = Input_E(2, ea2, 2, p3, p1, &errorID, &element_stacks);

    TSM = Component_TSM(&element_stacks,&errorID,&matrix_stacks);
    print_matrix(TSM,"TSM");

    free_stack2<MATRIX_NODE,MATRIX_ELEMENT_NODE>(&matrix_stacks);
    free_stack1<ELEMENT_NODE>(&element_stacks);
    system("pause");
    return 0;
}