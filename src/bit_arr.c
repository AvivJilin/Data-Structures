/******************************************************************/
/*Date: 07.12.22*/
/*Author: Aviv Jilin*/
/*reviewer:  Eliran*/
/*version: 1.0*/
/*****************************************************************/

#include <stddef.h> /* size_t */
#include "../include/bit_arr.h" /* API */

#define SIZE_T_BITS 64
/*1010101010101010101010101010101010101010101010101010101010101010*/
#define OFF_ON_BIT 0xAAAAAAAAAAAAAAAA 
/*1100110011001100110011001100110011001100110011001100110011001100*/
#define OFF_ON_TUPEL 0xCCCCCCCCCCCCCCCC
/*1111000011110000111100001111000011110000111100001111000011110000*/
#define OFF_ON_NIBBLE 0xF0F0F0F0F0F0F0F0
/*1111111100000000111111110000000011111111000000001111111100000000*/
#define OFF_ON_BYTE 0xFF00FF00FF00FF00
/*1111111111111111000000000000000011111111111111110000000000000000*/
#define OFF_ON_2BYTE 0xFFFF0000FFFF0000
/*1111111111111111111111111111111100000000000000000000000000000000*/
#define OFF_ON_4BYTE  0xFFFFFFFF00000000


bit_arr_ty BitArrSetAll(bit_arr_ty bit_array)
{
    return ~(bit_array & 0);
}

bit_arr_ty BitArrResetAll(bit_arr_ty bit_array)
{
    return (bit_array & 0);
}

bit_arr_ty BitArrSetOn(bit_arr_ty bit_array, size_t index)
{
    bit_arr_ty mask = 1;
    mask = mask << index;
    return (bit_array | mask);
}

bit_arr_ty BitArrSetOff(bit_arr_ty bit_array, size_t index)
{
    bit_arr_ty mask = 1;
    mask = mask << index;
    mask = ~mask;
    return (bit_array & mask);
}

bit_arr_ty BitArrSetBit(bit_arr_ty bit_array, size_t index, 
                        unsigned int bool_val)
{
    return ((size_t)bool_val<<index) | BitArrSetOff(bit_array, index);
}

unsigned int BitArrGetVal(bit_arr_ty bit_array, size_t index)
{
    bit_array = bit_array >> index;
    return (bit_array & 1);
}

bit_arr_ty BitArrFlip(bit_arr_ty bit_array, size_t index)
{
    bit_arr_ty mask = 1;
    mask = mask << index;
    return (bit_array ^ mask);
}

bit_arr_ty BitArrMirror(bit_arr_ty bit_array)
{
    bit_array = (((bit_array & OFF_ON_4BYTE) >> 32) | ((bit_array & (~OFF_ON_4BYTE)) << 32));
    bit_array = (((bit_array & OFF_ON_2BYTE) >> 16) | ((bit_array & (~OFF_ON_2BYTE)) << 16));
    bit_array = (((bit_array & OFF_ON_BYTE) >> 8) | ((bit_array & (~OFF_ON_BYTE)) << 8));
    bit_array = (((bit_array & OFF_ON_NIBBLE) >> 4) | ((bit_array & (~OFF_ON_NIBBLE)) << 4));               
    bit_array = (((bit_array & OFF_ON_TUPEL) >> 2) | ((bit_array & (~OFF_ON_TUPEL)) << 2)); 
    bit_array = (((bit_array & OFF_ON_BIT) >> 1) | ((bit_array & (~OFF_ON_BIT)) << 1));
    return bit_array;
}

bit_arr_ty BitArrRotateRight(bit_arr_ty bit_array, size_t shifts)
{
    shifts = shifts % SIZE_T_BITS;
    return ((bit_array >> shifts) | (bit_array << (SIZE_T_BITS - shifts)));
}

bit_arr_ty BitArrRotateLeft(bit_arr_ty bit_array, size_t shifts)
{
    shifts = shifts % SIZE_T_BITS;
    return (bit_array << (shifts) | (bit_array >> (SIZE_T_BITS - shifts)));
}

size_t BitArrCountOn(bit_arr_ty bit_array)
{
    size_t cnt = 0;

    cnt = bit_array;
    cnt = (cnt & ~OFF_ON_BIT) + ((cnt >> 1) & ~OFF_ON_BIT);
    cnt = (cnt & ~OFF_ON_TUPEL) + ((cnt >> 2) & ~OFF_ON_TUPEL);
    cnt = (cnt & ~OFF_ON_NIBBLE) + ((cnt >> 4) & ~OFF_ON_NIBBLE);
    cnt = (cnt & ~OFF_ON_BYTE) + ((cnt >> 8) & ~OFF_ON_BYTE);
    cnt = (cnt & ~OFF_ON_2BYTE) + ((cnt >> 16) & ~OFF_ON_2BYTE);
    cnt = (cnt & ~OFF_ON_4BYTE) + ((cnt >> 32) & ~OFF_ON_4BYTE);
    return cnt;
}

size_t BitArrCountOff(bit_arr_ty bit_array)
{
    return ((size_t)(SIZE_T_BITS - BitArrCountOn(bit_array)));
}

char *BitArrToString(bit_arr_ty bit_array, char *dest_buffer)
{
    int i = 0;
    dest_buffer[SIZE_T_BITS] = '\0';
    for (i = SIZE_T_BITS - 1; i >= 0; --i)
    {
        dest_buffer[i] = (bit_array & 1) ? ('1') : ('0');
        bit_array = bit_array >> 1;
    }
    return dest_buffer;
}

