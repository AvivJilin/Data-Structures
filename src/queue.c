/******************************************************************/
/*Date: 19.12.22*/
/*Author: Aviv Jilin*/
/*reviewer: eliran */
/*version: 1.1*/
/*****************************************************************/


#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */

#include "slist.h"
#include "slist.c"
#include "queue.h"

struct queue
{
    slist_ty *slist;
};

queue_ty *QueueCreate(void)
{
    queue_ty *new_queue = NULL;

    new_queue = (queue_ty *)malloc(sizeof(queue_ty));

    if (NULL == new_queue)
    {
        return NULL;
    } 
    
    new_queue->slist = SlistCreate();
    if (NULL == new_queue->slist)
    {
        free(new_queue);
        return NULL;
    }
    
    return new_queue;

}


void QueueDestroy(queue_ty *queue)
{
    assert (NULL != queue);

    SlistDestroy(queue->slist);

    free(queue);
    queue = NULL;
}


void *QueuePeek(const queue_ty *queue)
{
    assert (NULL != queue);

    return (SlistIterGetData(SlistIterBegin(queue->slist)));
}

int QueueEnqueue(queue_ty *queue, const void *data)
{
    assert(NULL != queue);
    assert(NULL != data);
     
    if(SlistInsert(SlistIterEnd(queue->slist), data) 
        == SlistIterEnd(queue->slist))
    {
        return 1;
    }

    return 0;
}

void QueueDequeue(queue_ty *queue)
{
    assert(NULL != queue);

    SlistRemove(SlistIterBegin(queue->slist));
}

int QueueIsEmpty(queue_ty *queue)
{
    assert(NULL != queue);
    
    return SlistIterIsEqual(SlistIterBegin(queue->slist),
     SlistIterEnd(queue->slist));
}

size_t QueueSize(queue_ty *queue)
{
    assert(NULL != queue);

    return SlistCount(queue->slist);
}

void QueueAppend(queue_ty *dest_queue, queue_ty *src_queue)
{
    assert(NULL != dest_queue);
    assert(NULL != src_queue);

    SlistAppend(dest_queue->slist, src_queue->slist);

    free(src_queue);
}
