#include <stdio.h> /* printf */



#include "dynamic_vector.h"
#include "tests.h"


static void TestVectorOnInt(void);

/******************************************************************************/
int main()
{
    TestVectorOnInt();
    PASS;
    return 0;
}

void TestVectorOnInt(void)
{
    d_vector_ty *d_vector = NULL;
    int elments[] = {0, 1566, 15, 4, -5};
    int *res = NULL;
    size_t i = 0;
    size_t num_of_tests = sizeof(elments) / sizeof(elments[0]);
    /*creat new vector */
    d_vector = VectorCreate(num_of_tests, sizeof(elments[0]));
    TEST("Test VectorGetCapacity", (size_t)num_of_tests, VectorGetCapacity(d_vector));
    while (i < num_of_tests)
    {
        VectorPushBack(d_vector, &elments[i]);
        res = VectorGetAccessToElement(d_vector, i);
        TEST("Test VectorGetAccessToElement", elments[i], *res);
        ++i;
    }
    TEST("Test VectorGetSize", (size_t)num_of_tests, VectorGetSize(d_vector));
    if (0 != VectorPushBack(d_vector, &elments[1]))
    {
        FAILED;
    }
    TEST("Test VectorGetCapacity", (size_t)(2 * num_of_tests), VectorGetCapacity(d_vector));
    TEST("Test VectorGetSize", (size_t)num_of_tests + 1, VectorGetSize(d_vector));
    res = VectorGetAccessToElement(d_vector, i);
    TEST("Test VectorPushWithRealloc", elments[1], *res);
    d_vector = VectorReserve(d_vector, 2 * num_of_tests);
    TEST("Test VectorGetCapacity", (size_t)2 * num_of_tests, VectorGetCapacity(d_vector));
    d_vector = VectorShrinkToFit(d_vector);
    TEST("Test VectorShrinkToFit", (size_t)num_of_tests + 1, VectorGetCapacity(d_vector));
    --i;
    while (i > 0)
    {
        res = VectorGetAccessToElement(d_vector, i);
        TEST("Test VectorPopBack", elments[i], *res);
        VectorPopBack(d_vector);
        --i;
    }
    VectorDestroy(d_vector);
}




