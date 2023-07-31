/*******************************************************************************
Project:    Heap
Author:     HRD28
Version:    1.0 - 15/02/2023
            1.1 - 15/02/2023 -  added undefined behaviour for HeapPop
                                removed ptrs from function params
                                fixed typos
                                updated match_func signature
*******************************************************************************/
#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */

typedef struct heap heap_ty;

/*  write a function with the following signature to perform the comparison of
    the sorting criteria of your choice
    "heap_data" and "data_to_match" are the compared elements
    returns:    > 0 if heap_data > data_to_match
                < 0 if heap_data < data_to_match
                = 0 if heap_data == data_to_match                             */
typedef int (*heap_cmp_func_ty)(void *heap_data, void *data_to_match);

/*  write a function with the following signature to compare "heap_data" with
    "data"
    return 1 if match is found, 0 otherwise                                   */
typedef int (*heap_is_match_func_ty)(const void *heap_data, const void *data);

/*******************************************************************************
 *  creates an empty max heap, sorted by the comparison criteria specified by
 *  "cmp_func"
 *  returns pointer to "heap" on success, or NULL on failure
 *  note: undefined behaviour if "cmp_func" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
heap_ty *HeapCreate(heap_cmp_func_ty cmp_func);

/*******************************************************************************
 *  frees all resources used by "heap"
 *  note: undefined behaviour if "heap" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
void HeapDestroy(heap_ty *heap);

/*******************************************************************************
 *  inserts "data" to the correct position in the "heap"
 *  returns 0 if succeeded, 1 otherwise
 *  note: undefined behaviour if "heap" or "data" are NULL
 *  Time Complexity: O(logn)
*******************************************************************************/
int HeapPush(heap_ty *heap, const void *data);

/*******************************************************************************
 *  removes the max value from "heap"
 *  note: undefined behaviour if "heap" is NULL or is empty
 *  Time Complexity: O(logn)
*******************************************************************************/
void HeapPop(heap_ty *heap);

/*******************************************************************************
 *  returns a pointer to the max value in "heap"
 *  note: undefined behaviour if "heap" is NULL or is empty
 *  Time Complexity: O(1)
*******************************************************************************/
void *HeapPeek(const heap_ty *heap);

/*******************************************************************************
 *  searches for "data" in "heap", using "match_func", and removes it
 *  returns removed data on success, or NULL on failure
 *  note: undefined behaviour if "heap", "match_func", or "data" are NULL
 *  Time Complexity: O(n)
*******************************************************************************/
void *HeapRemove(heap_ty *heap, heap_is_match_func_ty match_func,
                                                            const void *data);

/*******************************************************************************
 *  returns 1 if "heap" is empty, 0 otherwise
 *  note: undefined behaviour if "heap" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
int HeapIsEmpty(const heap_ty *heap);

/*******************************************************************************
 *  returns the size of "heap"
 *  note: undefined behaviour if "heap" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
size_t HeapSize(const heap_ty *heap);

#endif /*   __HEAP_H__   */