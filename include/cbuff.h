/******************
 * Author:  HRD28
 * Version: 1.5
******************/
#ifndef __C_BUFF_H__
#define __C_BUFF_H__

#include <stddef.h>        /*  size_t  */
#include <sys/types.h>     /*  ssize_t  */

typedef struct c_buff c_buff_ty;

/*******************************************************************************
 * Creates an empty circular buffer 
 * Arguments : cbuff capacity in bytes 
 * Returns pointer to the circular buffer on success, NULL otherwise
 * Time Complexity: determined by the used system call complexity
*******************************************************************************/
c_buff_ty *CBuffCreate(size_t capacity);

/*******************************************************************************
 * Frees all resources used by "buffer"
 * note: undefined behaviour if "buffer" is NULL
 * Time Complexity: determined by the used system call complexity
*******************************************************************************/
void CBuffDestroy(c_buff_ty *buffer);

/*******************************************************************************
 * writes up to "num_bytes" from "src" to "buffer".
 * Arguments: buffer    - buffer to write to
              src       - input buffer             
              num_bytes - number of bytes to write             
 * note: undefined behaviour if "buffer" or "src" are NULL, 
        
 * returns the amount of bytes that was successfully written, -1 otherwise
 * Time Complexity: O(n)
*******************************************************************************/
ssize_t CBuffWrite(c_buff_ty *buffer, const void *src, size_t num_bytes);

/*******************************************************************************
 * reads up to "num_bytes" from "buffer" to "dest".
 * Arguments: buffer    - buffer to read from
 	      dest      - buffer to write to             
              num_bytes - number of bytes to read 
 * note: undefined behaviour if "buffer" or "dest" are NULL         
 * returns the amount of bytes that was successfully read, -1 otherwise
 * Time Complexity: O(n)
*******************************************************************************/
ssize_t CBuffRead(c_buff_ty *buffer, void *dest, size_t num_bytes);

/*******************************************************************************
 * Returns 1 if the "buffer" is empty, 0 otherwise
 * note: undefined behaviour if "buffer" is NULL
 * Time Complexity: O(1)
*******************************************************************************/
int CBuffIsEmpty(const c_buff_ty *buffer);

/*******************************************************************************
 * Returns the amount of occupied bytes in "buffer" 
 * note: undefined behaviour if "buffer" is NULL
 * Time Complexity: O(1)
*******************************************************************************/
size_t CBuffSize(const c_buff_ty *buffer);

/*******************************************************************************
 * Returns the amount of UNoccupied bytes in "buffer" 
 * note: undefined behaviour if "buffer" is NULL
 * Time Complexity: O(1)
*******************************************************************************/
size_t CBuffFreeSpace(const c_buff_ty *buffer);


#endif /*   __C_BUFF_H__     */
