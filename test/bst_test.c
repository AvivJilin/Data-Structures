#include <stdio.h>

#include "bst.h"
#include "tests.h"

static void TestBST(void);
static int CmpFunc(void *bst_data, void *data_to_match, void *params);


int main(void)
{
    TestBST();
    PASS;
    
    return 0;
}

/******************************************************************************/

static void TestBST(void)
{
    bst_iter_ty iter;
    bst_iter_ty iter2;
    int num = 5;
    int num2 = 10;
    int num3 = 2;
    int num4 = 15;
    int num5 = 12;
    int num6 = 8;
    int num7 = 7;
    int num8 = 9;
    int num9 = 14;
    bst_ty *bst = BSTCreate(CmpFunc, NULL);
    
    if (NULL == bst)
    {
        FAILED;
    }
    else
    {
        TEST("BSTSize", BSTSize(bst), 0);
        TEST("BSTIsEmpty", BSTIsEmpty(bst), 1);
        TEST("BSTIterIsSame", BSTIterIsSame(BSTIterBegin(bst), BSTIterEnd(bst)), 1);
        BSTInsert(bst, &num);
        TEST("BSTSize", BSTSize(bst), 1);
        TEST("BSTIsEmpty", BSTIsEmpty(bst), 0);
        BSTInsert(bst, &num2);
        TEST("BSTSize", BSTSize(bst), 2);
        BSTInsert(bst, &num3);
        TEST("BSTSize", BSTSize(bst), 3);
        BSTInsert(bst, &num4);
        TEST("BSTSize", BSTSize(bst), 4);
        BSTInsert(bst, &num5);
        TEST("BSTSize", BSTSize(bst), 5);
        BSTInsert(bst, &num6);
        TEST("BSTSize", BSTSize(bst), 6);
        BSTInsert(bst, &num7);
        TEST("BSTSize", BSTSize(bst), 7);
        BSTInsert(bst, &num8);
        TEST("BSTSize", BSTSize(bst), 8);
        iter2 = BSTInsert(bst, &num9);
        TEST("BSTSize", BSTSize(bst), 9); 
        iter = BSTFind(bst, &num4);  
        TEST("BSTSize", BSTSize(bst), 9); 
        BSTRemove(iter);
        TEST("BSTSize", BSTSize(bst), 8);
        BSTRemove(iter2);
        TEST("BSTSize", BSTSize(bst), 7);
        BSTDestroy(bst);
    }
}

/******************************************************************************/

static int CmpFunc(void *bst_data, void *data_to_match, void *params)
{
    (void)params;
    
    return (*(int *)bst_data - *(int *)data_to_match);
}
