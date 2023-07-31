/******************************************************************/
/*Date: 07.12.22*/
/*Author: Aviv Jilin*/
/*reviewer: Lital */
/*version: 1.0*/
/*****************************************************************/

#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */


/*#include "../include/bit_arr.h"  API */
#include "stack.h"

/*typedef struct stack
{
    size_t capacity;
    size_t num_occupied_elem;
    size_t element_size;
    void *data_array;
}stack_ty;*/

stack_ty *StackCreate(size_t capacity, size_t element_size)
{
    stack_ty *stack = NULL;

    assert(capacity > 0);
    /*pseudo: allocate memory for stack struct (size of struct).
    check allocation.*/
    stack = (stack_ty *)malloc(sizeof(stack_ty));

    if (NULL == stack)
    {   
        return NULL;
    }
    /* allocate array (size of element * capacity)
    if failed, free struct.*/
    stack->data_array = malloc(capacity * element_size);


    if (NULL == stack->data_array)
    {   
        free(stack);
        return NULL;
    }
    /*init fields */
    stack->num_occupied_elem = 0;
    stack->element_size = element_size;
    stack->capacity = capacity;
    /*return struct pointer.*/
    return stack;
}


void StackDestroy(stack_ty *stack_ptr)
{
    assert(stack_ptr);

    free(stack_ptr->data_array);
    stack_ptr->data_array = NULL;

    free(stack_ptr);
    stack_ptr = NULL;
}


void StackPush(stack_ty *stack_ptr, const void *element)
{
    /*pseudo: assign value to stack's top
    change stack location (size/ptr)*/
    void *start = stack_ptr->data_array; 

    assert(stack_ptr);

    /* need to make the offset to the pointer: data array, 
    to fill the element in place,
    cast all the expressions to "void *", and cast the sub expression 
    to "char *" (1 byte), and add element size multiply by the size */ 
    stack_ptr->data_array = (void *)((unsigned char *)stack_ptr->data_array
     + (stack_ptr->num_occupied_elem * stack_ptr->element_size));

    /* memmove to copy the element to the data array, element_size times */
    memmove(stack_ptr->data_array, element, stack_ptr->element_size);
    
    /*return the data_array pointer to the start */
    stack_ptr->data_array = start;

    stack_ptr->num_occupied_elem = stack_ptr->num_occupied_elem + 1; /*increment word size */
}


void StackPop(stack_ty *stack_ptr)
{
    /*pseudo:
    change stuck location*/
    assert(stack_ptr);
    

   /*(size_t)(stack_ptr->data_array) + stack_ptr->num_occupied_elem * stack_ptr->element_size = NULL;
*/
    stack_ptr->num_occupied_elem = stack_ptr->num_occupied_elem - 1;

}

void *StackPeek(const stack_ty *stack_ptr)
{
    /*pseudo: return stack top location minus element size */
                /* peek to stack_ptr->arr in place size -1 */
    void *peek = (void *)((unsigned char *)stack_ptr->data_array
     + ((stack_ptr->num_occupied_elem - 1) * stack_ptr->element_size));


    return peek; 
}

size_t StackGetSize(const stack_ty *stack_ptr)
{
    /*pseudo: return size*/
    return stack_ptr->num_occupied_elem;
}


int StackIsEmpty(const stack_ty *stack_ptr)
{
    /*pseudo: return size == 0 */
    return !(stack_ptr -> num_occupied_elem);  
}


size_t StackGetCapacity(const stack_ty *stack_ptr)
{
    /*pseudo: return capacity */
    return stack_ptr->capacity;
}



