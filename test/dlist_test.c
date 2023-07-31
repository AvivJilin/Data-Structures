#include "dlist.h"
#include "tests.h"


static void TestDlistOnInt(void);
static void TestPushPopFrontAndBack(void);
static void TestSplice(void);
static int Find15(const void *list_data, void *param);
static int AddOne(void *list_data, void *param);

/******************************************************************************/
int main(void)
{

    TestDlistOnInt();
    TestPushPopFrontAndBack();
    TestSplice();
    PASS;
    return 0;
}

static int Find15(const void *list_data, void *param)
{
    int *list_data1 = (int *)list_data;
    (void)param;
    return (15 == *list_data1);
}

static int AddOne(void *list_data, void *param)
{
    int *list_data1 = NULL;
    (void)param;
    list_data1 = list_data;
    ++(*list_data1);
    return 0;   
}

is_match_func_ty my_func = Find15;

action_func_ty myfunc2 = AddOne;

void TestDlistOnInt(void)
{
    dlist_ty *new = NULL;
    dlist_ty *dest = NULL;
    int num = 5;
    int elments[] = {15, 1566, 15, 4, -5};
    void *param = NULL;
    dlist_iter_ty iters[5];
    dlist_iter_ty iter = NULL;
    int *res = NULL;
    size_t i = 0;
    size_t num_of_tests = sizeof(elments) / sizeof(elments[0]);
    new = DlistCreate();
    dest = DlistCreate();
    iter = DlistIterBegin(new);
    TEST("Test DlistIsEmpty", DlistIsEmpty(new), 1);
    while (i < num_of_tests)
    {
        iter = DlistInsert(iter, &elments[i]);
        iter = DlistIterBegin(new);
        iters[i] = DlistIterNext(iter);
        res = (int *)DlistIterGetData(iter);
        TEST("Test SlistInsert/SlistIterGetData", elments[i], *res);
        ++i;

    }
    TEST("Test SlistSizes", DlistSize(new), num_of_tests);
    TEST("Test DlistIsEmpty", DlistIsEmpty(new), 0);
    TEST("Test SlistIterIsEqual", DlistIterIsEqual(iters[1],iters[1]), 1);
    TEST("Test SlistIterIsEqual", DlistIterIsEqual(iters[0],iters[4]), 0);
    iter = DlistFind(DlistIterBegin(new), DlistIterEnd(new), my_func, param);
    res = (int *)DlistIterGetData(iter);
    TEST("Test SlistFind", 15, *res);
    DlistMultiFind(DlistIterBegin(new), DlistIterEnd(new), my_func, param, 
        dest);
    res = (int *)DlistPopBack(dest);
    TEST("Test DlistMultiFind", 15, *res);
    res = (int *)DlistPopBack(dest);
    TEST("Test DlistMultiFind", 15, *res);
    num = DlistForEach(DlistIterBegin(new), DlistIterEnd(new), myfunc2, param);
    TEST("Test SlistForEach", 0, num);
    i = 1;
    iter = DlistIterBegin(new);
    iter = DlistIterNext(iter);
    iter = DlistIterNext(iter);
    iter = DlistIterNext(iter);
    iter = DlistIterNext(iter);
    iter = DlistIterPrev(iter);
    res = (int *)DlistIterGetData(iter);
    TEST("SlistForEach/Next/Prev", 1567, *res);
    while (i < num_of_tests)
    {
        DlistRemove(iters[i]);
        TEST("Test SlistRemove/SlistCount", DlistSize(new), num_of_tests - i);
        ++i;
    }
    TEST("Test SlistCount", DlistSize(new), 1);

    DlistDestroy(new);
    DlistDestroy(dest);

}

void TestPushPopFrontAndBack(void)
{
    dlist_ty *dest;
    int elment = -789;
    int elment1 = 456;
    int elment2 = 123;
    
    dest = DlistCreate();
    
    DlistPushFront(dest, (void *)&elment);
    DlistPushFront(dest, (void *)&elment1);
    DlistPushFront(dest, (void *)&elment2);
    
    printf("DlistPopFront %d \n", *(int *)DlistPopFront(dest));
    printf("DlistIterGetData %d \n",
     *(int *)DlistIterGetData(DlistIterBegin(dest)));
    
    
    TEST("Test DlistSize", 2, DlistSize(dest));
    printf("DlistPopFront %d \n", *(int *)DlistPopFront(dest));
    TEST("Test DlistSize", 1, DlistSize(dest));
    printf("DlistPopFront %d \n", *(int *)DlistPopFront(dest));
    TEST("Test DlistIsEmpty", 1, DlistIsEmpty(dest));

    DlistPushBack(dest, (void *)&elment);
    DlistPushBack(dest, (void *)&elment1);
    DlistPushBack(dest, (void *)&elment2);
    
    printf("DlistPopFront %d \n", *(int *)DlistPopBack(dest));
    printf("DlistIterGetData %d \n",
     *(int *)DlistIterGetData(DlistIterBegin(dest)));
    
    
    TEST("Test DlistSize", 2, DlistSize(dest));
    printf("DlistPopFront %d \n", *(int *)DlistPopBack(dest));
    TEST("Test DlistSize", 1, DlistSize(dest));
    printf("DlistPopFront %d \n", *(int *)DlistPopBack(dest));
    TEST("Test DlistIsEmpty", 1, DlistIsEmpty(dest));
    
    DlistDestroy(dest);
}

void TestSplice(void)
{
    dlist_ty *first_list = DlistCreate();
    dlist_ty *second_list = DlistCreate();

    DlistPushFront(first_list, "Aviv");
    DlistPushFront(first_list, "Lital");
    DlistPushFront(first_list, "Sarit");

    DlistPushFront(second_list, "Nadav");
    DlistPushFront(second_list, "Almog");
    DlistPushFront(second_list, "Eliran");

    DlistSplice(DlistIterBegin(first_list), 
        DlistIterBegin(second_list), DlistIterEnd(second_list));

    TEST("DlistSize", DlistSize(first_list), 6);

    DlistDestroy(first_list);
    DlistDestroy(second_list);
}

