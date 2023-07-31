/*******************************************************************************
 * Author:      HRD28
 * Version:     1.1
*******************************************************************************/
#ifndef __DYNAMIC_VECTOR_H__
#define __DYNAMIC_VECTOR_H__

#include <stddef.h>     /*  size_t  */

/*  dynamic vector struct   */
typedef struct d_vector d_vector_ty;

/*******************************************************************************
 *  create a dynamic vector - receives element size and capacity
 *  return NULL if failed
*******************************************************************************/
d_vector_ty *VectorCreate(size_t capacity, size_t element_size);

/*******************************************************************************
 *  frees all dynamic allocated resources used by the vector
 *  note: undefined behaviour if "vector_ptr" is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
void VectorDestroy(d_vector_ty *vector_ptr);

/******************************************************************************* 
 *  insert element to the end of the vector 
 *  allocates extra memory if needed
 *  note: undefined behaviour if vector or element are NULL
 *  returns 0 if succeeded, otherwise not equal to 0
*******************************************************************************/
int VectorPushBack(d_vector_ty *vector_ptr, const void *element);

/******************************************************************************* 
 *  remove last element in vector 
 *  note: undefined behaviour if vector is empty or NULL
 *  Time Complexity: O(1)
*******************************************************************************/
void VectorPopBack(d_vector_ty *vector_ptr);

/*******************************************************************************
 *  return pointer to a specific "index" inside the vector
 *  note:   undefined behaviour if vector is empty or NULL, or if "index" is
 *          larger than current vector size or negative
 *  Time Complexity: O(1)
*******************************************************************************/
void *VectorGetAccessToElement(const d_vector_ty *vector_ptr, size_t index);

/******************************************************************************* 
 *  returns the number of occupied elements in the vector 
 *  note:   undefined behaviour if vector is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
size_t VectorGetSize(const d_vector_ty *vector_ptr);

/******************************************************************************* 
 *  returns the current capacity of the vector 
 *  note:   undefined behaviour if vector is NULL
 *  Time Complexity: O(1)
*******************************************************************************/
size_t VectorGetCapacity(const d_vector_ty *vector_ptr);

/******************************************************************************* 
 *  increases vector capacity to "new_capacity"
 *  return NULL if failed
 *  note:   if new_capacity is smaller than current capacity, nothing happens
            undefined behaviour if vector is NULL
*******************************************************************************/
d_vector_ty *VectorReserve(d_vector_ty *vector_ptr, size_t new_capacity);

/******************************************************************************* 
 *  removes unused space from the vector 
 *  return NULL if failed
 *  note:   undefined behaviour if vector is empty or NULL
*******************************************************************************/
d_vector_ty *VectorShrinkToFit(d_vector_ty *vector_ptr);

#endif  /*  __DYNAMIC_VECTOR_H__    */