/*******************************************************************************
Project:    Comparison Linear sort
Author:     HRD28
Version:    1.0 - 23/01/2023
*******************************************************************************/
#include <stddef.h> /* size_t */

#ifndef __COMPARING_LINEAR_SORT_H__
#define __COMPARING_LINEAR_SORT_H__

/*******************************************************************************
bubbleSort: Sorts an array of integers using the bubble sort algorithm.
arr: pointer to the first element of the array
size: number of elements in the array
note: undefined behavior if arr is empty.
Time Complexity: O(n^2)
Space Complexity: O(1)
*******************************************************************************/
void BubbleSort(int *arr, size_t size);

/*******************************************************************************
insertionSort: Sorts an array of integers using the insertion sort algorithm.
arr: pointer to the first element of the array
size: number of elements in the array
note: undefined behavior if arr is empty.
Time Complexity: O(n^2)
Space Complexity: O(1)
*******************************************************************************/
void InsertionSort(int *arr, size_t size);

/*******************************************************************************
SelectionSort: Sorts an array of integers using the selection sort algorithm.
arr: pointer to the first element of the array
size: number of elements in the array
note: undefined behavior if arr is empty.
Time Complexity: O(n^2)
Space Complexity: O(1)
*******************************************************************************/
void SelectionSort(int *arr, size_t size);

/*******************************************************************************
RadixSort: Sorts an array of integers using the radix sort algorithm.
arr: pointer to the first element of the array
size: number of elements in the array
Time Complexity: O(nk)
Space Complexity: O(n+k)
returns: 0 if successful, non-zero otherwise
*******************************************************************************/
int RadixSort(int *arr, size_t size);

/*******************************************************************************
CountingSort: Sorts an array of integers using the counting sort algorithm.
arr: pointer to the first element of the array
size: number of elements in the array
Time Complexity: O(n+k)
Space Complexity: O(n+k)
returns: 0 if successful, non-zero otherwise
*******************************************************************************/
int CountingSort(int *arr, size_t size);

#endif  /*  __COMPARING_LINEAR_SORT_H__   */
