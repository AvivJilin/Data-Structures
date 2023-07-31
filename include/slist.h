/*******************************************************************************
 * Author:      HRD28
 * Version:     1.4
*******************************************************************************/
#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>     /*  size_t  */

/*  node is a temporary object, it might change, do not use it                */
typedef struct node *iter_ty;

/*  "slist" handler                                                           */
typedef struct slist slist_ty;

/*  write a function with the following signature to compare "list_data" with
    internal data in the function
    "param" is extra data
    return 1 if match is found, 0 otherwise                                   */
typedef int (*is_match_func_ty)(const void *list_data, void *param);

/*  write a function with the following signature to perform whichever action
    you need on "list_data"
    "param" is extra data                                              
    return 0 if succeeded, otherwise - not 0                                  */
typedef int (*action_func_ty)(void *list_data, void *param);

/*******************************************************************************
 *  creates an empty single linked list - "slist"
 *  returns pointer to "slist" on success
 *  or NULL on failure
*******************************************************************************/
slist_ty *SlistCreate(void);

/*******************************************************************************
 *  frees all dynamic allocated resources used by "slist"
 *  note: undefined behaviour if "slist" is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
void SlistDestroy(slist_ty *slist);

/******************************************************************************* 
 *  inserts "data" before a given iter "where"
 *  returns an iterator to the added data if succeeded, SlistIterEnd() otherwise
 *  Time Complexity: avg - O(1), worst - O(n)
*******************************************************************************/
iter_ty SlistInsert(iter_ty where, const void *data);

/******************************************************************************* 
 *  removes the element at "iter_to_remove" and returns iterator to the next 
 *  element in the slist
 *  note: undefined behaviour if "iter_to_remove" is SlistIterEnd()
 *  Time Complexity: O(1)
*******************************************************************************/
iter_ty SlistRemove(iter_ty iter_to_remove);

/******************************************************************************* 
 *  returns the number of elements in "slist"
 *  note: undefined behaviour if "slist" is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
size_t SlistCount(const slist_ty *slist);

/******************************************************************************* 
 *  performs "match_func" on each element in the range ["from", "to") till 
 *  success
 *  if found, returns the iterator to that element, return "to" iter otherwise
 *  note: undefined behaviour if "from" is SlistIterEnd()
          from must be order before to in the list
 *  Time Complexity: O(n)
*******************************************************************************/
iter_ty SlistFind(iter_ty from, iter_ty to, is_match_func_ty match_func, void *param);

/******************************************************************************* 
 *  performs "action" on each element in the range ["from", "to") till success
 *  returns 0 if succeeded, not 0 otherwise
 *  note: undefined behaviour if "from" is SlistIterEnd()
          from must be order before to in the list
 *  Time Complexity: O(n)
*******************************************************************************/
int SlistForEach(iter_ty from, iter_ty to, action_func_ty action, void *param);

/******************************************************************************* 
 *  returns an iterator to the first valid element in "slist", SlistIterEnd() 
 *  if empty.
 *  note: undefined behaviour if "slist" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
iter_ty SlistIterBegin(slist_ty *slist);

/******************************************************************************* 
 *  returns an iterator to the end of "slist", this is an invalid element
 *  note: undefined behaviour if "slist" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
iter_ty SlistIterEnd(slist_ty *slist);

/******************************************************************************* 
 *  returns an iterator to the next element in slist
 *  note: undefined behaviour if "iter" is SlistIterEnd() 
 *  Time Complexity: O(1)
*******************************************************************************/
iter_ty SlistIterNext(iter_ty iter);

/******************************************************************************* 
 *  returns data stored in "iter"
 *  note: undefined behaviour if "iter" is SlistIterEnd()
 *  Time Complexity: O(1)
*******************************************************************************/
void *SlistIterGetData(iter_ty iter);

/******************************************************************************* 
 *  sets the data in "iter" to be "new_data"
 *  note: undefined behaviour if "iter" is SlistIterEnd()
 *  Time Complexity: O(1)
*******************************************************************************/
void SlistIterSetData(iter_ty iter, const void *new_data);

/******************************************************************************* 
 *  returns 1 if two iterators are pointing to the same element in a slist,
 *  0 otherwise
 *  Time Complexity: O(1)
*******************************************************************************/
int SlistIterIsEqual(iter_ty iterator1, iter_ty iterator2);

#endif  /*  __SLIST_H__   */
