#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "tests.h"

#define TEST_HASH_TABLE_CAPACITY  (10)
#define DICTIONARY_SIZE 104334

void *get_key(const void *data);
size_t hash_func(const void *key);
int cmp_func(const void *curr_key, void *key_to_match);
int action_func(void *hash_data, void *params);
void TEST_HTCreate(void);
void TEST_HT(void);
void test_find(hash_table_ty *hash_table, const void *key, void *expected_value);
void dictionary(void);
int HTIsInDictionary(hash_table_ty *dictionary, char *word);
static void LoadDictionary(char *argv[]);
static size_t StrHashFunc(const void *key);
static int StrCmpFunc(const void *curr_key, void *key_to_match);
int PrintDataPtr(void *list_data, void *param);
int Free(void *list_data, void *param);

action_func_ty action_ptr = PrintDataPtr;


int main(int argc, char **argv)
{
    TEST_HTCreate();
    TEST_HT();

    if (argc == 2)
    {
        LoadDictionary(argv);    
    }
    
    PASS;
    
    return 0;
}

int Free(void *list_data, void *param)
{
    (void)param;
    free(list_data);
    
    list_data = NULL; 

    return 0;
}

void TEST_HTCreate(void)
{
    hash_table_ty *hash_table = HTCreate(TEST_HASH_TABLE_CAPACITY, hash_func, cmp_func, get_key);

    if (hash_table == NULL)
    {
        puts("creat function failed");
    }
    HTDestroy(hash_table);
}

void TEST_HT(void)
{
    hash_table_ty *ht = NULL;
    int value1 = 0;
    int value2 = 0;
    int value3 = 0;

    ht = HTCreate(10, hash_func, cmp_func, get_key);

    TEST("HTIsEmpty", HTIsEmpty(ht), 1);

    value1 = 1;
    value2 = 2;
    value3 = 3;

    TEST("insert_result1", HTInsert(ht, &value1), 0);
    TEST("insert_result2", HTInsert(ht, &value2), 0);
    TEST("insert_result3", HTInsert(ht, &value3), 0);

    TEST("HTIsEmpty", HTIsEmpty(ht), 0);

    test_find(ht, get_key(&value1), &value1);
    test_find(ht, get_key(&value2), &value2);
    test_find(ht, get_key(&value3), &value3);

    TEST("HTSize", HTSize(ht), 3);

    HTRemove(ht, get_key(&value1));
    HTRemove(ht, get_key(&value2));
    HTRemove(ht, get_key(&value3));

    TEST("HTSize", HTSize(ht), 0);

    printf("after remove, it is good if now tests are failed:\n");
    test_find(ht, get_key(&value1), &value1);
    test_find(ht, get_key(&value2), &value2);
    test_find(ht, get_key(&value3), &value3);

    HTDestroy(ht);

}

void test_find(hash_table_ty *hash_table, const void *key, void *expected_value)
{
    void *value = HTFind(hash_table, key);
    if (value == expected_value)
    {
        printf("Test passed: found value %p matches expected value %p.\n", value, expected_value);
    }
    else
    {
        printf("Test failed: found value %p does not match expected value %p.\n", value, expected_value);
    

    }
}


/*  function that gets a data and returns his key                             */
void *get_key(const void *data)
{
    return (void*)data;
}

/*  function that gets a key and returns his idx in the hash table            */
size_t hash_func(const void *key)
{
    return *(int*)key % TEST_HASH_TABLE_CAPACITY;
}

/*  write a function with the following signature to perform the comparison of
    "curr_key" and "key_to_match"
    returns: 1 if matched, 0 otherwise                                        */
int cmp_func(const void *curr_key, void *key_to_match)
{
    return (*(int*)curr_key == *(int*)key_to_match);
}

/*  write a function with the following signature to perform whichever action
    you need on "hash_data"
    "params" is extra data
    return 0 if succeeded, otherwise - not 0                                  */
int action_func(void *hash_data, void *params)
{
    params = NULL;
    *(int*)hash_data = *(int*)hash_data + 1;

    return 0;
}



static void LoadDictionary(char *argv[])
{
    FILE *fp = fopen("/usr/share/dict/words", "r");
    char line[256];
    hash_table_ty *hash = NULL;
    char *word = NULL;

    if (NULL == fp)
    {
        printf("Failed to open file %s\n", "/usr/share/dict/words");
        
        return;
    }

    hash = HTCreate(DICTIONARY_SIZE, StrHashFunc, StrCmpFunc, get_key);

    while (fgets(line, sizeof(line), fp))
    {
        /* remove the newline character from the line */
        line[strcspn(line, "\n")] = '\0';
    
        /* dynamically allocate memory for the line */
        word = malloc(strlen(line) + 1);
        strcpy(word, line);
        
        /* insert the line into the hash */
        HTInsert(hash, word);

    }

    fclose(fp);

    printf("Spell checker: %s\n" , (char *)HTFind(hash, argv[1]));

    HTForEach(hash, &Free, NULL);

    HTDestroy(hash);
}


static size_t StrHashFunc(const void *key)
{
    const char *str = (const char *)key;
    size_t hash = 0;
    int c;

    while ((c = *str++))
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash % DICTIONARY_SIZE;
}

static int StrCmpFunc(const void *curr_key, void *key_to_match)
{
    int res = 0;

    res = strcmp(curr_key, key_to_match);

    if (res == 0)
    {
        return 1;
    }

    return 0;
}

int PrintDataPtr(void *list_data, void *param)
{
    (void)param;
    printf("list_data is: %s \n" , (char *)list_data);

    return 0;
}




