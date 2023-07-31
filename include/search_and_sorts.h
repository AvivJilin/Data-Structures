/*******************************************************************************
Project:    Binary Search, Merge Sort, and Quick Sort
Author:     HRD28
Version:    1.0 - 12/02/2023
			1.1 - 13/02/2023 : return value corrections
			1.2 - 13/02/2023 : space complexity of quickSort update
			1.3 - 13/02/2023 : cmp_func definition
			1.4 - 13/02/2023 : cmp func signiture fixed
*******************************************************************************/
#ifndef __SEARCH_AND_SORTS_H__
#define __SEARCH_AND_SORTS_H__

#include <sys/types.h>	/*	ssize_t	*/

/*  write a function with the following signature to perform the comparison of 
    the sorting criteria 
    "data1" and "data2" are the compared elements
    returns:    > 0 if data1 > data2
                < 0 if data1 < data2
                = 0 if data1 == data2                                         */
typedef int (*sort_cmp_func_ty)(const void *data1, const void *data2);

/*******************************************************************************
 *  searches for "num" in "arr"
 *  note: - "arr" must be sorted (ascending)
 *	returns the index of searched num in arr or -1 otherwise
 *        - undefined behaviour if "arr" is NULL or if "size" is not the array's
 *          actual size
 *  time complexity:    O(logn)
 *  space complexity:   O(1)
*******************************************************************************/
ssize_t BinarySearchIterative(int num, int *arr, size_t size);

/*******************************************************************************
 *  searches for "num" in "arr"
 *	returns the index of searched num in arr or -1 otherwise
 *  note: - "arr" must be sorted (ascending)
 *        - undefined behaviour if "arr" is NULL or if "size" is not the array's
 *          actual size
 *  time complexity:    O(logn)
 *  space complexity:   O(logn)
*******************************************************************************/
ssize_t BinarySearchRecursive(int num, int *arr, size_t size);

/*******************************************************************************
 *  sorts "arr" in ascending order
 *	returns 0 if succeeded  and not 0 otherwize
 *  note: - undefined behaviour if "arr" is NULL or if "size" is not the array's
 *          actual size
 *  time complexity:    O(nlogn)
 *  space complexity:   O(n)
*******************************************************************************/
int MergeSort(int *arr_to_sort, size_t num_elements);

/*******************************************************************************
 *  sorts an array with "nmemb" elements of "size", in ascending order according
 *  to the comparison criteria "compar"
 *  "base" points to the start of the array
 *  note: - undefined behaviour if "base" is NULL, if "nmemb" is not the array's
 *          actual size, if "size" is not the element's actual size, or if
 *          "compar" is NULL
 *  time complexity:    O(nlogn)
 *  space complexity:   O(1)
*******************************************************************************/
void QuickSort(void *base, size_t nmemb, size_t size, sort_cmp_func_ty cmp_func);

#endif /*__SEARCH_AND_SORTS_H__*/
