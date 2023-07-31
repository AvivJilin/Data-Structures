#include <stdio.h>

#include "cbuff.h"
#include "tests.h"

#define BUFFER_SIZE 15

void TestCBuffer(void);

int main()
{
    TestCBuffer();

    PASS;

    return 0;
}

void TestCBuffer()
{
    char *test_string[] = {"Hello","MeshiJilin"};
    char read_from_buffer[BUFFER_SIZE+1] = {'\0'};
    char read_from_buffer2[BUFFER_SIZE+1] = {'\0'};
    c_buff_ty *test_buffer = CBuffCreate(BUFFER_SIZE);

    TEST("CBuffIsEmpty", CBuffIsEmpty(test_buffer), 1);

    TEST("CBuffFreeSpace", CBuffFreeSpace(test_buffer), 15);

    TEST("CBuffWrite", CBuffWrite(test_buffer, test_string[0],
     strlen(test_string[0])), (ssize_t)strlen(test_string[0]));

    TEST("CBuffFreeSpace", CBuffFreeSpace(test_buffer), 10);

    TEST("CBuffRead", CBuffRead(test_buffer, read_from_buffer2,
     strlen(test_string[0])), 5);

    TEST("CBuffWrite", CBuffWrite(test_buffer, test_string[0],
     strlen(test_string[0])), (ssize_t)strlen(test_string[0]));

    TEST("CBuffWrite2", CBuffWrite(test_buffer, test_string[1],
     strlen(test_string[1])), (ssize_t)strlen(test_string[1]));

    TEST("CBuffRead", CBuffRead(test_buffer, read_from_buffer,
     strlen(test_string[0]) + strlen(test_string[1])), 15);

    printf("%s\n", read_from_buffer);

    TEST("CBuffIsEmpty", CBuffIsEmpty(test_buffer), 1);
    TEST("CBuffFreeSpace", CBuffFreeSpace(test_buffer), 15);


    CBuffDestroy(test_buffer);
}

