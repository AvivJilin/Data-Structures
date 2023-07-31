/*******************************************************************************
Project:    AVL
Author:     Aviv Jilin
Tester:     Nir
Version:    1.0 - 06/02/2023
*******************************************************************************/
#include <sys/types.h> /*  ssize_t      */
#include <stdlib.h> /* malloc ,free, max */
#include <assert.h> /* assert       */

#include "avl.h"

typedef enum children_enum {LEFT = 0, RIGHT = 1, NUM_CHILDREN = 2} children_ty;

enum state {SUCCESS = 0, FAIL = 1};

enum bool_var {FALSE = 0, TRUE = 1};

typedef struct avl_node
{
    void *data;
    struct avl_node *child[NUM_CHILDREN];
    ssize_t height;
} avl_node_ty;

struct avl
{
    avl_node_ty *root;
    cmp_func_ty cmp_func;
};

/******************************Static Functions********************************/

static void AVLDestroyImp(avl_node_ty *node);

static size_t AVLSizeImp(const avl_node_ty *node);

static avl_node_ty *AVLInsertImp(avl_node_ty *node, const void *data, cmp_func_ty cmp_func, avl_node_ty *new_node);

static int AVLFindImp(const avl_node_ty *node, const void *data_to_match, 
                     cmp_func_ty cmp_func);

static ssize_t MaxHeight(ssize_t a, ssize_t b);

static int AVLForEachPreOrder(const avl_node_ty *node, action_func_ty action, void *params);

static int AVLForEachInOrder(const avl_node_ty *node, action_func_ty action, void *params);

static int AVLForEachPostOrder(const avl_node_ty *node, action_func_ty action, void *params);

static void UpdateHeight(avl_node_ty *node);

static avl_node_ty *CreateAndInitNode(const void *data);

static avl_node_ty *AVLRemoveImp(avl_node_ty *node, void *data_to_remove, cmp_func_ty cmp_func);

static int IsLeaf(avl_node_ty *node);

static void *GetMaxData(avl_node_ty *node);

static void *GetMinData(avl_node_ty *node);

static int AVLGetBalance(avl_node_ty *node);

static avl_node_ty *AVLRightRotate(avl_node_ty *node);

static avl_node_ty *AVLLeftRotate(avl_node_ty *node);

static avl_node_ty* Balance(avl_node_ty *node);

static avl_node_ty* GetRight(avl_node_ty *node);

static avl_node_ty* GetLeft(avl_node_ty *node);

static ssize_t GetHeight(avl_node_ty *node);

avl_ty *AVLCreate(cmp_func_ty cmp_func)
{
    avl_ty *new_avl = NULL;

    assert (NULL != cmp_func);

    /* allocate new handle and check for failure */
    new_avl = (avl_ty *)malloc(sizeof(avl_ty));
    if (NULL == new_avl) 
    {
        return NULL;
    }

    /* init root node */
    new_avl->root = NULL;

    /* init other members */
    new_avl->cmp_func = cmp_func;

    /* return the handle */
    return new_avl;
}

void AVLDestroy(avl_ty *avl)
{
    assert(NULL != avl);
    
    AVLDestroyImp(avl->root);

    free(avl);
    avl = NULL;
}

void AVLDestroyImp(avl_node_ty *node)
{
    /* AVLDestroyImp should have the base that it is node == NULL just return */
    if (node == NULL)
    {
        return;
    }

    /* dig left recusively with left child */
    AVLDestroyImp(GetLeft(node));

    /* dig right recusively with righ child */
    AVLDestroyImp(GetRight(node));

    /* free(node); */
    free(node);

    /* node = NULL */
    node = NULL; 
}


size_t AVLSize(const avl_ty *avl)
{
    assert(NULL != avl);

    /* call the AVLSizeImp function that is recursive */
    return AVLSizeImp(avl->root);
}

size_t AVLSizeImp(const avl_node_ty *node) 
{
    /* ravlsizeimp the base check is if node is null return 0 */ 
    if (NULL == node) 
    {
        return 0;
    }
    /* then return dig left recusively with left child 
            + dig right recusively with right child + 1 */
    return AVLSizeImp(node->child[LEFT]) + AVLSizeImp(node->child[RIGHT]) + 1;
}

int AVLIsEmpty(const avl_ty *avl)
{
    assert(NULL != avl);
    /* check if avl->root->data is NULL if so it is true and return 1 */
    if (NULL == avl->root) 
    {
        return TRUE;
    } 
    /* otherwise return 0 */
    return FALSE;

}

ssize_t AVLHeight(const avl_ty *avl)
{
    if (AVLIsEmpty(avl))
    {
        return -1; /* -1 means empty */
    }
    return avl->root->height;
}

int AVLInsert(avl_ty *avl, const void *data) 
{
  avl_node_ty *new_node = NULL; 

  assert(NULL != avl);

  new_node = CreateAndInitNode(data);
  if (NULL == new_node) 
  {
    return FAIL;
  }

  avl->root = AVLInsertImp(avl->root, data, avl->cmp_func, new_node);

  return SUCCESS;
}

static avl_node_ty *AVLInsertImp(avl_node_ty *node, const void *data, cmp_func_ty cmp_func, avl_node_ty *new_node)
{
    int comparison = 0;
    /* base check if untill node data is NULL*/
    if (NULL == node) 
    {
        return new_node;
    }

    /* put in variable res and each time compare between data and *root->data */
    comparison = cmp_func((void *)data, node->data);

    /* if res is smaller from zero go left recursively using left child*/
    if (comparison < 0) 
    {
        node->child[LEFT] = AVLInsertImp(GetLeft(node), data, cmp_func, new_node);
        /* if res is bigger then zero go right recursively using right child */
    } 
    else if (comparison > 0) 
    {
        node->child[RIGHT] = AVLInsertImp(GetRight(node), data, cmp_func, new_node);
    } 
    else 
    {
        free(new_node);
        new_node = NULL;
        /* data already exists in the tree */
        return node;
    }

    UpdateHeight(node);

    node = Balance(node);

    return node;
}

static void UpdateHeight(avl_node_ty *node)
{
    if (NULL != node)
    { 
        node->height = 1 + MaxHeight((GetHeight(GetLeft(node))), 
                                                (GetHeight(GetRight(node))));
    }
}

static ssize_t MaxHeight(ssize_t a, ssize_t b) 
{
    return (a > b) ? a : b;
}

avl_node_ty *CreateAndInitNode(const void *data)
{
    avl_node_ty *new_node = NULL; 

    new_node = (avl_node_ty *)malloc(sizeof(avl_node_ty));
    if (NULL == new_node) 
    {
        return NULL;
    }

    new_node->data = (void *)data;
    new_node->child[LEFT] = NULL;
    new_node->child[RIGHT] = NULL;
    new_node->height = 0;

    return new_node;    
} 

int AVLGetBalance(avl_node_ty *node)
{
    size_t height_left = 0;
    size_t height_right = 0;
    /* check if node == NULL then return 0 */
    if (NULL == node)
    {
        return -1;
    }
    /* get height from node left */
    height_left = GetHeight(GetLeft(node));
    /* get height from node right */
    height_right = GetHeight(GetRight(node));

    /* return left height - right height */
    return height_left - height_right;
}

avl_node_ty *AVLRightRotate(avl_node_ty *node) 
{
    avl_node_ty *left_subtree = NULL;
    avl_node_ty *right_subtree_from_left_subtree = NULL;

    if(NULL == node)
    {
        return NULL;
    }

    /* get the left_subtree*/
    left_subtree = GetLeft(node);
    /* get the right subtree from left subtree*/
    right_subtree_from_left_subtree = GetRight(left_subtree);

    /* Perform rotation */
    /* left_subtree -> right =  node */
    left_subtree->child[RIGHT] = node;

    /* node -> left = right subtree from left subtree */
    node->child[LEFT] = right_subtree_from_left_subtree;

    /* Update heights */
    /* node->height is the max height from node left or node right + 1; */
    UpdateHeight(node);

    /* left_subtree->height is the max height from left subtree or right sub tree + 1; */
    UpdateHeight(left_subtree);

    /* Return new node that is left_subtree */
    return left_subtree;
}

avl_node_ty *AVLLeftRotate(avl_node_ty *node) 
{
    avl_node_ty *right_subtree = NULL;
    avl_node_ty *left_subtree_from_right_subtree = NULL;

    if(NULL == node)
    {
        return NULL;
    }

    /* get the right_subtree*/
    right_subtree = GetRight(node);
    /* get the left subtree from right subtree*/
    left_subtree_from_right_subtree = GetLeft(right_subtree);


    /* Perform rotation */
    /* right_subtree -> left =  node */
    right_subtree->child[LEFT] = node;

    /* node -> right = left subtree from right subtree */
    node->child[RIGHT] = left_subtree_from_right_subtree;

    /* Update heights */
    /* node->height is the max height from node left or node right + 1; */
    UpdateHeight(node);

    /* right_subtree->height is the max height from right subtree left or right sub tree right + 1; */
    UpdateHeight(right_subtree);

    /* Return new node that is right_subtree */
    return right_subtree;
}

avl_node_ty* Balance(avl_node_ty *node) 
{
    int balance = 0;

    balance = AVLGetBalance(node);

    if (balance > 1) /* left heavy of node */
    {
        if (AVLGetBalance(GetLeft(node)) < 0) /* right heavy of child */
        {
            node->child[LEFT] = AVLLeftRotate(GetLeft(node));
            return AVLRightRotate(node);
        }
        else 
        {
            /* left heavy of child */
            return AVLRightRotate(node);
        }
    }


    if (balance < -1) /* right heavy of node */
    {
        if (AVLGetBalance(GetRight(node)) > 0) /* left heavy of child */
        {
            node->child[RIGHT] = AVLRightRotate(GetRight(node));
            return AVLLeftRotate(node); 
        }
        else
        {
            /* right heavy of child */
            return AVLLeftRotate(node);   
        }
    }

    return node;
}


void AVLRemove(avl_ty *avl, const void *data_to_remove)
{
    assert(NULL != avl);

    avl->root = AVLRemoveImp(avl->root, (void *)data_to_remove, avl->cmp_func);
}


avl_node_ty *AVLRemoveImp(avl_node_ty *node, void *data_to_remove, cmp_func_ty cmp_func)
{
    int compare_res = 0;
    void *max_data = NULL;
    void *min_data = NULL;
    
    if (NULL == node)
    {
        return node;  
    } 
    
    compare_res = (cmp_func((void *)data_to_remove, node->data));
    
    if (IsLeaf(node))
    {
        free(node);
        node = NULL;
        
        return node;
    }
    
    if(compare_res > 0)
    {
        node->child[RIGHT] = AVLRemoveImp(GetRight(node), data_to_remove, cmp_func);
        
        return node;
    }
    else if(compare_res < 0)
    {
        node->child[LEFT] = AVLRemoveImp(GetLeft(node), data_to_remove, cmp_func);

        return node;
    }
    
    if (NULL != GetLeft(node))
    {
        max_data = GetMaxData(GetLeft(node));
        
        node->data = max_data;
        
        node->child[LEFT] = AVLRemoveImp(GetLeft(node), max_data, cmp_func);
    }
    else
    {
        min_data = GetMinData(GetRight(node));
        
        node->data = min_data;
        
        node->child[RIGHT] = AVLRemoveImp(GetRight(node), min_data, cmp_func);
    }

    UpdateHeight(node);
    
    node = Balance(node);

    return node;
}

int IsLeaf(avl_node_ty *node)
{  
    return (node->child[LEFT] == NULL && node->child[RIGHT] == NULL);
}

void *GetMaxData(avl_node_ty *node)
{
    if (NULL != node->child[RIGHT])
    {
        return GetMaxData(node->child[RIGHT]);
    }
    
    return node->data;
}

void *GetMinData(avl_node_ty *node)
{
    if (NULL != node->child[LEFT])
    {
        return GetMinData(node->child[LEFT]);
    }
    
    return node->data;
}


int AVLFind(const avl_ty *avl, const void *data_to_match)
{
    /* call avlfind recursive */
    return AVLFindImp(avl->root, data_to_match, avl->cmp_func);
}

int AVLFindImp(const avl_node_ty *node, const void *data_to_match, 
                     cmp_func_ty cmp_func)
{
    int comparison = 0;

    /* base if is until node == NULL then return 0 that is not fount */
    if (NULL == node) 
    {
        /* Tree is empty */
        return FAIL;
    }

    /* each time do cmp for data_to_match and node->data */
    comparison = cmp_func((void *)data_to_match, node->data);

    if (comparison < 0) 
    {
        /* Search the left subtree */
        return AVLFindImp(GetLeft((avl_node_ty *)node), data_to_match, cmp_func);
    }
    else if (comparison > 0)
    {
        /* Search the right subtree */
        return AVLFindImp(GetRight((avl_node_ty *)node), data_to_match, cmp_func);
    }
    else
    {
        /* Found */
        return SUCCESS;
    }
}


int AVLForEach(avl_ty *avl, order_ty order,
                                        action_func_ty action, void *params) 
{
    int ret = SUCCESS;

    assert(NULL != avl);

    switch (order) 
    {
        case PRE:
            ret = AVLForEachPreOrder(avl->root, action, params);
            break;
        case IN:
            ret = AVLForEachInOrder(avl->root, action, params);
            break;
        case POST:
            ret = AVLForEachPostOrder(avl->root, action, params);
            break;
        default:
            ret = FAIL;
            break;
    }
    return ret;
}

static int AVLForEachPreOrder(const avl_node_ty *node, 
                                            action_func_ty action, void *params) 
{
    /* base if is untill node == NULL return zero */
    if (NULL == node) 
    {
        return SUCCESS;
    }
    /* each time do action on node data */
    if (action(node->data, params) != SUCCESS) 
    {
        return FAIL;
    }
    /* recursively dig left */
    if (AVLForEachPreOrder(node->child[LEFT], action, params) == FAIL) 
    {
        return FAIL;
    }
    /* recursively dig right */
    if (AVLForEachPreOrder(node->child[RIGHT], action, params) == FAIL) 
    {
        return FAIL;
    }
    return SUCCESS;
}

static int AVLForEachInOrder(const avl_node_ty *node, action_func_ty action, void *params) 
{
    /* base if is untill node == NULL return zero */
    if (NULL == node) 
    {
        return SUCCESS;
    }
    /* recursively dig left */
    if (AVLForEachInOrder(node->child[LEFT], action, params) == FAIL) 
    {
        return FAIL;
    }
    /* each time do action on node data */
    if (action(node->data, params) != SUCCESS) 
    {
        return FAIL;
    }
    /* recursively dig right */
    if (AVLForEachInOrder(node->child[RIGHT], action, params) == FAIL) 
    {
        return FAIL;
    }
    return SUCCESS;
}

static int AVLForEachPostOrder(const avl_node_ty *node, action_func_ty action, void *params) 
{
    if (NULL == node) 
    {
        return SUCCESS;
    }
    /* recursively dig left */
    if (AVLForEachPostOrder(node->child[LEFT], action, params) == FAIL) 
    {
        return FAIL;
    }
    /* recursively dig right */
    if (AVLForEachPostOrder(node->child[RIGHT], action, params) == FAIL) 
    {
        return FAIL;
    }
    /* each time do action on node data */
    if (action(node->data, params) != SUCCESS) 
    {
        return FAIL;
    }
    return SUCCESS;
}

static avl_node_ty* GetRight(avl_node_ty *node)
{
    if (NULL == node)
    {
        return NULL;
    }
    return node->child[RIGHT];
}

static avl_node_ty* GetLeft(avl_node_ty *node)
{
    if (NULL == node)
    {
        return NULL;
    }
    return node->child[LEFT];
}

static ssize_t GetHeight(avl_node_ty *node)
{
    if(NULL == node)
    {
        return -1;
    }
    return node->height;
}


