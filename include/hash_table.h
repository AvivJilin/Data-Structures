/*******************************************************************************
* Author: HRD28
* Date: 9/02/2023
* Version: 1.0
           1.1 : 10/02/2023 : - fixed avl_data to hash_data
                              - fixed the name hash_table_func_ty to 
                                hash_func_ty
           1.2 : 10/02/2023  : changed names of typedes to hash_cmp_func_ty
                               and hash_action_func_ty
           1.3 : 10/02/2023  : in hash_cmp_func_ty changed the name of 
                               parameters to curr_key and key_to_match
           1.4 : 11/02/2023  : changed type of curr_key in hash_cmp_func_ty
                               to const
           1.5 : 11/02/2023  : added in function HTForEach underfined behaviour
                               if action = NULL
           1.6 : 11/02/2023  : in HTForEach changed the return value for failing
                               to: "the number of dlists that 
                                    action performed on"
*******************************************************************************/
#ifndef __HTABLE_H__
#define __HTABLE_H__

#include <stddef.h>         /*   size_t      */

#include "dlist.h"          /*   dlist_ty    */

typedef struct hash_table hash_table_ty;

/*  function that gets a data and returns his key                             */
typedef void *(*get_key_func_ty)(const void *data);

/*  function that gets a key and returns his idx in the hash table            */
typedef size_t (*hash_func_ty)(const void *key);

/*  write a function with the following signature to perform the comparison of
    "curr_key" and "key_to_match"
    returns: 1 if matched, 0 otherwise                                        */
typedef int (*hash_cmp_func_ty)(const void *curr_key, void *key_to_match);

/*  write a function with the following signature to perform whichever action
    you need on "hash_data"
    "params" is extra data
    return 0 if succeeded, otherwise - not 0                                  */
typedef int (*hash_action_func_ty)(void *hash_data, void *params);


/*******************************************************************************
 *  creates an empty hash table with "capacity", and the functions:
 *  "hash_func", "cmp_func" and "get_key"
 *  returns pointer to the "hash_table" on success, or NULL on failure
 *  note: undefined behaviour if "capacity" is 0 or the functions are NULL
 *  Time Complexity: O(n)
*******************************************************************************/
hash_table_ty *HTCreate(size_t capacity, hash_func_ty hash_func, 
                            hash_cmp_func_ty cmp_func, get_key_func_ty get_key);

/*******************************************************************************
 *  frees all resources used by "hash_table"
 *  note: undefined behaviour if "hash_table" is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
void HTDestroy(hash_table_ty *hash_table);

/******************************************************************************* 
 *  removes a value identified with a unique "key" from the "hash_table" 
 *  note: undefined behaviour if "hash_table" is NULL or "key" is NULL
 *  Time Complexity: avg - O(1), worst - o(n)
*******************************************************************************/
void HTRemove(hash_table_ty *hash_table, const void *key);

/******************************************************************************* 
 *  inserts "value" to the "hash_table"
 *  returns 0 if succeeded, not 0 otherwise
 *  note: undefined behavior if:
          - "hash_table" is NULL
          - "value" is NULL
          - "value" doesn't belong to the data type stored in "hash_table"
 *  Time Complexity: avg - O(1), worst - o(n)
*******************************************************************************/
int HTInsert(hash_table_ty *hash_table, const void *value);

/******************************************************************************* 
 *  returns the number of elements in "hash_table"
 *  note: undefined behaviour if "hash_table" is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
size_t HTSize(hash_table_ty *hash_table);

/******************************************************************************* 
 *  returns 1 if "hash_table" is empty, 0 otherwise
 *  note: undefined behaviour if "hash_table" is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
int HTIsEmpty(hash_table_ty *hash_table);

/******************************************************************************* 
 *  search for "key" in "hash_table"
 *  returns the value identified with the "key",
 *  or NULL if the value wasn't found
 *  note: undefined behaviour if:
          - "hash_table" is NULL
          - "key" is NULL
 *  Time Complexity: best - O(1), worst - O(n)
*******************************************************************************/
void *HTFind(hash_table_ty *hash_table, const void *key);

/******************************************************************************* 
 *  performs "action" on each element in the "hash_table"
 *  returns 0 if succeeded or the number of dlists that action performed on
 *  note: undefined behaviour if:
          - "hash_table" is NULL
          -  "action" is NULL
          - the action failed in process of HTForEach so the values
            are corrupted 
 *  Time Complexity: O(n)
*******************************************************************************/
size_t HTForEach(hash_table_ty *hash_table, hash_action_func_ty action, 
                                                                  void *params);

#endif  /*  __HTABLE_H__  */
