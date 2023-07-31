/******************************************************************
Project: Search and sorts
Author: Aviv Jilin
reviewer: Nadav
version: 1.0 - 13.02.23
         2.0 - 14.02.23 - Add enums in all functions, 
                        change the names to left and right in BinarySearchIterative  
                        add assert in all functions
*****************************************************************/

#include <stdlib.h> /* malloc, free, size_t */ 
#include <assert.h> /* assert               */
#include <string.h> /* memcpy               */

#include "search_and_sorts.h"

enum search_state
{
    NOT_FOUND = -1,
    FOUND
};

enum state
{
    SUCCESS = 0,
    FAIL
};


/*this is binary search recursive imp for the recursive function*/
static ssize_t BinarySearchRecursiveImp(int num, int *arr, int low, int high);

/* this is the merge function that recieve left sub array and right sub array and do a merge */
static int Merge(int *arr_to_sort, size_t num_elements, int *l_sub_arr, int *r_sub_arr);

/* partition function it is a function that return the pivot index in the right place */
static int Partition(void *base, size_t nmemb, size_t size, 
                                                    sort_cmp_func_ty cmp_func);
static void Swap(void *num, void *num2);

ssize_t BinarySearchIterative(int num, int *arr, size_t size) 
{
    /* init the left, mid and right */
    int left = 0;
    int right = 0; 
    int mid = 0;

    assert (NULL != arr);

    /* right should be size - 1*/
    right = size - 1;

    /* a loop until left is bigger than right */
    while (left <= right) 
    {
        /* each time take the middle */
        mid = (left + right) / 2;

        /* check arr[mid] if it is the num */
        if (arr[mid] == num) 
        {
            /* return mid if found */
            return mid;
            /* check if arr[mid] is smaller than num */
        } 
        else if (arr[mid] < num) 
        {
            /* if true add mid + 1 */
            left = mid + 1;
        } 
        else 
        {
            /* if false mid - 1*/
            right = mid - 1;
        }
    }
    /* return -1 if not found */
    return NOT_FOUND; 
}

ssize_t BinarySearchRecursive(int num, int *arr, size_t size)
{
    assert(NULL != arr);

    /* call the recursive imp function */
    return BinarySearchRecursiveImp(num, arr, 0, size - 1);
}

    
ssize_t BinarySearchRecursiveImp(int num, int *arr, int low, int high)
{
    int mid = 0;

    assert(NULL != arr);

    /* base check if low is greater than high */
    if (low > high)
    {
        return NOT_FOUND;  
        /* return -1 */
    }

    /* get the mid by (low + high)/2 */
    mid = (low + high) / 2;

    /* check if arr[mid] is equal to num*/
    if (arr[mid] == num) 
    {
        /* return mid */
        return mid;
    /* else if check if arr[mid] is smaller than num */
    } 
    else if (arr[mid] < num)
    {
        /* call the recursive function with mid + 1 in the low argument */
        return BinarySearchRecursiveImp(num, arr, mid + 1, high);
    } 
    /* else */
    else
    {
        /* call the recursive functin with mid - 1 in the high argument */
        return BinarySearchRecursiveImp(num, arr, low, mid - 1);
    }
}


int MergeSort(int *arr_to_sort, size_t num_elements)
{
    size_t half_n_elem = 0;
    int *left_sub_arr_ptr = NULL; 
    int *right_sub_arr_ptr = NULL;
    int res = 0;

    assert(NULL != arr_to_sort);

    /* base if check until num_element <= 1 */
    if (num_elements <= 1)
    {
        /* return */
        return res;
    }

    /* get mid num by / 2 */
    half_n_elem = num_elements / 2;
    left_sub_arr_ptr = arr_to_sort;
    right_sub_arr_ptr = arr_to_sort + half_n_elem;

    /* call the MergeSort with arr_to_sort and the mid */ 
    MergeSort(left_sub_arr_ptr, half_n_elem);
    /* call the Other half with arr_to_sort + mid, num_elements - mid */
    MergeSort(right_sub_arr_ptr, num_elements - half_n_elem);
    /* call the Merge(arr_to_sort, mid, num_elements - mid, arr_to_sort + mid) */ 
    res = Merge(arr_to_sort, num_elements, left_sub_arr_ptr, right_sub_arr_ptr);

    return res;
}


int Merge(int *arr_to_sort, size_t num_elements, int *l_sub_arr, int *r_sub_arr) 
{

    int *r_sub_arr_end = NULL;
    int *l_sub_arr_end = NULL;
    /* get the size of left len and right len */
    size_t l_sub_arr_len = (num_elements / 2);
    size_t r_sub_arr_len = (num_elements - l_sub_arr_len);
    int *tmp_begin = NULL;
    int *temp = NULL;

    assert(NULL != arr_to_sort);

    /*allocate new memory for temp array */
    temp = (int *)malloc(num_elements * sizeof(int));
    tmp_begin = temp;

    l_sub_arr_end = l_sub_arr + l_sub_arr_len;
    r_sub_arr_end = r_sub_arr + r_sub_arr_len;

    /* check for allocation */
    if (NULL == temp)
    {
        return FAIL;   
    }

    /* do a while loop and check if indexes i and j are smaller than left and right len */
    while (l_sub_arr < l_sub_arr_end && r_sub_arr < r_sub_arr_end) 
    {
        /* check if the data is smaller than right */
        if (*(l_sub_arr) <= *(r_sub_arr)) 
        {
            /* put the smaller or equal to the temp */
            *(temp) = *(l_sub_arr);
            l_sub_arr = l_sub_arr + 1;
        } else /*Nadav: need to be in new line */
        {
            /* put the bigger to the temp */
            *(temp) = *(r_sub_arr);
            r_sub_arr = r_sub_arr + 1;  
        }
        ++temp;
    }

    /* now do the leftover of each right and left arrays to the temp*/
    while (l_sub_arr < l_sub_arr_end) 
    {
        *(temp) = *(l_sub_arr);
        l_sub_arr = l_sub_arr + 1;
        ++temp;
    }

    while (r_sub_arr < r_sub_arr_end) 
    {
        *(temp) = *(r_sub_arr);
        r_sub_arr = r_sub_arr + 1;
        ++temp;
    }

    /* put all the temp to the original arr_to_sort */
    memcpy(arr_to_sort, tmp_begin, num_elements * sizeof(int));
    
    free(tmp_begin);
    return SUCCESS;
}

void QuickSort(void *base, size_t nmemb, size_t size, sort_cmp_func_ty cmp_func)
{
    /*init base_tmp and pivot_index*/
    int pivot_index = 0;
    char *base_tmp = NULL;

    assert(NULL != base);

    base_tmp = (char *)base;

    /*check if the array has more than 1 element, return if not */
    if (nmemb < 2)
    {
        return;
    }

    /*find the pivot index using partition() */
    pivot_index = Partition(base_tmp, nmemb, size, cmp_func);

    /*recursively sort elements before and after the pivot, "less" and "greater" partitions */
    QuickSort(base_tmp, pivot_index, size, cmp_func);
    QuickSort(base_tmp + (pivot_index + 1) * size, nmemb - pivot_index - 1, size, cmp_func);
}

int Partition(void *base, size_t nmemb, size_t size, 
                                                    sort_cmp_func_ty cmp_func)
{
    /*init runners to traverse the array*/
    size_t i = -1, j = 0;
    /*init pivot pointer var*/
    void *pivot = NULL;
    char *base_tmp = (char *)base;
    
    /*choose the last element as the pivot */
    pivot = (char *)base + (nmemb - 1) * size;

    /*partition the array around the pivot */
    for (j = 0; j < nmemb - 1; ++j)
    {
        if (cmp_func(base_tmp + j * size, pivot) < 0)
        {
            ++i;
            /*Swap((char *)base + i * size, (char *)base + j * size, size);*/
            Swap((void *)(base_tmp + i * size), (void *)(base_tmp + (j * size)));
        }
    }

    /*place the pivot in the correct position */
    /*Swap((char *)base + (i + 1) * size, pivot, size);*/
    Swap((void *)(base_tmp + (i + 1) * size), pivot);

    /*return the pivot index */
    return i + 1;
}

void Swap(void *num, void *num2)
{
    int temp = 0;

    temp = *(int *)num;
    *(int *)num = *(int *)num2;
    *(int *)num2 = temp;
}

