/******************************************************************/
/*Date: 20.12.22*/
/*Author: Aviv Jilin*/
/*reviewer: Gita */
/*version: 1.0*/
/*****************************************************************/

#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */


#include "cbuff.h"

struct c_buff
{
	size_t read_idx;
    size_t size;
    size_t capacity;
    char arr[1];
};


c_buff_ty *CBuffCreate(size_t capacity)
{
    c_buff_ty *cbuf = NULL;
    size_t res = offsetof(c_buff_ty, arr) + capacity;

    if (res < sizeof(c_buff_ty))
    {
        res = sizeof(c_buff_ty);
    }

    cbuf = (c_buff_ty *)malloc(res);

    if (NULL == cbuf)
    {
        return NULL;
    }
    
    cbuf -> read_idx = 0;
    cbuf -> size = 0;
    cbuf->capacity = capacity;

    return cbuf;
}

void CBuffDestroy(c_buff_ty *buffer)
{
	assert(NULL != buffer);

    free(buffer);
    buffer = NULL;
}

ssize_t CBuffWrite(c_buff_ty *buffer, const void *src, size_t num_bytes) 
{
    ssize_t res = num_bytes;
    size_t free_space = CBuffFreeSpace(buffer);
    size_t first_end = 0;
    size_t second_end = 0;

    assert(NULL != buffer);
    assert(NULL != src);

    if (0 == free_space)
    {
        return -1;
    }

    if (free_space < (size_t)res)
    {
        res = free_space;
    }

    first_end = buffer->size + res;
    second_end = first_end;

    if (second_end > buffer->capacity)
    {
        second_end = buffer->capacity;
    }

    memcpy(buffer->arr + buffer->size, src, second_end - buffer->size);

    if (first_end > buffer->capacity)
    {
        first_end = first_end - buffer->capacity;
        memcpy(buffer->arr,(char *) src + second_end - buffer->size, first_end);
    }

	buffer->size = buffer->size + res;

    if(buffer->size > buffer->capacity)
    {
        buffer->size = buffer->size - buffer->capacity;
    }

    return res;
}

ssize_t CBuffRead(c_buff_ty *buffer, void *dest, size_t num_bytes)
{
    ssize_t res = num_bytes;
    size_t first_end = 0;
    size_t second_end = 0;

    assert(NULL != buffer);
    assert(NULL != dest);

    if (num_bytes > buffer->size)
    {
        res = buffer->size;
    }

    if (CBuffIsEmpty(buffer))
    {
        return -1;
    }

    first_end = buffer->read_idx + res;
    second_end = first_end;

    if (second_end > buffer->capacity)
    {
        second_end = buffer->capacity;
    }

    memcpy(dest, buffer->arr + buffer->read_idx, second_end - buffer->read_idx);

    if (first_end > buffer->capacity)
    {
        first_end = first_end - buffer->capacity;
        memcpy((char *)dest + second_end - buffer->read_idx, buffer->arr, first_end);
    }

    buffer->size = buffer->size - res;
    buffer->read_idx = buffer->read_idx + res;

    if(buffer->read_idx > buffer->capacity)
    {
        buffer->read_idx = buffer->read_idx - buffer->capacity;
    }

    return res;
}


int CBuffIsEmpty(const c_buff_ty *buffer)
{
	assert(NULL != buffer);

    if (0 == buffer->size)
    {
        return 1;
    }

    return 0;
}

size_t CBuffSize(const c_buff_ty *buffer)
{
	assert(NULL != buffer);

    return buffer->size;
}

size_t CBuffFreeSpace(const c_buff_ty *buffer)
{
	assert(NULL != buffer);
    
    return buffer->capacity - buffer->size;
}



