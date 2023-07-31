/******************************************************************/
/*Date: 20.12.22*/
/*Author: Aviv Jilin*/
/*reviewer: Sarit */
/*version: 1.0*/
/*****************************************************************/

#include <assert.h> /* assert */ 
#include <stddef.h> /* NULL */ 

#include "slist_excercise.h"


node_t *Flip(node_t *head)
{
    node_t *previous = NULL;
    node_t *current = head;
    node_t *following = head;
   
    assert (NULL != head);
   
    while(NULL != current)
    {
        following = following->next;
        current->next = previous;
        previous = current;
        current = following;
    }
    return previous;
}

int HasLoop(const node_t *head)
{
    node_t *slow_p = (node_t *)head; 
    node_t *fast_p = (node_t *)head;

    assert(NULL != head);

    while(NULL != slow_p && NULL != fast_p && NULL != fast_p->next) 
    {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p)
        {
            return 1;  /* 1 means there is a loop */
        }
    }
    return 0; /* 0 means there isnt a loop */
}

node_t *FindIntersection(node_t *head1, node_t *head2)
{
    node_t *first_ptr = head1;
    node_t *second_ptr = head2;

    assert(NULL != head1);
    assert(NULL != head2); 

    while(first_ptr != second_ptr)
    {
        first_ptr = first_ptr->next;
        second_ptr = second_ptr->next;

        if(first_ptr == second_ptr)
        {
            return first_ptr;
        }

        if(NULL == first_ptr)
        {
            first_ptr = head2;
        }

        if (NULL == second_ptr)
        {
            second_ptr = head1;           
        }

    }
    return first_ptr; /* first_ptr will return NULL, because both first_ptr
    and second_ptr is NULL at the end */
}












