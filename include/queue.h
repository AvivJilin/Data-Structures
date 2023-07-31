/******************
 * Author:  HRD28
 * Version: 1.3
******************/
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>     /*  size_t  */

typedef struct queue queue_ty;

/*******************************************************************************
 * Create an empty queue
 * Returns pointer to the queue on success, NULL otherwise
 * Time Complexity:     O(1)
*******************************************************************************/
queue_ty *QueueCreate(void);

/*******************************************************************************
 * Frees all dynamic allocated resources used by "queue"
 * note: undefined behaviour if "queue" is NULL
 * Time Complexity: O(n)
*******************************************************************************/
void QueueDestroy(queue_ty *queue);

/*******************************************************************************
 * Returns the data from the front of the "queue"
 * note: undefined behaviour if "queue" is empty or NULL
 * Time Complexity: O(1)
*******************************************************************************/
void *QueuePeek(const queue_ty *queue);

/*******************************************************************************
 * Adds data to the back of the "queue"
 *  returns 0 if succeeded, not 0 otherwise
 * note: undefined behaviour if "queue" is NULL
 * Time Complexity: O(1)
*******************************************************************************/
int QueueEnqueue(queue_ty *queue, const void *data);

/*******************************************************************************
 * Removes data from the front of the "queue"
 * note: undefined behaviour if "queue" is empty or NULL
 * Time Complexity: O(1)
*******************************************************************************/
void QueueDequeue(queue_ty *queue);

/*******************************************************************************
 * Returns 1 if the "queue" is empty, 0 otherwise
 * note: undefined behaviour if "queue" is NULL
 * Time Complexity: O(1)
*******************************************************************************/
int QueueIsEmpty(queue_ty *queue);

/*******************************************************************************
 * Returns the size of the "queue"
 * note: undefined behaviour if "queue" is NULL
 * Time Complexity: O(n)
*******************************************************************************/
size_t QueueSize(queue_ty *queue);

/*******************************************************************************
 * Appends the data from "src_queue" to the back of "dest_queue"
 * "src_queue" is emptied
 * note: undefined behaviour if "src_queue" or "dest_queue" are NULL
 * Time Complexity: O(1)
*******************************************************************************/
void QueueAppend(queue_ty *dest_queue, queue_ty *src_queue);

#endif /*   __QUEUE_H__     */
