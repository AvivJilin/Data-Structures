#include <stdlib.h> /* malloc,free */
#include <assert.h> /* assert */

#include "slist_excercise.h"
#include "tests.h"


static node_t *CreateNode(void *data);
static void Destroy(node_t *head);
static node_t *PushNode(node_t *head, void *data);
static void PrintList(node_t *head);
static void SaritTestInterSection(void);
static void TestSlist(void);


int main()
{
    TestSlist();
    PASS;

    return 0;
}

/******************************************************************************/
node_t *CreateNode(void *data)
{
    node_t *new_node = NULL;

    assert(NULL != data);

    new_node = (node_t*)malloc(sizeof(node_t));

    if (NULL == new_node)
    {
        return NULL;
    }

    new_node->data = data;

    return new_node;
}

/******************************************************************************/
void Destroy(node_t *head)
{
    node_t *temp = head;

    assert(NULL != head);

    while(NULL != head)
    {
        temp = head->next;
        
        free(head);

        head = NULL;

        head = temp;
    }
}

/******************************************************************************/
node_t *PushNode(node_t *head, void *data)
{
    node_t *new_head = NULL;

    assert(NULL != data);

    new_head = CreateNode(data);

    new_head->next = head;

    return new_head;
}

void PrintList(node_t *head)
{
    node_t *temp = NULL;

    assert(head);

    temp = head;

    while(temp)
    {
        printf("%d -> ", *(int *)temp->data);
        temp = temp->next;
    }
    puts("NULL");
}

void SaritTestInterSection(void)
{
    int x = 1, y = 2 , z = 3, w = 4, t = 5;
    node_t head1, node1_one, node1_two, node1_three, tail1;
    node_t head2, node2_one;
    node_t *ptr1 = &head1;
    node_t *ptr2 = &head2;
    
    head1.data = &x;
    head1.next = &node1_one;
    
    head2.data = &x;
    head2.next = &node2_one;
    
    node1_one.data = &y;
    node1_one.next = &node1_two;
    
    node2_one.data = &y;
    node2_one.next = &node1_two;
    
    node1_two.data = &z;
    node1_two.next = &node1_three;
    
    node1_three.data = &w;
    node1_three.next = &tail1;
    
    tail1.data = &t;
    tail1.next = NULL;
    
    ptr1 = FindIntersection(ptr1,ptr2);
    
    TEST("TestInterSection", ptr1, &node1_two);
}


void TestSlist(void)
{
    node_t *list_1 = NULL;
    node_t *list_2 = NULL;

    int int_arr[7] = {10, 9, 8, 7, 6, 5, 4};
    
    list_1 = PushNode(list_1, &int_arr[0]);
    list_1 = PushNode(list_1, &int_arr[1]);
    list_1 = PushNode(list_1, &int_arr[2]);
    list_1 = PushNode(list_1, &int_arr[3]);
    list_1 = PushNode(list_1, &int_arr[4]);
    list_1 = PushNode(list_1, &int_arr[5]);
    list_1 = PushNode(list_1, &int_arr[6]);

    list_2 = PushNode(list_2, &int_arr[3]);
    list_2 = PushNode(list_2, &int_arr[4]);
    list_2 = PushNode(list_2, &int_arr[5]);
    list_2 = PushNode(list_2, &int_arr[6]); 


    printf("list1: ");
    PrintList(list_1);

    printf("list2: ");
    PrintList(list_2);

    list_1 = Flip(list_1);
    puts("Flip test: ");
    printf("list1: ");
    PrintList(list_1);

    TEST("HasLoop", HasLoop(list_1), 0); /* I dont check HasLoop because
    it will have problem with destroy */

    printf("FindIntersection: should ret NULL %p\n", 
        (void *)FindIntersection(list_1, list_2));

    SaritTestInterSection();

    Destroy(list_1);
    Destroy(list_2);
}











