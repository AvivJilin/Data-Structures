#include <stdio.h>      /* printf */

#include "queue.h"
#include "slist.h"

#include "tests.h"

static void QueueEnqueueTest(void);
static void QueueAppendTest(void);


int main(void)
{
    QueueEnqueueTest();
    QueueAppendTest();
    PASS;
    return 0;
}

static void QueueEnqueueTest(void)
{
    queue_ty *new_queue = NULL;
    size_t i = 0, size = 0;
    int data_arr[] = {0, 1, 2, 3, 4};
    size = sizeof(data_arr) / sizeof(data_arr[0]);

    new_queue = QueueCreate();
    TEST("IsEmpty", QueueIsEmpty(new_queue), 1);

    while (i < size)
    {
        QueueEnqueue(new_queue, &data_arr[i]);
        ++i;
    }


    TEST("QueueSize and Enqueue", QueueSize(new_queue), size);
    TEST("QueuePeek", *(int*)QueuePeek(new_queue), data_arr[0]);
    TEST("IsEmpty", QueueIsEmpty(new_queue), 0);

    QueueDequeue(new_queue);
    QueueDequeue(new_queue);
    QueueDequeue(new_queue);
    TEST("Dequeue", *(int*)QueuePeek(new_queue), data_arr[3]);

    QueueDestroy(new_queue);

}

static void QueueAppendTest(void)
{
    queue_ty *first_queue = QueueCreate();
    queue_ty *second_queue = QueueCreate();
    int data[4] = {1,2,3,4};

    QueueEnqueue(first_queue, &data[0]);
    QueueEnqueue(first_queue, &data[1]);
    QueueEnqueue(first_queue, &data[2]);
    QueueEnqueue(first_queue, &data[3]);
    
    QueueEnqueue(second_queue, &data[0]);
    QueueEnqueue(second_queue, &data[1]);
    QueueEnqueue(second_queue, &data[2]);
    QueueEnqueue(second_queue, &data[3]);
    
    QueueAppend(second_queue,first_queue);

    TEST("Test QueueSize",8 , QueueSize(second_queue));

    QueueDestroy(second_queue);
}

