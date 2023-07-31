/*******************************************************************************
 * Author:      HRD28
 * Version:     1.1
*******************************************************************************/

#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h>     /*  size_t  */

/*  supports a 64-bit array                                                   */
typedef size_t bit_arr_ty;

/*******************************************************************************
 * returns bit_array_ty with all bits set to 1
*******************************************************************************/
bit_arr_ty BitArrSetAll(bit_arr_ty bit_array);

/*******************************************************************************
 * returns bit_array_ty with all bits set to 0
*******************************************************************************/
bit_arr_ty BitArrResetAll(bit_arr_ty bit_array);

/*******************************************************************************
 * returns bit_array_ty with the bit at "index" set to 1
 * (rightmost bit is at index 0)
*******************************************************************************/
bit_arr_ty BitArrSetOn(bit_arr_ty bit_array, size_t index);

/*******************************************************************************
 * returns bit_array_ty with the bit at "index" set to 0
 * (rightmost bit is at index 0)
*******************************************************************************/
bit_arr_ty BitArrSetOff(bit_arr_ty bit_array, size_t index);

/*******************************************************************************
 * returns bit_array_ty with the bit at "index" set to "bool_val"
 * (rightmost bit is at index 0)
*******************************************************************************/
bit_arr_ty BitArrSetBit(bit_arr_ty bit_array, size_t index, 
                        unsigned int bool_val);

/*******************************************************************************
 * get the value of the bit at "index" (rightmost bit is at index 0)
*******************************************************************************/
unsigned int BitArrGetVal(bit_arr_ty bit_array, size_t index);

/*******************************************************************************
 * returns bit_array_ty with the bit at "index" flipped
 * (rightmost bit is at index 0)
*******************************************************************************/
bit_arr_ty BitArrFlip(bit_arr_ty bit_array, size_t index);

/*******************************************************************************
 * returns the mirror of "bit_array"
 * e.g. 11000100 -> 00100011
*******************************************************************************/
bit_arr_ty BitArrMirror(bit_arr_ty bit_array);

/*******************************************************************************
 * returns "bit_array" rotated "shifts" bits to the right
*******************************************************************************/
bit_arr_ty BitArrRotateRight(bit_arr_ty bit_array, size_t shifts);

/*******************************************************************************
 * returns "bit_array" rotated "shifts" bits to the left 
*******************************************************************************/
bit_arr_ty BitArrRotateLeft(bit_arr_ty bit_array, size_t shifts);

/*******************************************************************************
 * count set bits in "bit_array"
*******************************************************************************/
size_t BitArrCountOn(bit_arr_ty bit_array);

/*******************************************************************************
 * count unset bits in "bit_array"
*******************************************************************************/
size_t BitArrCountOff(bit_arr_ty bit_array);

/*******************************************************************************
 * creates a string of "bit_array". returns a pointer to "dest_buffer".
   Note:    undefined behaviour if "dest_buffer" is NULL
            or not large enough to store 64 chars + terminating null
            (total of 65)
*******************************************************************************/
char *BitArrToString(bit_arr_ty bit_array, char *dest_buffer);

#endif  /*  __BIT_ARRAY_H__  */