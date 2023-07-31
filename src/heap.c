/*******************************************************************************
Project:    Heap
Author:     AvivJilin
Reviewer:   
Version:    1.0 - 14/02/2023
version:    1.1 - 16/02/2023 add comments and HeapifyDown
*******************************************************************************/
#include <stddef.h>    /* size_z        */
#include <sys/types.h> /*  ssize_t      */
#include <stdlib.h>    /* malloc, free  */
#include <assert.h>    /* assert        */

#include "heap.h"
#include "dynamic_vector.h"

#define CAPACITY 30

enum status {SUCCESS = 0, FAILURE = 1};

enum found {NOTFOUND = -1, FOUND = 1};

enum bool_status{FALSE = 0, TRUE = 1};

struct heap
{
    d_vector_ty *d_vector;
    heap_cmp_func_ty cmp_func;
};
/********************************static functions******************************/

/* Get parent of idx */
static int GetParent(int idx);

/* Get left child idx */
static int GetLeftChild(int idx);

/* Get right child idx */
static int GetRightChild(int idx);

/* Heapify up */
static void HeapifyUp(const heap_ty *heap, int idx);

/* Heapify down */
static void HeapifyDown(const heap_ty *heap, int idx);

/* Vector swap data */
static void VectorSwap(void **data, void **data2);

/* Heap find */
static ssize_t HeapFind(heap_ty *heap, heap_is_match_func_ty match_func,
                                                            const void *data);
                                                            
/* Comparison between two data */                                                            
static int Comparison(const heap_ty *heap, void *data, void *data2);

/* Get data */
static void *GetData(const heap_ty *heap, int idx);

/* Check if have child */
static int CheckIfValidIdx(size_t idx, size_t size);

/* check if right child is valid and if so comapre it to the left child */
static int IfValidRightCompare(const heap_ty *heap, void *data_left, 
                               void *data_right, int right_child_idx, int size);

/*******************************************************************************/

heap_ty *HeapCreate(heap_cmp_func_ty cmp_func)
{
    d_vector_ty *vector = NULL;
    /* allocate new heap_ty and check the allocate */
    heap_ty *heap = NULL;

    assert(NULL != cmp_func);
    
    heap = (heap_ty *)malloc(sizeof(heap_ty));
    if (NULL == heap)
    {
        return NULL;
    }

    /* create new dynamic vector and check the allocation */
    vector = VectorCreate(CAPACITY, sizeof(void *));

    if (NULL == vector)
    {
        free(heap);
        heap = NULL;
    }

    /* init the heap with cmp func and the dynamic vector */
    heap->d_vector = vector;
    heap->cmp_func = cmp_func;

    return heap;
    /* return the heap */

}

void HeapDestroy(heap_ty *heap)
{
    assert(NULL != heap);

    /* destroy the dynamic vector */
    VectorDestroy(heap->d_vector);

    heap->d_vector = NULL;
    heap->cmp_func = NULL;

    /* then free the heap struct */
    free(heap);

    /* dangling pointer */
    heap = NULL;
}

int HeapPush(heap_ty *heap, const void *data)
{
    int index = 0;
    int res = 0;

    assert(NULL != heap);
    assert(NULL != data);

    /* push the data to the end of the vector */
    res = VectorPushBack(heap->d_vector, data);
    
    if(FAILURE == res)
    {
    	return FAILURE;
    }
    
    /* get the last occupied index */
    index = VectorGetSize(heap->d_vector) - 1;

    /* use function HeapUp with the last occupied index*/
    HeapifyUp(heap, index);

    return SUCCESS;
}

void HeapPop(heap_ty *heap)
{
    size_t last_index = 0;
    void **root_data = NULL;
    void **last_data = NULL;

    assert(NULL != heap);
    assert(!HeapIsEmpty(heap));

    last_index = VectorGetSize(heap->d_vector) - 1;
    root_data = GetData(heap, 0);
    last_data = GetData(heap, last_index);

    /* swap the first element in the dynamic vector with the last */
    VectorSwap(root_data, last_data);

    /* pop the last element in the d_vector */
    VectorPopBack(heap->d_vector); 

    /* do heapdown for the top */
    HeapifyDown(heap, 0);          
}

void *HeapPeek(const heap_ty *heap)
{
    void *data = NULL;

    assert(NULL != heap);
    assert(!HeapIsEmpty(heap));

    data = GetData(heap, 0);
    /* use the function VectorGetAccessToElement with the index zero */ 

    return data;   
}

void *HeapRemove(heap_ty *heap, heap_is_match_func_ty match_func, const void *data)
{
    ssize_t index_found = 0;
    size_t last_index = 0;
    void **current_data = NULL;
    void **removed_data = NULL;
    void *return_data = NULL;

    assert(NULL != heap);
    assert(NULL != match_func);
    assert(NULL != data);

    /* first find the element to remove */
    index_found = HeapFind(heap, match_func, data);

    if (NOTFOUND == index_found)
    {
        return NULL;
    }

    last_index = HeapSize(heap) - 1;
    removed_data = GetData(heap, index_found);
    current_data = GetData(heap, last_index);
    
    return_data = *removed_data;

    /* when find the data swap the data from it to the last element */
    VectorSwap(removed_data, current_data);
    
    /* use dynamic pop back to remove the last element */
    VectorPopBack(heap->d_vector);

    if (!HeapIsEmpty(heap) && (HeapSize(heap) != (size_t)index_found))
    {
        HeapifyDown(heap, index_found);
    }

    return return_data;
}

static ssize_t HeapFind(heap_ty *heap, heap_is_match_func_ty match_func,
                                                            const void *data)
{
    size_t idx = 0;
    size_t size = 0;
    void *data_to_find = NULL;
    void *data_to_match = NULL;
    int result = 0;

    data_to_find = (void *)data;
    size = VectorGetSize(heap->d_vector);

    /*  for each element in heap (idx = 0; idx < HeapSize; ++idx)             */
    for (idx = 0; idx < size; ++idx)
    {
        /*  get ptr to element using VectorGetAccessToElement                 */
        data_to_match = GetData(heap, idx);

        /*  use match_func on element_ptr and data                            */
        result = match_func(data_to_match, data_to_find);

        if (FOUND == result)
        {
            return idx;
            /*  if match found - return idx                                    */
        }
    }
    /*  return NOT_FOUND                                                      */
    return NOTFOUND;
}

int HeapIsEmpty(const heap_ty *heap)
{
    assert(NULL != heap);

    /* use the function vector get size, and if zero, return true */
    if (0 == VectorGetSize(heap->d_vector))
    {
        return TRUE;
    }

    return FALSE;  
}

size_t HeapSize(const heap_ty *heap)
{
    size_t size = 0;

    assert(NULL != heap);

    /* use the function vector get size */
    size = VectorGetSize(heap->d_vector);

    return size;   
}



static void HeapifyUp(const heap_ty *heap, int idx)
{
    void **parent_data = NULL;
    void **current_data = NULL;
    int parent_idx = 0;

    assert(NULL != heap);

    /* While the current element is not at the root of the heap */
    while (idx > 0)
    {
        parent_idx = GetParent(idx);
        parent_data = GetData(heap, parent_idx);
        current_data = GetData(heap, idx);

        /* Compare the current element with its parent */
        if (Comparison(heap, current_data, parent_data) > 0)
        {                                                                       
            /* Swap the current element with its parent */
            VectorSwap(current_data, parent_data);
            /* Update the current index to the new position */
            idx = parent_idx;
        }
        else
        {
            /* The current element is in its correct position in the heap */
            break;
        }
    }
}

static void HeapifyDown(const heap_ty *heap, int idx)
{
    int max_child_idx = 0;
    int left_child_idx = 0;
    int right_child_idx = 0;
    size_t size = 0;
    void **data_idx = NULL;
    void **data_max_child_idx = NULL;
    void *data_left = NULL;
    void *data_right = NULL;

    assert(NULL != heap);

    /* get the left child index */
    left_child_idx = GetLeftChild(idx);

    /* get the right child index */
    right_child_idx = GetRightChild(idx);

    /* get the vector size */
    size = VectorGetSize(heap->d_vector);

    /* check while left child index is smaller than vectorsize */
    while (CheckIfValidIdx(left_child_idx, size))
    {
        /* mac_child_idx get as left_child_idx; */
        max_child_idx = left_child_idx;

        data_left = GetData(heap, left_child_idx);
        data_right = GetData(heap, right_child_idx);

        /* check if right_idxss is smaller than size and the right child is bigger */
        if (IfValidRightCompare(heap, data_left, data_right, right_child_idx, size))
        {
            max_child_idx = right_child_idx;
        }

        data_idx = GetData(heap, idx);
        data_max_child_idx = GetData(heap, max_child_idx);

        /* check if max_child_index is bigger the current index */
        if (Comparison(heap, data_idx, data_max_child_idx) < 0)
        {
            /* do a swap with between max_child_idx and idx */
            VectorSwap(data_idx, data_max_child_idx);

            /* get again the indexes */
            idx = max_child_idx;
            
            left_child_idx = GetLeftChild(idx);
            right_child_idx = GetRightChild(idx);
        }
        else
        {
            /* break if max_child_index is smaller */
            break;
        }
    }
}

static int GetParent(int idx)
{
    if (0 == idx)
    {
        return 0;
    }
    return (idx - 1)/2;
}

static int GetLeftChild(int idx)
{
    return (2 * idx + 1);
}

static int GetRightChild(int idx)
{
    return (2 * idx + 2);
}

static void VectorSwap(void **data, void **data2) 
{
    void *temp = *data;

    *data = *data2;

    *data2 = temp;
}

static int Comparison(const heap_ty *heap, void *data, void *data2)
{
    return heap->cmp_func(data, data2);
}

static void *GetData(const heap_ty *heap, int idx)
{
    return VectorGetAccessToElement(heap->d_vector, idx);    
}

static int CheckIfValidIdx(size_t idx, size_t size)
{
    return idx < size;
}

static int IfValidRightCompare(const heap_ty *heap, void *data_left, 
                                void *data_right, int right_child_idx, int size)
{
    if(CheckIfValidIdx(right_child_idx, size) 
                                && Comparison(heap, data_left, data_right) < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

