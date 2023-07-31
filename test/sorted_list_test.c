#include <stdio.h>
#include <stdlib.h>

#include "sorted_list.h"
#include "tests.h"

static int Find15(const void *list_data, void *param);
static int AddOne(void *list_data, void *param);
static int MyCmp(void *data1, void *data2);
static void TestBasics(void);
static void ShaulTestSortedMerge(void);

int MyCmp(void *data1, void *data2)
{
    return *(int *)data1 - *(int *)data2;
}
int MyCmp2(void *data1, void *data2)
{
    return *(int *)data2 - *(int *)data1;
}


int Find15(const void *list_data, void *param)
{
    int *list_data1 = (int *)list_data;
    (void)param;
    return (15 == *list_data1);
}

int AddOne(void *list_data, void *param)
{
    int *list_data1 = NULL;
    (void)param;
    list_data1 = list_data;
    ++(*list_data1);
    return 0;   
}

is_match_func_ty my_func = Find15;

action_func_ty myfunc2 = AddOne;

cmp_func_ty cmp_func = MyCmp;
cmp_func_ty cmp_func2 = MyCmp2;

int main(void)
{
    TestBasics();
    ShaulTestSortedMerge();
    PASS;

	return 0;
}

void TestBasics(void)
{
    int data_arr[] = { 1,2,3,4,5 };
    int original_arr[] = { 1,2,3,4,5 };
    size_t num_of_tests = sizeof(data_arr) / sizeof(data_arr[0]);
    size_t i = 0;
    sort_list_iter_ty iter;
    int *res = NULL;
    int num = 5;

    sort_list_ty *new_list = SortedListCreate(cmp_func);

    TEST("Test DlistIsEmpty", SortedListIsEmpty(new_list), 1);

    SortedListInsert(new_list, &data_arr[2]);
    SortedListInsert(new_list, &data_arr[1]);
    SortedListInsert(new_list, &data_arr[0]);
    SortedListInsert(new_list, &data_arr[4]);
    SortedListInsert(new_list, &data_arr[3]);

    TEST("Test DlistIsEmpty", SortedListIsEmpty(new_list), 0);
    TEST("SortedListSize", SortedListSize(new_list), num_of_tests);

    num = SortedListForeach(SortedListBegin(new_list), SortedListEnd(new_list), 
                                myfunc2, (void *)NULL);
    TEST("Test SlistForEach", 0, num);

    iter = SortedListBegin(new_list);
    res = (int *)SortedListGetData(iter);
    TEST("Test SlistForEach", original_arr[i] + 1, *res);
    iter = SortedListRemove(iter);
    res = (int *)SortedListGetData(iter);
    TEST("Test SortedListRemove", original_arr[i+1] + 1, *res);
    SortedListInsert(new_list, &data_arr[0]);
    iter = SortedListBegin(new_list);

    for(i = 1; i < num_of_tests-1; ++i)
    {
        
        iter = SortedListNext(iter);
        res = (int *)SortedListGetData(iter);
        TEST("Test SortedListNext/SortedListGetData", original_arr[i] + 1, *res);
    }

    for(i = 0; i < num_of_tests; ++i)
    {
        TEST("PopFront/Insert/Find", original_arr[i] + 1, *(int *)SortedListPopFront(new_list));
    }

    SortedListDestroy(new_list);
}

void ShaulTestSortedMerge(void)
{
    int data_arr1[5] = { 32, 55, 3, 4, 5 };
    int data_arr2[5] = { 6, 7, 88, 8, 9 };

    size_t count = 0;
    size_t i = 0;
    size_t test_cases = sizeof(data_arr1) / sizeof(data_arr1[0]);

    sort_list_ty *dest_list = SortedListCreate(cmp_func2);
    sort_list_ty *src_list = SortedListCreate(cmp_func2);

    
    while(count < test_cases)
    {
        SortedListInsert(dest_list, &data_arr1[count]);
        SortedListInsert(src_list, &data_arr2[count]);
        ++count;
    }

    SortedListMerge(dest_list, src_list);
    for (i = 1; i <= test_cases*2; ++i)
    {
	printf("element %ld = %d\n", i,*(int *)SortedListPopFront(dest_list));
    }
    
    TEST("SortedListSize & Merge", SortedListSize(dest_list), 0);

    SortedListDestroy(dest_list);
}


