/*******************************************************************************
Project:    Binary Search Tree
Author:     Aviv Jilin
Tester:     Almog
Version:    1.0 - 25/01/2023
*******************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "bst.h"

enum childs {LEFT = 0, RIGHT = 1, NUM_CHILD_NODES = 2};

enum success {SUCCESS = 0, FAIL = 1};

struct bst_node 
{
    void* data;
    struct bst_node* child[NUM_CHILD_NODES];
    struct bst_node* parent;
};

struct bst 
{
    struct bst_node* dummy;
    cmp_func_ty cmp_func;
    void* params;
};

/* Returns the iterator associated with the given node. */
static bst_iter_ty GetIterFromNode(bst_node_ty *node);

/* Returns the node associated with the given iterator */
static bst_node_ty *GetNodeFromIter(bst_iter_ty iter);

/* Returns 1 if the node associated with the given node has
 a left child, and 0 otherwise */
static int HasLeftChild(bst_node_ty *node);

/* Returns 1 if the node associated with the given node has
 a right child, and 0 otherwise. */
static int HasRightChild(bst_node_ty *node);

/* Returns the node pointer associated with the right child of the
 node pointer */
static bst_node_ty *GetRightNode(bst_node_ty *node);

/* Returns the node poniter associated with the left child of the 
 node pointer */
static bst_node_ty *GetLeftNode(bst_node_ty *node);


bst_ty *BSTCreate(cmp_func_ty cmp_func, void *params) 
{
    bst_ty *new_bst = NULL;

    assert (NULL != cmp_func);

    /* allocate new handle and check for failure */
    new_bst = (bst_ty *)malloc(sizeof(bst_ty));
    if (NULL == new_bst) 
    {
        return NULL;
    }
    /* allocate new dummy node and check for failure */
    new_bst->dummy = (bst_node_ty *)malloc(sizeof(bst_node_ty));
    if (NULL == new_bst->dummy) 
    {
        free(new_bst);
        return NULL;
    }

    new_bst->dummy->data = NULL;
    new_bst->dummy->child[LEFT] = NULL;
    new_bst->dummy->child[RIGHT] = NULL;
    new_bst->dummy->parent = NULL;

    /* init other members */
    new_bst->cmp_func = cmp_func;
    new_bst->params = params;

    /* return the handle */
    return new_bst;
}


void BSTDestroy(bst_ty *bst)
{
    bst_node_ty *destroy = NULL;
    bst_node_ty *parent = NULL;

    assert(NULL != bst);
    
    destroy = GetNodeFromIter(BSTIterBegin(bst));

    while(!BSTIsEmpty(bst))
    {
        if(GetRightNode(destroy))
        {
            destroy = GetRightNode(destroy);
        }
        else if(GetLeftNode(destroy))
        {
            destroy = GetLeftNode(destroy);
        }
        else
        {
            parent = destroy->parent;
            
            if (GetLeftNode(parent) == destroy)
            {
                parent->child[LEFT] = NULL;
            }
            else
            {
                parent->child[RIGHT] = NULL;
            }
            
            free(destroy);
            
            destroy = parent;
        }
    }
    
    free(bst->dummy);
    bst->dummy = NULL;
    
    free(bst);
    bst = NULL;
}


size_t BSTSize(const bst_ty *bst)
{
    size_t counter = 0;
    bst_iter_ty runner; 
    bst_node_ty *end = NULL;

    assert(NULL != bst);
    
    end = bst->dummy;
    runner = BSTIterBegin(bst);
    
    while (0 == BSTIterIsSame(runner, GetIterFromNode(end)))
    {
        ++counter;
        runner = BSTIterNext(runner);
    }
    
    return counter;
}

int BSTIsEmpty(const bst_ty *bst)
{
    assert(NULL != bst);

    /* check if the dummy node has a left child */
    return (!HasLeftChild(bst->dummy));
}

 bst_iter_ty BSTInsert(bst_ty *bst, const void *data)
{
    bst_node_ty *new_node;
    bst_node_ty *curr_node;
    int cmp_result = 0;
    int child_dir = 0;

    assert(NULL != bst);

    /* allocate new node */
    new_node = (struct bst_node *)malloc(sizeof(struct bst_node));
    if (NULL == new_node) 
    {
        return BSTIterEnd(bst);
    }

    /* init new node */
    new_node->data = (void *)data;
    new_node->child[LEFT] = NULL;
    new_node->child[RIGHT] = NULL;

    /* find the place to insert the new node and start from the root */
    curr_node = bst->dummy;
    child_dir = LEFT;
    while (NULL != curr_node->child[child_dir]) 
    {
        /* update the current node */
        curr_node = curr_node->child[child_dir];

        /* compare the new data with the current node data */
        cmp_result = bst->cmp_func(curr_node->data, (void *)data, bst->params);

        /* determine which child to follow */
        child_dir = (cmp_result > 0) ? LEFT : RIGHT;
    }

    /* insert the new node */
    curr_node->child[child_dir] = new_node;
    new_node->parent = curr_node;

    /* return the iterator to the new node */
    return GetIterFromNode(new_node);
}

void BSTRemove(bst_iter_ty iter_to_remove)
{
    bst_node_ty *node_to_remove = NULL;
    bst_node_ty *which_child = NULL, *parent = NULL;
    bst_node_ty *left_child = NULL, *right_child = NULL;                                                         
    bst_iter_ty prev_iter;
    int direction = 0;

    assert(GetNodeFromIter(iter_to_remove));

    node_to_remove = GetNodeFromIter(iter_to_remove);
    parent = node_to_remove->parent;
    left_child = GetLeftNode(node_to_remove);
    right_child = GetRightNode(node_to_remove);

    
    if (left_child && right_child)
    {   
        prev_iter = BSTIterPrev(iter_to_remove);
        node_to_remove->data = GetNodeFromIter(prev_iter)->data;
        
        node_to_remove = GetNodeFromIter(prev_iter);
        parent = node_to_remove->parent;
    }

    if (left_child)
    {
        which_child = GetLeftNode(node_to_remove);
    }
    else if (right_child)
    {
        which_child = GetRightNode(node_to_remove);
    }

    /* choose the direction by knowing what direction the parent child */
    direction = (GetRightNode(parent) == node_to_remove);
    parent->child[direction] = which_child;


    if (NULL != which_child)
    {
        which_child->parent = parent;
    }

    free(node_to_remove);
    node_to_remove = NULL;
}


bst_iter_ty BSTIterPrev(const bst_iter_ty iter)
{
    bst_node_ty *node = NULL;
    bst_node_ty *current = NULL;
    bst_node_ty *parent = NULL;

    assert(GetNodeFromIter(iter));

    /* get node from the iter */
    node = GetNodeFromIter(iter);

    /* check if the iter have left child */
    if (HasLeftChild(node))
    {
        /* if true go to the most rightest of the child and return it with get iter*/
        node = GetLeftNode(node);
        while (HasRightChild(node))
        {
            node = GetRightNode(node);
        }
        return GetIterFromNode(node);
    }
    /* the other else: */
    else
    {
        /* have your current node and parent node each time */
        current = node;
        parent = node->parent;
        /* do a while loop until you reach if the parent is NULL or 
        if the current dont equal to parent child left */
        while ((parent != NULL) && (current == GetLeftNode(parent)))
        {
             /* in the loop each time current = parent and parent = parent ->parent */
            current = parent;
            parent = parent->parent;
        }
        /* at the end return the parent with get iter */
        return GetIterFromNode(parent);
    }
}

bst_iter_ty BSTIterNext(const bst_iter_ty iter)
{
    bst_node_ty *node = NULL;
    bst_node_ty *current = NULL;
    bst_node_ty *parent = NULL;

    assert(GetNodeFromIter(iter));

    /* get node from the iter */
    node = GetNodeFromIter(iter);

    /* check if the iter have right child */
    if (GetRightNode(node))
    {
        /* if true go to the most leftes of the child and return it with get iter*/
        node = GetRightNode(node);
        while (GetLeftNode(node))
        {
            node = GetLeftNode(node);
        }
        return GetIterFromNode(node);
    }
    /* the other else: */
    else
    {
        /* have your current node and parent node each time */
        current = node;
        parent = node->parent;
        /* do a while loop until you reach if the parent is NULL or 
        if the current dont equal to parent child right */
        while ((parent != NULL) && (current == GetRightNode(parent)))
        {
             /* in the loop each time current = parent and parent = parent ->parent */
            current = parent;
            parent = parent->parent;
        }
        /* at the end return the parent with get iter */
        return GetIterFromNode(parent);
    }
}

bst_iter_ty BSTIterBegin(const bst_ty *bst)
{
    bst_node_ty *runner = NULL;
    bst_node_ty *child = NULL;

    assert(NULL != bst);

    /* DUMMY NODE */
    runner = bst->dummy;
    child = GetLeftNode(runner);
    
    while (NULL != child)
    {
        runner = child;
        child = GetLeftNode(runner);
    }
    
    return GetIterFromNode(runner);
    
}
    
bst_iter_ty BSTIterEnd(const bst_ty *bst)
{
    /* get the dummy from struct handle bst */
    bst_node_ty *dummy_curr = NULL;

    assert(NULL != bst);

    dummy_curr = bst->dummy;
    /* return the dummy */
    return GetIterFromNode(dummy_curr);
}

int BSTIterIsSame(const bst_iter_ty iter1, const bst_iter_ty iter2)
{
    /* get node of each iter */
    /* check if it is have the same data using cmp func */
    return (GetNodeFromIter(iter1) == GetNodeFromIter(iter2));
}

void *BSTIterGetData(const bst_iter_ty iter)
{
    bst_node_ty *node = NULL;

    assert(GetNodeFromIter(iter));

    node = GetNodeFromIter(iter);
    /* get node of iter */
    /* get data from the node and return it */
    return node->data;
}

bst_iter_ty BSTFind(const bst_ty *bst, const void *data_to_match)
{
    bst_node_ty *child = NULL;
    int cmp_result = 0;
    int child_dir = LEFT;

    assert(NULL != bst);

    /* start at the root */
    child = bst->dummy->child[child_dir];

    /* traverse the tree to find the matching node */
    while (NULL != child)
    {
        /* compare the data to match with the current node data */
        cmp_result = bst->cmp_func(child->data, (void *)data_to_match, bst->params);

        /* if equal, return the iterator to the current node */
        if (0 == cmp_result)
        {
            return GetIterFromNode(child);
        }

        /* determine which child to follow */
        child_dir = (cmp_result > 0) ? LEFT : RIGHT;

        /* update the current node */
        child = child->child[child_dir];
    }

    /* if not found, return the end iterator */
    return BSTIterEnd(bst);
}

int BSTForEach(bst_iter_ty from, bst_iter_ty to, action_func_ty action, void *params)
{
    int result = 0;
    bst_iter_ty current = from;

    assert(GetNodeFromIter(from));

    while (!(BSTIterIsSame(current, to)))
    {
        result = action(BSTIterGetData(current), params);
        if (SUCCESS != result)
        {
            return FAIL;
        }
        current = BSTIterNext(current);
    }
    return SUCCESS;
}

/******************************************************************************/
static bst_node_ty *GetLeftNode(bst_node_ty *node)
{
    assert(NULL != node);

    return node->child[LEFT];
}
static bst_node_ty *GetRightNode(bst_node_ty *node)
{  
    assert(NULL != node);

    return node->child[RIGHT];
}

static int HasLeftChild(bst_node_ty *node)
{
    assert(NULL != node);

    return (NULL != node->child[LEFT]);
}

static int HasRightChild(bst_node_ty *node)
{
    assert(NULL != node);

    return (NULL != node->child[RIGHT]);
}

static bst_iter_ty GetIterFromNode(bst_node_ty *node)
{
    bst_iter_ty iter;

    assert(NULL != node);

    iter.node = node;
    return iter;
}

static bst_node_ty *GetNodeFromIter(bst_iter_ty iter)
{
    return iter.node;
}

