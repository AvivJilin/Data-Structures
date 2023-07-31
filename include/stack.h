/*
*   Author: HRD28
*   Version: 1.1
*/
#ifndef __STACK_H__
#define __STACK_H__
 
#include <stddef.h>   /* size_t */
 


/* stack struct */
typedef struct stack stack_ty;

      

/************************************************************************ 
*   create stack - receives element size and capacity 
*   return NULL if failed - for success - return ptr to stack handler 
*************************************************************************/
stack_ty *StackCreate(size_t capacity, size_t size_of_element);

/************************************************************************
*   free all dynamic allocated resources used by the stack
*   note: undefined behaviour if stack is empty
*   or stack is NULL
*************************************************************************/
void StackDestroy(stack_ty *stack_ptr);

/************************************************************************ 
*   insert element to the top of the stack 
*   undefined behaviour if stack is full
*   or element is NULL
*************************************************************************/
void StackPush(stack_ty *stack_ptr, const void *element);

/************************************************************************ 
*   remove last element in stack 
*   note: undefined behaviour if stack is empty
*   or stack is NULL
*   Time Complexity: O(1)
*************************************************************************/
void  StackPop(stack_ty *stack_ptr);

/************************************************************************ 
*   return pointer to last element in the stack
*   note: undefined behaviour if stack is empty
*   or stack is NULL
*   Time Complexity: O(1)
*************************************************************************/
void *StackPeek(const stack_ty *stack_ptr);

/************************************************************************ 
*   return number of occupied elements in the stack 
*   note: undefined behaviour if stack is empty
*   or stack is NULL
*************************************************************************/
size_t StackGetSize(const stack_ty *stack_ptr);

/************************************************************************ 
*   return 1 if stack is empty and 0 if not 
*   note: undefined behaviour if stack is NULL
*************************************************************************/
int StackIsEmpty(const stack_ty *stack_ptr);

/************************************************************************ 
*   return maximum size of the stack 
*   note: undefined behaviour if stack is NULL
*************************************************************************/
size_t StackGetCapacity(const stack_ty *stack_ptr);


#endif /* __STACK_H__ */





