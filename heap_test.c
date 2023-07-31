#include <stdio.h>

#include "heap.h"
#include "tests.h"


/*****************************Static Functions*********************************/
static void TestHeap(void);
static int CmpFunc(void *var1, void *var2);
static int IsMatch(const void *heap_data, const void *data_to_match);
/******************************************************************************/

int main(void)
{
    TestHeap();

    PASS;
        
    return 0;
}

/*******************************************************************************
*******************************************************************************/

/******************************************************************************/

static void TestHeap(void)
{
    heap_ty *heap = NULL;
    int value1 = 10;
    int value2 = 20;

    heap = HeapCreate(CmpFunc);

    TEST("HeapSize", HeapSize(heap), 0);

    TEST("HeapIsEmpty", HeapIsEmpty(heap), 1);

    TEST("HeapPush", HeapPush(heap, &value1), 0);

    TEST("HeapSize", HeapSize(heap), 1);

    TEST("HeapIsEmpty", HeapIsEmpty(heap), 0);

    TEST("HeapPeek", (*(int *)HeapPeek(heap)), 10);

    TEST("HeapPush", HeapPush(heap, &value2), 0);

    TEST("HeapSize", HeapSize(heap), 2);

    TEST("HeapPeek", (*(int *)HeapPeek(heap)), 20);

    TEST("HeapRemove", HeapRemove(heap, IsMatch, &value2), &value2);

    TEST("HeapPeek", (*(int *)HeapPeek(heap)), 10);

    HeapPop(heap);

    TEST("HeapSize", HeapSize(heap), 0);

    TEST("HeapIsEmpty", HeapIsEmpty(heap), 1);

    HeapDestroy(heap);
}

/******************************************************************************/

static int CmpFunc(void *var1, void *var2)
{
    return *(int *)var1 - *(int *)var2;
}

static int IsMatch(const void *heap_data, const void *data_to_match)
{
    return *(int *)heap_data == *(int *)data_to_match;
}

