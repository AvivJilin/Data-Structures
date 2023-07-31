#include "p_queue.h"
#include "tests.h"

static void TestEnqueue(void);

int MyCmp(void *data1, void *data2)
{
    return *(int *)data1 - *(int *)data2;
}

int Find3(const void *list_data, void *param)
{
    int *list_data1 = (int *)list_data;
    (void)param;
    return (3 == *list_data1);
}

cmp_func_ty cmp_func = MyCmp;

is_match_func_ty my_func = Find3;

int main(void)
{
	TestEnqueue();
	PASS;
	return 0;
}

static void TestEnqueue(void)
{

    int data_arr[] = { 1,2,3,4,5 };
    size_t num_of_tests = sizeof(data_arr) / sizeof(data_arr[0]);
    size_t i = 0;
    void *data = NULL;

    p_queue_ty *new_queue = PQueueCreate(cmp_func);

    TEST("PQueueSize", PQueueSize(new_queue), 0);
    TEST("PQueueIsEmpty", PQueueIsEmpty(new_queue), 1);

    PQueueEnqueue(new_queue, &data_arr[2]);
    PQueueEnqueue(new_queue, &data_arr[1]);
    PQueueEnqueue(new_queue, &data_arr[0]);
    PQueueEnqueue(new_queue, &data_arr[4]);
    PQueueEnqueue(new_queue, &data_arr[3]);

    TEST("PQueueSize", PQueueSize(new_queue), num_of_tests);
    TEST("PQueueIsEmpty", PQueueIsEmpty(new_queue), 0);

    for (i = num_of_tests - 1; i > 0; --i)
    {
        TEST("PQueuePeek/PQueueDequeue", *(int *)PQueuePeek(new_queue), data_arr[i]);
        PQueueDequeue(new_queue);
    }
    PQueueDequeue(new_queue);
    TEST("PQueueIsEmpty", PQueueIsEmpty(new_queue), 1);


    PQueueEnqueue(new_queue, &data_arr[2]);
    PQueueEnqueue(new_queue, &data_arr[1]);
    PQueueEnqueue(new_queue, &data_arr[0]);
    PQueueEnqueue(new_queue, &data_arr[4]);
    PQueueEnqueue(new_queue, &data_arr[3]);

    data = PQueueErase(new_queue, my_func, data);
    TEST("PQueueErase", *(int *)data, data_arr[2]);

    TEST("PQueueSize/PQueueErase", PQueueSize(new_queue), 4);

    PQueueClear(new_queue);

    TEST("PQueueSize/PQueueClear", PQueueSize(new_queue), 0);
    TEST("PQueueIsEmpty", PQueueIsEmpty(new_queue), 1);


    PQueueDestroy(new_queue);
}





