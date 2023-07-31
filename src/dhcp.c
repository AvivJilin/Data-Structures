/*******************************************************************************
 * Project:    DHCP
 * Author:     Aviv Jilin
 * Tester:     Nazmeya
 * Version:    1.0 - 18/02/2023
*******************************************************************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <assert.h>

#include "dhcp.h" 

#define IPV 4
#define IP_BITS 32
#define MAX_CHAR 255
#define NUM_OF_BITS 7

typedef enum children
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_CHILDREN
} children_ty;

typedef enum occupied
{
    NOT_OCCUPIED = 0,
    OCCUPIED = 1
} occupied_ty;

enum bool_val {FALSE = 0, TRUE = 1};

typedef struct dhcp_node trie_node_ty;
struct dhcp_node
{
    trie_node_ty *parent;
    trie_node_ty *child[NUM_OF_CHILDREN];
    int is_occupied;
};

struct dhcp
{
    trie_node_ty *root;
    const ip_ty subnet_ip; 
    size_t subnet_bits_num;
};

/****************************************static functions**********************/
static trie_node_ty *CreateNode(dhcp_ty *dhcp);
static void InitNode(trie_node_ty *node, trie_node_ty *parent,
                trie_node_ty *l_child, trie_node_ty *r_child, int is_occupied);
static status_ty AllocateReservedAddresses(trie_node_ty *root, size_t host_bits);
static trie_node_ty *CreateChild(trie_node_ty *node, children_ty child);
static void DeleteTrie(trie_node_ty *node);
static size_t DHCPCountOccIMP(trie_node_ty *node);
static status_ty CheckIfSubnet(dhcp_ty *dhcp, const ip_ty ip);
static status_ty CheckSavedAddresses(const ip_ty ip);


/* naz : add asserts if needed */
dhcp_ty *DHCPCreate(const ip_ty subnet_ip, size_t subnet_bits_num)
{
    dhcp_ty *dhcp = NULL;
    trie_node_ty *root = NULL;
    size_t host_bits = 0;

    assert(NULL != subnet_ip);

    dhcp = (dhcp_ty *)malloc(sizeof(dhcp_ty));

    if (NULL == dhcp)
    {
        return NULL;
    }

    root = CreateNode(dhcp);
    host_bits = IP_BITS - subnet_bits_num;

    if (NULL == root)
    {
        free(dhcp);
        dhcp = NULL;

        return NULL;
    }

    InitNode(root, NULL, NULL, NULL, NOT_OCCUPIED);

    dhcp->root = root;

    if (FAILURE == AllocateReservedAddresses(root, host_bits))
    {
        DHCPDestroy(dhcp);
        dhcp = NULL;
        
        return NULL;
    }

    memcpy((void *)dhcp->subnet_ip, (void *)subnet_ip, IP_OCTET_NUM);
    
    dhcp->subnet_bits_num = subnet_bits_num;

    return dhcp;

}

static trie_node_ty *CreateNode(dhcp_ty *dhcp)
{
    trie_node_ty *new_node = NULL;

    assert(NULL != dhcp);

    new_node = (trie_node_ty *)malloc(sizeof(trie_node_ty));

    if (NULL == new_node)
    {
        return NULL;
    }

    return new_node;
}

static void InitNode(trie_node_ty *node, trie_node_ty *parent,
                trie_node_ty *l_child, trie_node_ty *r_child, int is_occupied)
{
    node->parent = parent;
    node->child[LEFT] = l_child;
    node->child[RIGHT] = r_child;
    node->is_occupied = is_occupied;
}

static status_ty AllocateReservedAddresses(trie_node_ty *root, size_t host_bits)
{
    size_t count_bits = 0;
    trie_node_ty *node_left = NULL;
    trie_node_ty *node_right = NULL;
    trie_node_ty *node = NULL;


    assert(NULL != root);

    node_left = root;
    node_right = root;

    while((count_bits < host_bits) && (NULL != node_left) && (NULL != node_right))
    {
        node_left = CreateChild(node_left, LEFT);
        node_right = CreateChild(node_right, RIGHT);
        ++count_bits;
    }

    if ((NULL != node_left) && (NULL != node_right))
    {
        node_left->is_occupied = TRUE;
        node_right->is_occupied = TRUE;

        node = CreateChild(node_left->parent, RIGHT);

        if(NULL != node)
        {
            node_left->parent->is_occupied = TRUE;
            node->is_occupied = TRUE;

            return SUCCESS;
        }
    }

    return FAILURE;
}

static trie_node_ty *CreateChild(trie_node_ty *node, children_ty child)
{
    trie_node_ty *new_node = NULL;
    
    assert(NULL != node);
    
    new_node = (trie_node_ty *)malloc(sizeof(trie_node_ty));
    
    if (NULL == new_node)
    {
        return NULL;
    }
    
    node->child[child] = new_node;
    
    new_node->parent = node;
    new_node->child[LEFT] = NULL;
    new_node->child[RIGHT] = NULL;
    new_node->is_occupied = 0;
    return new_node;
}

void DHCPDestroy(dhcp_ty *dhcp)
{
    assert(NULL != dhcp);

    if (NULL == dhcp)
    {
        return;
    }

    DeleteTrie(dhcp->root);

    free(dhcp);
    dhcp = NULL;
}

static void DeleteTrie(trie_node_ty *node)
{
    if (NULL == node)
    {
        return;
    }

    DeleteTrie(node->child[LEFT]);
    DeleteTrie(node->child[RIGHT]);

    free(node);
    node = NULL;
}


status_ty DHCPAllocateIP(dhcp_ty *dhcp, const ip_ty requested_ip, ip_ty allocated_ip)
{
    size_t i = 0;
    size_t host_bits_num = 0; 
    unsigned char bit_mask = 0;
    unsigned char host = 0;
    unsigned char bit = 0;
    trie_node_ty *node = NULL; 

    assert(NULL != dhcp);

    node = dhcp->root;
    host_bits_num = IP_BITS - dhcp->subnet_bits_num;

    /* Check if the requested IP is in the same subnet as the DHCP server */
    if (FAILURE == CheckIfSubnet(dhcp, requested_ip))
    {
        return FAILURE;
    }

    if (FAILURE == CheckSavedAddresses(requested_ip))
    {
        return FAILURE;
    }

    host = requested_ip[IP_OCTET_NUM - 1]; 
    
    /* Iterate over the host bits to find an unoccupied IP address by the requested ip */
    while ((requested_ip[IP_OCTET_NUM - 1] - 1) != host)
    {

        for (i = 0; i < host_bits_num; ++i)
        {
            bit_mask = 1 << (NUM_OF_BITS - i);
            bit = host & bit_mask;

            if (0 != bit)
            {
                bit = 1;
            }

            if (NULL == node->child[bit])
            {
                node = CreateChild(node, bit);

                if (NULL == node)
                {
                    return FAILURE;
                }
            }
            else
            {
                node = node->child[bit];
            }
        }


        if(OCCUPIED == node->is_occupied)
        {
            if (host == MAX_CHAR)
            {
                host = 2;
            }
            else
            {
                host += 1;   
            }
            node = dhcp->root;   
        }
        else
        {
            break;
        }
    }

    if (NOT_OCCUPIED == node->is_occupied)
    {
        node->is_occupied = OCCUPIED;
        memcpy(allocated_ip, requested_ip, IPV);

        return SUCCESS;
    }
    return FAILURE;
}

status_ty DHCPFreeIP(dhcp_ty *dhcp, ip_ty ip_to_free)
{
    size_t i = 0;
    size_t host_bits_num = 0;
    unsigned char host = 0;
    unsigned char bit_mask = 0;
    unsigned char bit = 0;
    trie_node_ty *node = NULL; 

    assert(NULL != dhcp);

    node = dhcp->root;
    host_bits_num = IP_BITS - dhcp->subnet_bits_num;

    if (FAILURE == CheckIfSubnet(dhcp, ip_to_free))
    {
        return DOUBLE_FREE_FAILURE;
    }

    if (FAILURE == CheckSavedAddresses(ip_to_free))
    {
        return FAILURE;
    }

    host = ip_to_free[IP_OCTET_NUM - 1];
    for (i = 0; i < host_bits_num; ++i)
    {
        bit_mask = 1 << (NUM_OF_BITS - i); 
        bit = host & bit_mask;

        if (0 != bit)
        {
            bit = 1;
        }

        if (NULL == node->child[bit])
        {
            return DOUBLE_FREE_FAILURE;  
        }
        else
        {
            node = node->child[bit];
        }
    }

    if (NOT_OCCUPIED == node->is_occupied ) 
    {
        return DOUBLE_FREE_FAILURE;
    }
    else
    {
        node->is_occupied = NOT_OCCUPIED;
        return SUCCESS;
    }
}

size_t DHCPCountFree(const dhcp_ty *dhcp)
{
    assert(NULL != dhcp);

    return MAX_CHAR - DHCPCountOccIMP(dhcp->root);
}

static size_t DHCPCountOccIMP(trie_node_ty *node)
{

    if (NULL == node) 
    {
        return 0;
    }
    
    
   if (OCCUPIED == node->is_occupied)
    {
        return 1;
    }
    
    return DHCPCountOccIMP(node->child[LEFT]) + DHCPCountOccIMP(node->child[RIGHT]);
}

static status_ty CheckIfSubnet(dhcp_ty *dhcp, const ip_ty ip)
{
    int i = 0;

    if(NULL == ip)
    {
        return FAILURE;
    }

    for (i = 0; i < IP_OCTET_NUM - 1; ++i)
    {
        if (ip[i] != dhcp->subnet_ip[i])
        {
            return FAILURE;
        }
    } 
    return SUCCESS;   
}

static status_ty CheckSavedAddresses(const ip_ty ip)
{
    if(NULL == ip)
    {
        return FAILURE;
    }

    if ((ip[3] == 1) || (ip[3] == 0) || (ip[3] == MAX_CHAR))
    {
        return FAILURE;
    }
    return SUCCESS;   
}






