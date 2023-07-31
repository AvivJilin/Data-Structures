#include <stddef.h>     /*  size_t      */
#include <stdlib.h>     /*  rand, qsort */
#include <time.h>       /*  clock       */

#include "comparisonlinearsort.h"
#include "tests.h"

#define ARR_SIZE 5000

/*****************************Static Functions*********************************/

static void InitArr(int *arr);
static void InitArrCounting(int *arr);
static void InitArrRadix(int *arr);
static int IsSorted(int *arr);
static void TestBubbleSort(void);
static void TestSelectionSort(void);
static void TestInsertionSort(void);
static void TestCountingSort(void);
static void TestRadixSort(void);
static void TestRuntime(void);
static int CmpFunc(const void *var1, const void *var2);

/******************************************************************************/

int main(void)
{
    TestBubbleSort();
    TestSelectionSort();
    TestInsertionSort();
    TestCountingSort();
    TestRadixSort();
    PASS;
    
    TestRuntime();
    
    return 0;
}

/*******************************************************************************
*******************************************************************************/

static void InitArr(int *arr)
{
    size_t idx = 0;
    
    for (idx = 0; idx < ARR_SIZE; ++idx)
    {
        arr[idx] = rand();
    }
}

static void InitArrCounting(int *arr)
{
    size_t idx = 0;
    
    for (idx = 0; idx < ARR_SIZE; ++idx)
    {
        arr[idx] = 1 + (rand() % 100);
    }
}


static void InitArrRadix(int *arr)
{
    size_t idx = 0;
    
    for (idx = 0; idx < ARR_SIZE; ++idx)
    {
        arr[idx] = 1000000 + (rand() % 999999);
    }
}


static int IsSorted(int *arr)
{
    size_t idx = 0;
    
    for (idx = 1; idx < ARR_SIZE; ++idx)
    {
        if (arr[idx] < arr[idx - 1])
        {
            printf("idx: %lu\n", idx);
            printf("val @idx-1: %d\n", arr[idx - 1]);
            printf("val @idx: %d\n", arr[idx]);
            return 0;
        }
    }
    
    return 1;
}

/******************************************************************************/

static void TestBubbleSort(void)
{
    int arr[ARR_SIZE] = {0};
    double runtime = 0;
    
    InitArr(arr);
    
    runtime = clock();
    
    BubbleSort(arr, ARR_SIZE);
    TEST("BubbleSort", IsSorted(arr), 1);
    
    runtime = clock() - runtime;
    
    printf("BubbleSort elapsed run-time: %f\n", runtime / CLOCKS_PER_SEC);
}

/******************************************************************************/

static void TestSelectionSort(void)
{
    int arr[ARR_SIZE] = {0};
    double runtime = 0;
    
    InitArr(arr);
    
    runtime = clock();
    
    SelectionSort(arr, ARR_SIZE);
    TEST("SelectionSort", IsSorted(arr), 1);
    
    runtime = clock() - runtime;
    
    printf("SelectionSort elapsed run-time: %f\n", runtime / CLOCKS_PER_SEC);
}

/******************************************************************************/

static void TestInsertionSort(void)
{
    int arr[ARR_SIZE] = {0};
    double runtime = 0;
    
    InitArr(arr);
    
    runtime = clock();
    
    InsertionSort(arr, ARR_SIZE);
    TEST("InsertionSort", IsSorted(arr), 1);
    
    runtime = clock() - runtime;
    
    printf("InsertionSort elapsed run-time: %f\n", runtime / CLOCKS_PER_SEC);
}

/******************************************************************************/

static void TestCountingSort(void)
{
    int arr[ARR_SIZE] = {0};
    double runtime = 0;
    
    InitArrCounting(arr);
    
    runtime = clock();
    
    CountingSort(arr, ARR_SIZE);
    TEST("CountingSort", IsSorted(arr), 1);
    
    runtime = clock() - runtime;
    
    printf("CountingSort elapsed run-time: %f\n", runtime / CLOCKS_PER_SEC);
}

/******************************************************************************/

static void TestRadixSort(void)
{
    int arr[ARR_SIZE] = {0};
    double runtime = 0;
    
    InitArrRadix(arr);
    
    runtime = clock();
    
    RadixSort(arr, ARR_SIZE);
    TEST("RadixSort", IsSorted(arr), 1);
    
    runtime = clock() - runtime;
    
    printf("RadixSort elapsed run-time: %f\n", runtime / CLOCKS_PER_SEC);
}

/******************************************************************************/

static void TestRuntime(void)
{
    int arr[ARR_SIZE] = {0};
    double runtime = 0;
    
    InitArr(arr);
    
    runtime = clock();
    
    qsort(arr, ARR_SIZE, sizeof(int), CmpFunc);
    TEST("qsort", IsSorted(arr), 1);
    
    runtime = clock() - runtime;
    
    printf("qsort elapsed run-time: %f\n", runtime / CLOCKS_PER_SEC);
}

/******************************************************************************/

static int CmpFunc(const void *var1, const void *var2)
{
    return *(int *)var1 - *(int *)var2;
}
