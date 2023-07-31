/******************************************************************/
/*Date: 23.01.22*/
/*Author: Aviv Jilin*/
/*reviewer: Sarit */
/*version: 1.0 */
/*version :1.1 - added flag in bubblesort, added swapints for all functions, */
/*added another two variables (index_of_count) in radix and counting */
/*****************************************************************/

#include <stdlib.h> /* calloc,free */ 
#include <assert.h> /* assert      */

#include "comparisonlinearsort.h"

#define TRUE 1
#define FALSE 0

#define SUCCESS 0
#define FAIL 1


/* find minimum and maximum in array */
static void FindMinMax(int *arr, size_t size, int *out_min, int *out_max); 

/* function that swaps between two ints in memory                             */
static void SwapInts(int *num1, int *num2);

void SwapInts(int *num1, int *num2)
{
	int temp = 0;
	
	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

/*
bubbleSort: Sorts an array of integers using the bubble sort algorithm.
arr: pointer to the first element of the array
size: number of elements in the array
Time Complexity: O(n^2)
Space Complexity: O(1)
*/
void BubbleSort(int *arr, size_t size) 
{
    size_t i = 0;
    size_t j = 0;
    int swapped = FALSE;
    
    assert(NULL != arr);

    /* first loop i from 0 to size - 1 */
    for (i = 0; i < size - 1; ++i)
    {
        /* second loop j from 0 to size - i - 1*/
        /* make wall because end is always sorted */
        for (j = 0; j < size - i - 1; ++j) 
        {
            /* check if array at j is greater than array at j + 1 */
            if (arr[j] > arr[j+1])
            {
                /* true: do a swap between them */
                SwapInts(&arr[j], &arr[j+1]);
                swapped = TRUE;
            }
        }
        if(FALSE == swapped)
        {
	    break;
	}
    } 
}

/*
insertionSort: Sorts an array of integers using the insertion sort algorithm.
arr: pointer to the first element of the array
size: number of elements in the array
Time Complexity: O(n^2)
Space Complexity: O(1)
*/
void InsertionSort(int *arr, size_t size) 
{
    size_t i = 0;
    size_t j = 0;
    
    assert(NULL != arr);
    
    /* first loop from 1 to size - 1 */
    for (i = 1; i < size; ++i) 
    {
        /* j equal to i */
        j = i;
        /* second loop until j > 0 and arr[j - 1] > arr[j] to find where to insert*/
        while ((j > 0) && (arr[j -1] > arr[j]))
        {
            /* true: swap between arr[j] and arr [j -1] */
            SwapInts(&arr[j], &arr[j-1]);
            /* decrease j each time by one */
            --j;
        }
    }
    
    /* end second loop */
}

/*
SelectionSort: Sorts an array of integers using the selection sort algorithm.
arr: pointer to the first element of the array
size: number of elements in the array
Time Complexity: O(n^2)
Space Complexity: O(1)
*/
void SelectionSort(int *arr, size_t size) 
{
    size_t i = 0;
    size_t j = 0;
    size_t minimum_index = 0;
    
    assert(NULL != arr);
    
    /* first loop from 1 to size - 1*/
    for (i = 0; i < size - 1; ++i)
    {
        /* minimum_index is equal to i */
        minimum_index = i;
        /* second loop from j = i + 1 till n */
        for (j = i + 1; j < size; ++j)
        {
            /* find the smallest minimum */
            /* if (arr[i] < arr[minimum_index]) */
            if (arr[j] < arr[minimum_index])
            {
                /* true: update minimum_index to i */
                minimum_index = j;
            }
        }
        /* check if minimum_index is not equal to himself that is i */
        if (minimum_index != i)
        {
            /* perform swap between arr[i] and arr[minimum_index] */
            SwapInts(&arr[i], &arr[minimum_index]);
        }
    }
}

/*
RadixSort: Sorts an array of integers using the radix sort algorithm.
arr: pointer to the first element of the array
size: number of elements in the array
Time Complexity: O(nk)
Space Complexity: O(n+k)
returns: 0 if successful, non-zero otherwise*/

int RadixSort(int* arr, size_t size) 
{
    int i = 0;
    int max = 0;
    int min = 0;
    int exp = 1;
    int index_for_count = 0;
    int *output = NULL;
    int *count = NULL;
    
    assert(NULL != arr);

    /* Find the maximum value in the array */
    FindMinMax(arr, size, &min, &max);

    /* Perform counting sort for each digit */
    for (exp = 1; max / exp > 0; exp *= 10) 
    {
        output = (int *)malloc(size * sizeof(int));
        if (NULL == output)
        { 
            return FAIL; 
        }
    

        count = (int*)calloc(10, sizeof(int));
        if (count == NULL) 
        {
            free(output);
            output = NULL;
            
            return FAIL; 
        }
        

        /* Count the number of times each digit appears */
        for (i = 0; i < (int)size; ++i) 
        {
            index_for_count = (arr[i] / exp) % 10;
            ++count[index_for_count]; 
        }


        /* Calculate the cummulative count of each digit */
        for (i = 1; i < 10; ++i) 
        {
            count[i] += count[i - 1];
        }


        /* Build the output array */
        for (i = size - 1; i >= 0; --i) 
        {
            index_for_count = (arr[i] / exp) % 10;
            output[count[index_for_count] - 1] = arr[i];
            --count[index_for_count];
        }


        /* Copy the output array to the original array */
        for (i = 0; i < (int)size; ++i) 
        {
            arr[i] = output[i];
        }
        
        free(count);
        free(output);
        count = NULL;
        output = NULL;
    }
    return SUCCESS; 
}

/*CountingSort: Sorts an array of integers using the counting sort algorithm.
arr: pointer to the first element of the array
size: number of elements in the array
Time Complexity: O(n+k)
Space Complexity: O(n+k)
returns: 0 if successful, non-zero otherwise*/

int CountingSort(int *arr, size_t size) 
{
    int i = 0;
    int min = 0;
    int max = 0;
    int range = 0;
    int index_for_count = 0;
    int *count = NULL;
    int *output = NULL;
    
    assert(NULL != arr);

    /* function : findminmax */
    FindMinMax(arr, size, &min, &max);
    range = (max - min) + 1; 

    /* allocation with range * sizeof(int) set to zero */
    count = (int *)calloc(range, sizeof(int));
    if (NULL == count)
    {
        return FAIL; 
    }

    output = (int *)malloc(size * sizeof(int));
    if (NULL == output)
    {
        free(count);
        count = NULL;
        return FAIL; 
    }
    
    /* loop from 0 to size */
    for (i = 0; i < (int)size; ++i) 
    {
        /* ++count[arr[i] - min]; */
        ++count[arr[i] - min];
    }

    /* Store the cummulative count of each array */
    for (i = 1; i < range; ++i) 
    {
        count[i] += count[i - 1];
    }

    /* Build the output array */
    for (i = (int)size - 1; i >= 0; --i) 
    {
        index_for_count = arr[i] - min;
        output[count[index_for_count] - 1] = arr[i];
        --count[index_for_count];
    }

    /* Copythe output array to original array */
    /* sarit: you can use memcpy than do this youself! */
    for (i = 0; i < (int)size; ++i) 
    {
        arr[i] = output[i];
    } 

    /* Deallocate memory */
    free(count);
    free(output);
    count = NULL;
    output = NULL;

    /* Return success */
    return SUCCESS; 
}


/*FindMinMax: Finds the minimum and maximum elements in an array of integers
arr: pointer to the first element of the array
size: number of elements in the array
out_min: pointer to a variable that will hold the minimum value
out_max: pointer to a variable that will hold the maximum value
Time Complexity: O(n)
Space Complexity: O(1)*/

void FindMinMax(int *arr, size_t size, int *out_min, int *out_max) 
{
    size_t i = 0;
    *out_min =  arr[0];
    *out_max = arr[0];
    /* loop from start to size */
    for (i = 0; i < size; ++i) 
    {
        /* check if arr[i] < *outmin) */
        if (arr[i] < *out_min) 
        {
            /* asaign *out_min = arr[i] */
            *out_min = arr[i];
        }
        /* check if arr[i] > *outmax */
        else if (arr[i] > *out_max) 
        {
            /* asaign *out_max = arr[i] */
            *out_max = arr[i];
        }
    }
}
