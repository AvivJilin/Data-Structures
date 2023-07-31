/*******************************************************************************
Project:    Hash Table
Author:     Aviv Jilin
Tester:     Gita
Version:    1.0 - 06/02/2023
*******************************************************************************/
#include <stdlib.h> /* malloc ,free, max */
#include <assert.h> /* assert       */

#include "hash_table.h"
#include "dlist.c"

struct hash_table
{
    size_t capacity;
    get_key_func_ty get_key;
    hash_cmp_func_ty cmp_func;
    hash_func_ty hash_func;
    dlist_ty **dlist;
};

typedef struct data
{
    void *key;
    void *value;
}data_ty;

typedef struct cmp_and_params
{
    hash_cmp_func_ty cmp_func;
    const void *key;
} cmp_and_params_ty;

typedef struct action_and_params
{
    hash_action_func_ty action;
    void *user_params;
} action_and_params_ty;


enum check {SUCCESS = 0, FAIL = 1};

/******************************Static Functions********************************/
static int FreeHashedElement(void *hash_data, void *params);
static dlist_iter_ty FindElementWithKey(hash_table_ty *hash_table,
                                            dlist_ty **dlist, const void *key);
static int MatchKeys(const void *ds_data, void *params);
static int ActionFunc(void *hash_data, void *params);


hash_table_ty *HTCreate(size_t capacity, hash_func_ty hash_func, 
                                 hash_cmp_func_ty cmp_func, get_key_func_ty get_key)
{
    /* create index i = 0 */
    size_t i = 0;
    /* allocate new table and check for failure */
    hash_table_ty *new_table = (hash_table_ty *)malloc(sizeof(hash_table_ty));

    if (NULL == new_table)
    {
        return NULL;
    }

    /* init all the members of new_table */
    new_table->capacity = capacity;
    new_table->hash_func = hash_func;
    new_table->cmp_func = cmp_func;
    new_table->get_key = get_key;
    new_table->dlist = (dlist_ty**)malloc(sizeof(dlist_ty*) * capacity);

    if (NULL == new_table->dlist) 
    {
        free(new_table);
        new_table = NULL;
        return NULL;
    }

    /* create dlist for each member till capacity if failed free all the created */
    for (i = 0; i < capacity; ++i)
    {
        new_table->dlist[i] = DlistCreate();
        if (NULL == new_table->dlist[i])
        {
            for (i = 0; i > 0; --i)
            {
                DlistDestroy(new_table->dlist[i - 1]);
            }
            free(new_table);
            new_table = NULL;

            return NULL;
        }
    }

    /* return the new table */
    return new_table;
}

/*******************************************************************************
 *  frees all resources used by "hash_table"
 *  note: undefined behaviour if "hash_table" is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
void HTDestroy(hash_table_ty *hash_table) 
{
    /* declare index i = 0 and dlist*/
    size_t i = 0;
    dlist_ty *list = NULL;

    /* in loop destroy each dlist that was created */
    for (i = 0; i < hash_table->capacity; ++i) 
    {
        list = hash_table->dlist[i];
        DlistForEach(DlistIterBegin(list), DlistIterEnd(list),
                                                    FreeHashedElement, NULL);

        DlistDestroy(list);
    }

    free(hash_table->dlist);
    hash_table->dlist = NULL;

    /* free the hash_table */
    free(hash_table);
    hash_table = NULL;
}

void HTRemove(hash_table_ty *hash_table, const void *key)
{
    dlist_ty *dlist = NULL;
    dlist_iter_ty iter; /* will be used to hold the iter to the dlist element */
    
    assert(NULL != hash_table);
    assert(NULL != key);
    
    /*  find the element corresponding to key and check for success           */
    iter = FindElementWithKey(hash_table, &dlist, key);
    
    if (!DlistIterIsEqual(iter, DlistIterEnd(dlist)))
    {
        /*  use DlistRemove on the iterator from DlistFind                    */
        FreeHashedElement(DlistIterGetData(iter), NULL);
        DlistRemove(iter);
    }
}


int HTInsert(hash_table_ty *hash_table, const void *value)
{
    /* declare key,idx,list and iter */
    void *key = NULL;
    size_t idx = 0;
    dlist_ty *list = NULL;
    dlist_iter_ty iter = NULL;
    data_ty *data = NULL;

    /* get the key from get_key, the idx from hash_func and get dlist[idx] */
    key = hash_table->get_key(value);
    idx = hash_table->hash_func(key);
    list = hash_table->dlist[idx];

    data = (data_ty *)malloc(sizeof(data_ty));

    data->key = key;
    data->value = (void *)value;
    
    /* insert to the back the data */
    iter = DlistPushBack(list, data);

    /* check if it failed or successed */
    if (iter == DlistIterEnd(list))
    {
        return FAIL;
    }
    return SUCCESS;
}

size_t HTSize(hash_table_ty *hash_table)
{
    /* declare count and index i */
    size_t count = 0, i = 0;

    /* loop for each dlist and get size of each dlist */
    for (i = 0; i < hash_table->capacity; ++i)
    {
        count += DlistSize(hash_table->dlist[i]);
    }

    return count;
}

int HTIsEmpty(hash_table_ty *hash_table) 
{
    /* declare index i */
    size_t i = 0;

    /* loop until found or not found the return from dlistsize */
    for (i = 0; i < hash_table->capacity; ++i) 
    {
        if (DlistSize(hash_table->dlist[i]) > 0)
        {
            return SUCCESS;
        }
    }
    return FAIL;
}


void *HTFind(hash_table_ty *hash_table, const void *key)
{
    dlist_iter_ty found_iter;
    dlist_ty *dlist = NULL;
    dlist_iter_ty end = NULL;
    data_ty *data = NULL;
    
    assert(hash_table);
    assert(key);
    
    dlist = hash_table->dlist[hash_table->hash_func(key)];
    end = DlistIterEnd(dlist);
    
    /* find the element iter in dlist */
    found_iter = FindElementWithKey(hash_table, &dlist, key);
    
    /* check if iter found */
    if (DlistIterIsEqual(end, found_iter))
    {
        return NULL;
    }
    
    /* return the data in case it found using DlistIterGetData */
    data = (data_ty *) DlistIterGetData(found_iter);

    return data->value;
}

static dlist_iter_ty FindElementWithKey(hash_table_ty *hash_table,
                                            dlist_ty **dlist, const void *key)
{
    dlist_iter_ty iter; /* will be used to hold the iter to the dlist element */
    cmp_and_params_ty altered_params = {NULL, NULL};
    
    assert(NULL != hash_table);
    assert(NULL != key);
    
    /*  use the hash_func to get an index from the key                        */
    *dlist = hash_table->dlist[hash_table->hash_func(key)];;
    
    /*  use DlistFind with hash_cmp_func on each element in the dlist to find
        the one that matches the given key                                    */
    altered_params.cmp_func = hash_table->cmp_func;
    altered_params.key = key;
    
    iter = DlistFind(DlistIterBegin(*dlist), DlistIterEnd(*dlist),
                                            MatchKeys, (void *)&altered_params);
    
    return iter;
}

/******************************************************************************/

static int MatchKeys(const void *ds_data, void *params)
{
    hash_cmp_func_ty cmp_func = NULL;
    const void *curr_key = NULL;
    void *key_to_match = NULL;
    data_ty *ds_data_tmp = (data_ty *)ds_data;
    
    assert(NULL != ds_data);
    assert(NULL != params);
    
    cmp_func = ((cmp_and_params_ty *)params)->cmp_func;
    key_to_match = (void *)(((cmp_and_params_ty *)params)->key);
    curr_key = ds_data_tmp->key;
    
    return cmp_func(curr_key, key_to_match);
}

size_t HTForEach(hash_table_ty *hash, action_func_ty action, void *params)
{
    /*int DlistForEach(dlist_iter_ty from, dlist_iter_ty to,
     action_func_ty action, void *param);*/
    int cnt_falied = 0;
    size_t i = 0;
    dlist_ty *dlist = NULL;
    action_and_params_ty altered_params = {NULL, NULL};

    assert(hash);
    assert(action);

    altered_params.action = action;
    altered_params.user_params = params;
    
    
    for (i = 0; i < hash->capacity; ++i)
    {
        dlist = hash->dlist[i];
        
        cnt_falied += DlistForEach(DlistIterBegin(dlist), DlistIterEnd(dlist),
         ActionFunc, (void *)&altered_params);
    }
    
    return cnt_falied;
}

static int ActionFunc(void *hash_data, void *params)
{
    data_ty *hashed_element = NULL;
    hash_action_func_ty action = NULL;
    void *user_params = NULL;
    
    
    assert(NULL != hash_data);
    assert(NULL != params);


    action = ((action_and_params_ty *)params)->action;
    user_params = ((action_and_params_ty *)params)->user_params;
    hashed_element = (data_ty *)hash_data;
    
    return action((void *)hashed_element->value, user_params);
}


static int FreeHashedElement(void *hash_data, void *params)
{

    params = (char *)params;
    
    assert(NULL != hash_data);
    
    free(hash_data);
    hash_data = NULL;
    
    return SUCCESS;
}






