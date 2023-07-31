#include <stdio.h>    /* printf */
#include <string.h>   /* memcmp */

/******************************************************************************/
/***                        Color Defines   		                        ***/
/******************************************************************************/
#define DEFAULT     "\033[0m"
#define BLACK       "\033[30m"             /* Black */
#define RED         "\033[31m"             /* Red */
#define GREEN       "\033[32m"             /* Green */
#define YELLOW      "\033[33m"             /* Yellow */
#define BLUE        "\033[34m"             /* Blue */
#define MAGENTA     "\033[35m"             /* Magenta */
#define CYAN        "\033[36m"             /* Cyan */
#define WHITE       "\033[37m"             /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

/******************************************************************************/
/***                      Public macros declarations                        ***/
/******************************************************************************/
static int test_counter_g = 0;
static int success_counter_g = 0;

#define TEST(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEFAULT, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)

#define TEST_EACH_BYTE(name, real, expected, num) \
    do { \
        ++test_counter_g; \
        (0 == memcmp(real, expected, num)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d\n" DEFAULT, name, __LINE__); \
    } while (0)

#define TEST_NE(name, real, Not_expected) \
    do { \
        ++test_counter_g; \
        ((real) != (Not_expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Not Expected: %ld\n" DEFAULT, name, __LINE__, (long) (real), (long) (Not_expected)); \
    } while (0)

#define TEST_STR(name, real, str1, str2, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, %s  %s \nReal: %ld, Expected: %ld\n" DEFAULT, name, __LINE__, str1, str2, (long) (real), (long) (expected)); \
    } while (0)


#define TEST_SEQ(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) <= (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEFAULT, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)
    
#define TEST_LEQ(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) >= (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEFAULT, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)


#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEFAULT) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEFAULT, \
           test_counter_g - success_counter_g, test_counter_g)


#define FAILED \
        do \
        { \
        PASS; \
        printf(RED "Some Tests were not completed, due to failure in the middle of them.\n" DEFAULT); \
        } while(0)
      
