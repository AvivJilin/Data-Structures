#include <stdio.h> /* printf */


#include "stack.h" /* API */
#include "tests.h"

#define CAPACITY 5


static void TestStackOnInt(void);

/******************************************************************************/
int main()
{
    TestStackOnInt();
    PASS;
    return 0;
}

void TestStackOnInt(void)
{
    stack_ty *new_stack = NULL;
    int elments[] = {0, 1566, 15, 4, -5};
    int *res = NULL;
    int i = 0;
    int num_of_tests = sizeof(elments) / sizeof(elments[0]);
    /*creat new stack */
    new_stack = StackCreate(CAPACITY, sizeof(int));
    
    TEST("Test StackCreate/StackIsempty", StackIsEmpty(new_stack), 0);
    TEST("Test StackGetCapacity", StackGetCapacity(new_stack), (size_t)num_of_tests);
    while (i < num_of_tests)
    {
        StackPush(new_stack, &elments[i]);
        res = StackPeek(new_stack);
        TEST("Test StackPush/StackPeek", *res, elments[i]);
        ++i;
    }
    TEST("Test StackGetSize", StackGetSize(new_stack), (size_t)num_of_tests);
    --i;
    while (i > 0)
    {
        res = StackPeek(new_stack);
        TEST("Test StackPop", *res, elments[i]);
        StackPop(new_stack);
        --i;
    }
    StackDestroy(new_stack);
}




