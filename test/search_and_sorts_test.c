#include <stddef.h>     /*  size_t      */
#include <stdlib.h>     /*  rand, qsort */
#include <time.h>       /*  clock       */

#include "search_and_sorts.h"
#include "tests.h"

#define ARR_SIZE 100

/*****************************Static Functions*********************************/

static void InitArr(int *arr);
static int IsSorted(int *arr);
static void TestMergeSort(void);
static void TestQuickSort(void);
static void TestRuntime(void);
static int CmpFunc(const void *var1, const void *var2);
void TestBinarySearch2(int num, int *arr, size_t size, ssize_t expectedIndex);
void TestBinarySearch(void);
void TestBinarySearch3(int num, int *arr, size_t size, ssize_t expectedIndex);

/******************************************************************************/

int main(void)
{
    TestMergeSort();
    TestQuickSort();
    TestBinarySearch();

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

static void TestMergeSort(void)
{
    int arr[ARR_SIZE] = {0};
    double runtime = 0;
    
    InitArr(arr);
    
    runtime = clock();
    
    MergeSort(arr, ARR_SIZE);
    TEST("MergeSort", IsSorted(arr), 1);
    
    runtime = clock() - runtime;
    
    printf("MergeSort elapsed run-time: %f\n", runtime / CLOCKS_PER_SEC);
}

static void TestQuickSort(void)
{
    int arr[ARR_SIZE] = {0};
    double runtime = 0;
    
    InitArr(arr);
    
    runtime = clock();
    
    QuickSort(arr, ARR_SIZE, sizeof(int), CmpFunc);
    TEST("QuickSort", IsSorted(arr), 1);
    runtime = clock() - runtime;
    
    printf("QuickSort elapsed run-time: %f\n", runtime / CLOCKS_PER_SEC);
}


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

void TestBinarySearch2(int num, int *arr, size_t size, ssize_t expectedIndex)
{

    ssize_t iterativeIndex = BinarySearchIterative(num, arr, size);
    if (iterativeIndex == expectedIndex) {
        printf("Iterative test passed\n");
    } else {
        printf("Iterative test failed\n");
    }
}

void TestBinarySearch3(int num, int *arr, size_t size, ssize_t expectedIndex)
{

    ssize_t iterativeIndex = BinarySearchRecursive(num, arr, size);
    if (iterativeIndex == expectedIndex) {
        printf("Recursive test passed\n");
    } else {
        printf("Recursive test failed\n");
    }
}

void TestBinarySearch(void)
{
    int arr1[] = {1, 2, 3, 4, 5, 6};
    size_t size1 = sizeof(arr1) / sizeof(*arr1);
    int num1 = 4;
    ssize_t expectedIndex1 = 3;
    TestBinarySearch2(num1, arr1, size1, expectedIndex1);
    TestBinarySearch3(num1, arr1, size1, expectedIndex1);
}
