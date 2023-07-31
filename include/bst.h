/*******************************************************************************
Project:    Binary Search Tree
Author:     HRD28
Version:    1.0 - 25/01/2023
            1.1 - 25/01/2023 -  BSTFind - delete is_match_fucntion
                             -  add params to cmp_func_ty
                             -  change time_complexity of BSTIterBegin,
                                BSTIterPrev, and BSTIterNext
            1.2 - 26/01/2023 -  fixed typos in BSTFind
                             -  fixed undefined behaviour in BSTIterBegin
                             -  BSTForEach - changed "iter" to "from"
            1.3 - 29/01/2023 -  BSTFind - changed "iter" to "bst"
            1.4 - 29/01/2023 -  BSTForEach - fixed undefined behaviour
                                if action is NULL 
*******************************************************************************/
#ifndef __BST_H__
#define __BST_H__

#include <stddef.h>     /*  size_t  */

/*  "bst" handle                                                              */
typedef struct bst bst_ty;

typedef struct bst_node bst_node_ty;

/*  bst_iter is a temporary object, it might change, do not use it            */
typedef struct bst_iter
{
    bst_node_ty *node;
} bst_iter_ty;


/*  write a function with the following signature to perform whichever action
    you need on "bst_data"
    "params" is extra data
    return 0 if succeeded, otherwise - not 0                                  */
typedef int (*action_func_ty)(void *bst_data, void *params);

/*  write a function with the following signature to perform the comparison of
    the sorting criteria of your choice
    "bst_data" and "data_to_match" are the compared elements
    returns:    > 0 if bst_data > data_to_match
                < 0 if bst_data < data_to_match
                = 0 if bst_data == data_to_match                              */
typedef int (*cmp_func_ty)(void *bst_data, void *data_to_match, void *params);

/*******************************************************************************
 *  creates an empty binary search tree, "bst", sorted by the comparison
 *  criteria specified by "cmp_func"
 *  returns pointer to "bst" on success, or NULL on failure
 *  Time Complexity: O(1)
*******************************************************************************/
bst_ty *BSTCreate(cmp_func_ty cmp_func, void *params);

/*******************************************************************************
 *  frees all resources used by "bst"
 *  note: undefined behaviour if "bst" is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
void BSTDestroy(bst_ty *bst);

/******************************************************************************* 
 *  returns the number of elements in "bst"
 *  note: undefined behaviour if "bst" is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
size_t BSTSize(const bst_ty *bst);

/******************************************************************************* 
 *  returns 1 if "bst" is empty, 0 otherwise
 *  note: undefined behaviour if "bst" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
int BSTIsEmpty(const bst_ty *bst);

/******************************************************************************* 
 *  inserts "data" to the correct position in the "bst"
 *  returns an iterator to the added "data" if succeeded, BSTIterEnd otherwise
 *  note: may cause iterator invalidity
 *        undefined behavior if inserting a duplicate element or "bst" is NULL 
 *  Time Complexity: best - O(logn), worst - O(n)
*******************************************************************************/
bst_iter_ty BSTInsert(bst_ty *bst, const void *data);

/******************************************************************************* 
 *  removes the element at "iter_to_remove"
 *  note: undefined behaviour if "iter_to_remove" is BSTIterEnd
 *  Time Complexity: best - O(logn), worst - O(n)
*******************************************************************************/
void BSTRemove(bst_iter_ty iter_to_remove);

/******************************************************************************* 
 *  returns an iterator to the left-most child of "bst", BSTIterEnd if empty
 *  note: undefined behaviour if "bst" is NULL
 *  Time Complexity: O(logn)
*******************************************************************************/
bst_iter_ty BSTIterBegin(const bst_ty *bst);

/******************************************************************************* 
 *  returns an iterator to the end of "bst", this is an invalid element
 *  note: undefined behaviour if "bst" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
bst_iter_ty BSTIterEnd(const bst_ty *bst);

/******************************************************************************* 
 *  returns an iterator to the previous element in "bst", according to its 
 *  sorting criteria
 *  note: undefined behaviour if "iter" is BSTIterBegin
 *  Time Complexity: O(logn)
*******************************************************************************/
bst_iter_ty BSTIterPrev(const bst_iter_ty iter);

/******************************************************************************* 
 *  returns an iterator to the next element in "bst", according to its sorting
 *  criteria
 *  note: undefined behaviour if "iter" is BSTIterEnd
 *  Time Complexity: O(logn)
*******************************************************************************/
bst_iter_ty BSTIterNext(const bst_iter_ty iter);

/******************************************************************************* 
 *  returns 1 if two iterators are pointing to the same element in a bst,
 *  0 otherwise
 *  Time Complexity: O(1)
*******************************************************************************/
int BSTIterIsSame(const bst_iter_ty iter1, const bst_iter_ty iter2);

/******************************************************************************* 
 *  returns data stored in the node corresponding to "iter"
 *  note: undefined behaviour if "iter" is BSTIterEnd
 *  Time Complexity: O(1)
*******************************************************************************/
void *BSTIterGetData(const bst_iter_ty iter);

/******************************************************************************* 
 *  uses "cmp_func" to search "bst" for "data_to_match" till success
 *  if found, returns the iterator to that element, return BSTIterEnd otherwise
 *  note: undefined behaviour if "bst" is NULL
 *  Time Complexity: best - O(logn) worst - O(n)
*******************************************************************************/
bst_iter_ty BSTFind(const bst_ty *bst, const void *data_to_match);

/******************************************************************************* 
 *  performs "action" on each element in the range ["from", "to") till success
 *  returns 0 if succeeded, not 0 otherwise
 *  note: undefined behaviour if "from" is BSTIterEnd, or action is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
int BSTForEach(bst_iter_ty from, bst_iter_ty to,
                                        action_func_ty action, void *params);

#endif  /*  __BST_H__  */
