/******************************************************************/
/*Date: 11.12.22*/
/*Author: Aviv Jilin*/
/*reviewer: Nir */
/*version: 1.0*/
/*****************************************************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */


#include "dynamic_vector.h"

#define GROWTH_FACTOR 2

struct d_vector
{
    size_t capacity;
    size_t num_occupied_elem;
    size_t element_size;
    void *data_array;
};

/****************************Vector***************************************************************/
 
d_vector_ty *VectorCreate(size_t capacity, size_t element_size)
{
    d_vector_ty *vector_ptr = (d_vector_ty *)malloc(sizeof(d_vector_ty));
    if (NULL == vector_ptr)
    {
        return NULL;
    }
    vector_ptr -> data_array = (void *)malloc(element_size * capacity);
    if (NULL == vector_ptr -> data_array)
    {
        free(vector_ptr);
        return NULL;
    }

    vector_ptr -> capacity = capacity;
    vector_ptr -> num_occupied_elem = 0;
    vector_ptr -> element_size = element_size;

    return vector_ptr;
}

void VectorDestroy(d_vector_ty *vector_ptr)
{
    assert(NULL != vector_ptr);
    free(vector_ptr -> data_array);
    vector_ptr -> data_array = NULL;
    free(vector_ptr);
    vector_ptr = NULL;
}

int VectorPushBack(d_vector_ty *vector_ptr, const void *element)
{
    void *start_ptr = NULL;
    size_t new_capacity = GROWTH_FACTOR * vector_ptr->capacity;

    assert(NULL != vector_ptr);

    if (vector_ptr->capacity == vector_ptr->num_occupied_elem)
    {
        vector_ptr = VectorReserve(vector_ptr, new_capacity);
        if (NULL == vector_ptr)
        {
            return 1;
        }
    }
    start_ptr = vector_ptr -> data_array;

    vector_ptr -> data_array = (void *)((char *)vector_ptr -> data_array
        + (vector_ptr -> num_occupied_elem * vector_ptr -> element_size));

    memcpy(vector_ptr -> data_array, element, vector_ptr -> element_size);

    vector_ptr -> num_occupied_elem = vector_ptr -> num_occupied_elem + 1;

    vector_ptr -> data_array = start_ptr;

    return 0;
}

void VectorPopBack(d_vector_ty *vector_ptr)
{
    assert(NULL != vector_ptr);
    vector_ptr -> num_occupied_elem = vector_ptr -> num_occupied_elem - 1;
}

void *VectorGetAccessToElement(const d_vector_ty *vector_ptr, size_t index)
{
    void *dest_addr = NULL;
    assert(NULL != vector_ptr);
    dest_addr = ((char *)vector_ptr -> data_array + (index * vector_ptr -> element_size));
    return (void *)dest_addr; 
}

size_t VectorGetSize(const d_vector_ty *vector_ptr)
{
    assert(NULL != vector_ptr);
    return vector_ptr -> num_occupied_elem;
}

size_t VectorGetCapacity(const d_vector_ty *vector_ptr)
{
    assert(NULL != vector_ptr);
    return vector_ptr -> capacity;    
}

d_vector_ty *VectorReserve(d_vector_ty *vector_ptr, size_t new_capacity)
{

    assert(NULL != vector_ptr);

    if (vector_ptr -> capacity < new_capacity)
    {
        vector_ptr -> data_array = (void *)realloc(vector_ptr -> data_array, 
            vector_ptr -> element_size * new_capacity);
    
        if (NULL == vector_ptr -> data_array)
        {
            VectorDestroy(vector_ptr);
            return NULL;  
        }

        vector_ptr -> capacity = new_capacity;
    }

    return vector_ptr;
}

d_vector_ty *VectorShrinkToFit(d_vector_ty *vector_ptr)
{
    assert(NULL != vector_ptr);
    vector_ptr -> data_array = (void *)realloc(vector_ptr -> data_array, 
        vector_ptr -> element_size * vector_ptr -> num_occupied_elem);
    if (NULL == vector_ptr -> data_array)
    {
        VectorDestroy(vector_ptr);
        return NULL;  
    }

    vector_ptr -> capacity = vector_ptr -> num_occupied_elem;
    return vector_ptr;    
}




