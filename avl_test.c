#include <stdio.h>

#include "avl.h"
#include "tests.h"
static void TestAVL(void);
static int CmpFunc(void *avl_data, void *data_to_match);
static int AddOne(void *list_data, void *param);

static void TestRemove(void)
{
    int i = 0;
    int data[30] = {10, 20, 30, 15, 25, 40, 45, 55, 34, 2,
                    99, 98, 96, 94, 21, 41, 11, 32, 31, 9,
                    77, 76, 75, 79, 71, 61, 62, 67, 69, 66};
    int found = 71;
    int found2 = 72;
    int found3 = 73;
    int found4 = 74;
     

    avl_ty *avl = AVLCreate(CmpFunc);
    
    for(i = 0; i < 30; ++i)
    {
        AVLInsert(avl, &data[i]);
    }

    TEST("AVLSize", AVLSize(avl), 30);

    TEST("AVLFind", AVLFind(avl, &found), 0);

    AVLForEach(avl, PRE, AddOne, NULL);

    TEST("AVLFindPRE", AVLFind(avl, &found2), 0);

    AVLForEach(avl, IN, AddOne, NULL);

    TEST("AVLFindIN", AVLFind(avl, &found3), 0);

    AVLForEach(avl, POST, AddOne, NULL);

    TEST("AVLFindIN", AVLFind(avl, &found4), 0);

    TEST("AVLFind", AVLFind(avl, &found), 1);

    AVLRemove(avl, &found4);

    TEST("AVLRemove", AVLFind(avl, &found4), 1);

    TEST("AVLSize", AVLSize(avl), 29);
    
    AVLDestroy(avl);
}
static void TestRotate(void)
{
    int data[10] = {100,50,160,150,170,40,180,155,140,130};
    avl_ty *avl = AVLCreate(CmpFunc);

    AVLInsert(avl, &data[0]);
    AVLInsert(avl, &data[1]);
    AVLInsert(avl, &data[2]);
    AVLInsert(avl, &data[3]);
    AVLInsert(avl, &data[4]);
    AVLInsert(avl, &data[5]);
    AVLInsert(avl, &data[6]);
    AVLInsert(avl, &data[7]);
    AVLInsert(avl, &data[8]);  

    TEST("AVLHeight", AVLHeight(avl), 3);

    AVLInsert(avl, &data[9]);

    TEST("AVLHeight", AVLHeight(avl), 3);

    AVLDestroy(avl);
   
}


int main(void)
{
    TestRemove();
    TestAVL();
    TestRotate();
    PASS;
    
    return 0;
}

/******************************************************************************/

static void TestAVL(void)
{

    int num = 5;
    int num2 = 10;
    int num3 = 2;
    int num4 = 15;
    int num5 = 12;
    int num6 = 8;
    int num7 = 7;
    int num8 = 9;
    int num9 = 14;
    avl_ty *avl = AVLCreate(CmpFunc);
    
    if (NULL == avl)
    {
        FAILED;
    }
    else
    {
        TEST("BSTSize", AVLSize(avl), 0);
        TEST("BSTIsEmpty", AVLIsEmpty(avl), 1);
        AVLInsert(avl, &num);
        TEST("BSTSize", AVLSize(avl), 1);
        TEST("BSTIsEmpty", AVLIsEmpty(avl), 0);
        AVLInsert(avl, &num2);
        TEST("BSTSize", AVLSize(avl), 2);
        AVLInsert(avl, &num3);
        TEST("BSTSize", AVLSize(avl), 3);
        AVLInsert(avl, &num4);
        TEST("BSTSize", AVLSize(avl), 4);
        AVLInsert(avl, &num5);
        TEST("BSTSize", AVLSize(avl), 5);
        AVLInsert(avl, &num6);
        TEST("BSTSize", AVLSize(avl), 6);
        AVLInsert(avl, &num7);
        TEST("BSTSize", AVLSize(avl), 7);
        AVLInsert(avl, &num8);
        TEST("BSTSize", AVLSize(avl), 8);
        AVLInsert(avl, &num9);
        TEST("BSTSize", AVLSize(avl), 9); 
        TEST("AVLFind", AVLFind(avl, &num4), 0);
        /*TEST("AVLHeight", AVLHeight(avl), 3);*/

        AVLDestroy(avl);
    }
}

/******************************************************************************/

static int CmpFunc(void *avl_data, void *data_to_match)
{
    
    return (*(int *)avl_data - *(int *)data_to_match);
}

int AddOne(void *list_data, void *param)
{
    int *list_data1 = NULL;
    (void)param;
    list_data1 = list_data;
    ++(*list_data1);
    return 0;   
}
