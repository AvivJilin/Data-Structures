/******************************************************************/
/*Date: 14.12.22*/
/*Author: Aviv Jilin*/
/*reviewer: Gita */
/*version: 1.0*/
/*****************************************************************/


#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */

#include "slist.h"

typedef struct node
{
    void *data;
    struct node *next;
}node_ty;

struct slist
{
    node_ty *head;
    node_ty *tail;
};

static node_ty *GetNode(iter_ty iter_to_node)
{
    return (node_ty *)iter_to_node;
}

static iter_ty GetIter(node_ty *node_to_iter)
{
    return (iter_ty)node_to_iter;
}

/*******************************************************************************
 *  creates an empty single linked list - "slist"
 *  returns pointer to "slist" on success
 *  or NULL on failure
*******************************************************************************/
slist_ty *SlistCreate(void)
{
    node_ty *dummy = NULL;
    slist_ty *slist = (slist_ty *)malloc(sizeof(slist_ty));
    if (NULL == slist)
    {
        return NULL;
    }
    dummy = (node_ty *)malloc(sizeof(node_ty));
    if (NULL == slist)
    {
        free(slist);
        slist = NULL;
        return NULL;
    }
    dummy -> data = slist;
    dummy -> next = NULL;

    slist->tail = dummy;
    slist->head = dummy;

    return slist;
}

/*******************************************************************************
 *  frees all dynamic allocated resources used by "slist"
 *  note: undefined behaviour if "slist" is NULL
 *  Time Complexity: O(n)
*******************************************************************************/
void SlistDestroy(slist_ty *slist)
{
    node_ty *tmp = NULL;
    node_ty *start = NULL;
    assert(NULL != slist);

    start = slist->head;
    tmp = start;
    while(NULL != start->next)
    {
        tmp = start;
        start = start->next;
        free(tmp);
    }
    tmp = start;
    free(tmp);
    slist->head = NULL;
    slist->tail = NULL;
    free(slist);
    slist = NULL;
}


/******************************************************************************* 
*******************************************************************************/
iter_ty SlistInsert(iter_ty where, const void *data)
{
    slist_ty *tmp = NULL;
    node_ty *new_node = (node_ty *)malloc(sizeof(node_ty));
    
   
    assert(NULL != data);
    assert(NULL != where);

    new_node->data = where->data;
    new_node->next = where->next;
    where->data = (void *)data;
    where->next = new_node;

    if (NULL == new_node->next)
    {
        tmp = (slist_ty *)new_node->data;
        tmp->tail = new_node;
    }

    return GetIter(where);
}

/******************************************************************************* 
*******************************************************************************/
iter_ty SlistRemove(iter_ty iter_to_remove)
{   
    slist_ty *list = NULL;
    node_ty *temp = NULL;
    assert(NULL != iter_to_remove->next);

    temp = iter_to_remove->next;
    iter_to_remove->data = temp->data;
    iter_to_remove->next = temp->next;
    if (NULL == iter_to_remove->next)
    {
        list = (slist_ty *)iter_to_remove->data;
        list->tail = iter_to_remove;
    }
    free(temp);
    temp = NULL;

    return GetIter(iter_to_remove);
}

/******************************************************************************* 
*******************************************************************************/
size_t SlistCount(const slist_ty *slist)
{
    node_ty *tmp = NULL;
    size_t count = 0;
    assert(NULL != slist);
    tmp = slist->head;
    while (NULL != (tmp->next))
    {
        tmp =  tmp->next;
        ++count;
    }
    return count;
}

/******************************************************************************* 
*******************************************************************************/
iter_ty SlistFind(iter_ty from, iter_ty to, is_match_func_ty match_func, void *param)
{
    node_ty *temp = NULL;
    
    assert(NULL != from->next);

    temp = GetNode(from);
    while (temp != to)
    {
        if (match_func(temp->data, param))
        {
            return temp;
        }
        temp = temp->next;
    }
    return GetIter(to);
}

/******************************************************************************* 
*******************************************************************************/
int SlistForEach(iter_ty from, iter_ty to, action_func_ty action, void *param)
{
    node_ty *ptr_temp = NULL;
    int res = 0;

    assert(NULL != from->next);

    ptr_temp = GetNode(from);
    while (ptr_temp != to)
    {
        if (0 != action(ptr_temp->data, param))
        {
            return 1;
        }
        ptr_temp = ptr_temp->next;
    }
    return res;
}        
    

/******************************************************************************* 
*******************************************************************************/
iter_ty SlistIterBegin(slist_ty *slist)
{
    assert(NULL != slist);
    return GetIter(slist->head);
}


/****************************************************************************** 
*******************************************************************************/
iter_ty SlistIterEnd(slist_ty *slist)
{
    assert(NULL != slist);

    return GetIter(slist->tail);
}

/******************************************************************************* 
*******************************************************************************/
iter_ty SlistIterNext(iter_ty iter)
{
    node_ty *node_next = NULL;

    assert(NULL != iter->next);

    node_next = GetNode(iter);
    
    return GetIter(node_next->next);
}

/******************************************************************************* 
*******************************************************************************/
void *SlistIterGetData(iter_ty iter)
{
    node_ty *node_get_data = NULL;

    assert(NULL != iter);

    node_get_data = GetNode(iter);
    
    return GetIter(node_get_data->data);    
}

/******************************************************************************* 
*******************************************************************************/
void SlistIterSetData(iter_ty iter, const void *new_data)
{
    node_ty *node_set_data = NULL;

    assert(NULL != new_data);
    assert(NULL != iter->next);
    
    node_set_data = GetNode(iter);
    
    node_set_data->data = (void*)new_data;
}

/******************************************************************************* 
*******************************************************************************/
int SlistIterIsEqual(iter_ty iterator1, iter_ty iterator2)
{
    node_ty *node1 = NULL;
    node_ty *node2 = NULL;

    node1 = GetNode(iterator1);
    node2 = GetNode(iterator2);
    
    return (node1 == node2);
}

/******************************************************************************* 
*******************************************************************************/
void SlistAppend(slist_ty *dest, slist_ty *src)
{
    assert(NULL != dest);
    assert(NULL != src);

    dest->tail->data = src->head->data;
    dest->tail->next = src->head->next;
    free(src->head);

    src->tail->data = dest;

    dest->tail = src->tail;

    free(src);

    src = NULL;
}







