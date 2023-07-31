/*******************************************************************************
Project:    AVL
Author:     HRD28
Version:    1.0 - 06/02/2023
            1.1 - 06/02/2023 : update time complexity from o(n) to o(1) in
                               function AVLHeight
            1.2 - 06/02/2023 : * changed the return type of function AVLHeight
                               * more undefined behaviour in AVLFind,AVLForEach
*******************************************************************************/
#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h>     /*  size_t  */
#include <sys/types.h>  /*  ssize_t */

typedef struct avl avl_ty;

typedef enum order {PRE = 0, IN = 1, POST = 2} order_ty;

/*  write a function with the following signature to perform whichever action
    you need on "avl_data"
    "params" is extra data
    return 0 if succeeded, otherwise - not 0                                  */
typedef int (*action_func_ty)(void *avl_data, void *params);

/*  write a function with the following signature to perform the comparison of
    the sorting criteria of your choice
    "avl_data" and "data_to_match" are the compared elements
    returns:    > 0 if avl_data > data_to_match
                < 0 if avl_data < data_to_match
                = 0 if avl_data == data_to_match                              */
typedef int (*cmp_func_ty)(void *avl_data, void *data_to_match);

/*******************************************************************************
 *  creates an empty AVL tree, "avl", sorted by the comparison
 *  criteria specified by "cmp_func"
 *  returns pointer to "avl" on success, or NULL on failure
 *  note: undefined behaviour if "cmp_func" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
avl_ty *AVLCreate(cmp_func_ty cmp_func);

/*******************************************************************************
 *  frees all resources used by "avl"
 *  note: undefined behaviour if "avl" is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
void AVLDestroy(avl_ty *avl);

/******************************************************************************* 
 *  returns the number of elements in "avl"
 *  note: undefined behaviour if "avl" is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
size_t AVLSize(const avl_ty *avl);

/******************************************************************************* 
 *  returns 1 if "avl" is empty, 0 otherwise
 *  note: undefined behaviour if "avl" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
int AVLIsEmpty(const avl_ty *avl);

/******************************************************************************* 
 *  returns the height of "avl"
 *  if the AVL is empty, return -1
 *  note: undefined behaviour if "avl" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
ssize_t AVLHeight(const avl_ty *avl);

/******************************************************************************* 
 *  inserts "data" to the correct position in the "avl"
 *  returns 0 if succeeded, 1 otherwise
 *  note: undefined behavior if:
          - "avl" is NULL
          - inserting a duplicate element
 *  Time Complexity: O(logn)
*******************************************************************************/
int AVLInsert(avl_ty *avl, const void *data);

/******************************************************************************* 
 *  removes "data_to_remove" from the "avl"
 *  note: undefined behaviour if "avl" is NULL
 *  Time Complexity: O(logn)
*******************************************************************************/
void AVLRemove(avl_ty *avl, const void *data_to_remove);

/******************************************************************************* 
 *  uses "cmp_func" to search "avl" for "data_to_match" till success
 *  returns 0 if found, 1 otherwise
 *  note: undefined behaviour if:
          - "avl" is NULL
          - data_to_match doesnt match the sorting criteria of cmp_func
 *  Time Complexity: O(logn)
*******************************************************************************/
int AVLFind(const avl_ty *avl, const void *data_to_match);

/******************************************************************************* 
 *  performs "action" on each element in the "avl", in "order", till success
 *  returns 0 if succeeded, 1 otherwise
 *  note: undefined behaviour if:
          - "avl" is NULL 
          -  the action failed in process of AVLForEach so the datas
             are corrupted 
          -  the action made the tree not sorted
 *  Time Complexity: O(n)
*******************************************************************************/
int AVLForEach(avl_ty *avl, order_ty order,
                                        action_func_ty action, void *params);

#endif  /*  __AVL_H__  */
