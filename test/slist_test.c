
#include "slist.h"
#include "tests.h"


static void TestSlistOnInt(void);
static int Find15(const void *list_data, void *param);
static int AddOne(void *list_data, void *param);

/******************************************************************************/
int main(void)
{

    TestSlistOnInt();
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

static void TestSlistOnInt(void)
{
    slist_ty *new = NULL;
    int num = 5;
    int elments[] = {0, 1566, 15, 4, -5};
    void *param = NULL;
    iter_ty iters[5];
    iter_ty iter = NULL;
    int *res = NULL;
    size_t i = 0;
    size_t num_of_tests = sizeof(elments) / sizeof(elments[0]);
    new = SlistCreate();
    iter = SlistIterBegin(new);
    while (i < num_of_tests)
    {
        iter = SlistInsert(iter, &elments[i]);
        iter = SlistIterBegin(new);
        iters[i] = SlistIterNext(iter);
        res = (int *)SlistIterGetData(iter);
        TEST("Test SlistInsert/SlistIterGetData", elments[i], *res);
        ++i;

    }
    TEST("Test SlistCount", SlistCount(new), num_of_tests);
    TEST("Test SlistIterIsEqual", SlistIterIsEqual(iters[0],iters[0]), 1);
    TEST("Test SlistIterIsEqual", SlistIterIsEqual(iters[0],iters[4]), 0);
    iter = SlistFind(SlistIterBegin(new), SlistIterEnd(new), my_func, param);
    res = (int *)SlistIterGetData(iter);
    TEST("Test SlistFind", 15, *res);
    num = SlistForEach(SlistIterBegin(new), SlistIterEnd(new), myfunc2, param);
    TEST("Test SlistForEach", 0, num);
    i = 1;
    iter = SlistIterBegin(new);
    iter = SlistIterNext(iter);
    iter = SlistIterNext(iter);
    iter = SlistIterNext(iter);
    res = (int *)SlistIterGetData(iter);
    TEST("SlistForEach", 1567, *res);
    SlistIterSetData(iter, &elments[0]);
    res = (int *)SlistIterGetData(iter);
    TEST("SlistIterSetData", 1, *res);
    while (i < num_of_tests)
    {
        SlistRemove(iters[i]);
        TEST("Test SlistRemove/SlistCount", SlistCount(new), num_of_tests - i);
        ++i;
    }
    TEST("Test SlistCount", SlistCount(new), 1);

    SlistDestroy(new);

}




