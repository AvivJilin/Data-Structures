#include <math.h> /* pow */


#include "../include/bit_arr.h" /* API */
#include "tests.h"


static void TestBitArrSetAll(void);

static void TestBitArrResetAll(void);

static void TestBitArrSetOn(void);

static void TestBitArrSetOff(void);

static void TestBitArrSetBit(void);

static void TestBitArrGetVal(void);

static void TestBitArrFlip(void);

static void TestBitArrMirror(void);

static void TestBitArrRotateRight(void);

static void TestBitArrRotateLeft(void);

static void TestBitArrCountOn(void);

static void TestBitArrCountOff(void);

static void TestBitArrToString(void);

/******************************************************************************/
int main(void)
{
    TestBitArrSetAll();
    TestBitArrResetAll();
    TestBitArrSetOn();
    TestBitArrSetOff();
    TestBitArrSetBit();
    TestBitArrGetVal();
    TestBitArrFlip();
    TestBitArrMirror();
    TestBitArrRotateRight();
    TestBitArrRotateLeft();
    TestBitArrCountOn();
    TestBitArrCountOff();
    TestBitArrToString();
    PASS;
    return 0;
}
void TestBitArrSetAll(void)
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {0, 1, 15, 4};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("TestBitArrResetAll", (size_t) -1,BitArrSetAll(nums[i]));
        ++i;
    }
    
}

void TestBitArrResetAll(void)
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {0, 1, 15, 4};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("TestBitArrResetAll", (size_t)0,BitArrResetAll(nums[i]));
        ++i;
    }
}

void TestBitArrSetOn(void)
{
    size_t num = 2147614720;
    TEST("TestBitArrSetOn", 2147614736, BitArrSetOn(num, 4));            
}

void TestBitArrSetOff(void)
{
    size_t num = 2147614736;
    TEST("TestBitArrSetOff", 2147614720, BitArrSetOff(num, 4));    
}

void TestBitArrSetBit(void)
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {555, 79879, 123134, 0};
    size_t results[] = {811, 80135, 123390, 256};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("TestBitArrSetBit", results[i], BitArrSetBit(nums[i], 8, 1));
        ++i;
    }

}
void TestBitArrGetVal(void)
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {555, 79879, 123134, 0, 1231341};
    size_t results[] = {0, 0, 1, 0, 1};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("TestBitArrGetVal", results[i], BitArrGetVal(nums[i], 7));
        ++i;
    }
    
}

void TestBitArrFlip(void)
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {555, 79879, 123134, 0, 1231341};
    size_t results[] = {811, 80135, 123390, 256, 1231085};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("TestBitArrFlip", results[i], BitArrFlip(nums[i], 8));
        ++i;
    }        
}

void TestBitArrMirror(void)
{
    
    TEST("BitArrMirror", BitArrMirror(pow(2,63)+pow(2,62)), 3);

    TEST("BitArrMirror", BitArrMirror(pow(2,63)),1);
}
  

void TestBitArrRotateRight(void)
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {1, 79879, 123134, 0, 1231341};
    size_t results[] = {16, 1278064, 1970144, 0, 19701456};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("TestBitArrRotateRight", results[i], BitArrRotateRight(nums[i], 60));
        ++i;
    }        
}

void TestBitArrRotateLeft(void)
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {1, 8, 16, 64, 256};
    size_t results[] = {2, 16, 32, 128, 512};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("TestBitArrRotateLeft", results[i], BitArrRotateLeft(nums[i], 1));
        ++i;
    }       
}

void TestBitArrCountOn(void)
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {56, 23, 456, 4879, 4564564};
    size_t results[] = {3, 4, 4, 7, 10};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("TestBitArrCountOn", results[i], BitArrCountOn(nums[i]));
        ++i;
    }     
}

void TestBitArrCountOff(void)
{
    size_t i = 0;
    size_t num_of_tests = 0;
    size_t nums[] = {56, 23, 456, 4879, 4564564};
    size_t results[] = {61, 60, 60, 57, 54};
    num_of_tests = sizeof(nums) / sizeof(nums[0]);
    
    while (i < num_of_tests)
    {
        TEST("TestBitArrCountOff", results[i], BitArrCountOff(nums[i]));
        ++i;
    }     
}
void TestBitArrToString(void)
{
    char buffer[65] = {0};
    char *one ="0000000000000000000000000000000000000000000000000000000000000001";  
    char *zero ="0000000000000000000000000000000000000000000000000000000000000000";  
    TEST_EACH_BYTE("BitArrToString", BitArrToString((size_t)1, buffer), one, 65); 
    TEST_EACH_BYTE("BitArrToString", BitArrToString((size_t)0, buffer), zero, 65);

}
