/*******************************************************************************
 * Project:    DHCP
 * Author:     HRD28
 * Version:    1.0 - 16/02/2023
			   1.1 - 17/02/2023 : changes: variable names 
			   					  return value of DHCPAllocateIP, DHCPFreeIP
			   					  definition of IPV constant
               1.2 - 17/02/2023 : changed second param's name in Create and 
                                  clarified its meaning
                                  added failure option in Allocate for IP out of
                                  range
                                  changed IPV into IP_OCTET_NUM
*******************************************************************************/
#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /* size_t */

#define IP_OCTET_NUM 4

typedef struct dhcp dhcp_ty;

typedef unsigned char ip_ty[IP_OCTET_NUM];

typedef enum status
{
    SUCCESS = 0,
    FAILURE = 1,
    DOUBLE_FREE_FAILURE = 2
} status_ty;

/*******************************************************************************
 *  creates a new DHCP server with "subnet_ip", that can manage addresses of
 *  "IP_OCTET_NUM", where the subnet contains "subnet_bits_num"
 *  returns a pointer to it on success, NULL otherwise
 *  note: undefined behaviour if "subnet_ip" is NULL
 *  time complexity: O(logn)
*******************************************************************************/
dhcp_ty *DHCPCreate(const ip_ty subnet_ip, size_t subnet_bits_num);

/*******************************************************************************
 *  frees all resources used by "dhcp"
 *  note: undefined behaviour if "dhcp" is NULL
 *  time complexity: O(n)
*******************************************************************************/
void DHCPDestroy(dhcp_ty *dhcp);

/*******************************************************************************
 *  allocates the "requested_ip" if available, or the closest higher available
 *  IP address, if any, and stores the value in "allocated_ip"
 *  if "requested_ip" is not specified, the minimal available IP address will be
 *  allocated
 *  failure occurs if there are no available addresses or if "requested_ip" is
 *  a saved address or does not match the "subnet_ip"
 *  note: saved host IDs are 1, 0, and 255
 *        undefined behaviour if "dhcp" or "allocated_ip" are NULL
 *  time complexity: O(logn)
*******************************************************************************/
status_ty DHCPAllocateIP(dhcp_ty *dhcp,
                                const ip_ty requested_ip, ip_ty allocated_ip);

/*******************************************************************************
 *  frees "ip_to_free" to be available in "dhcp"
 *	returns FAILURE if "ip_to_free" is out of range, or is a saved address
 *	returns DOUBLE_FREE_FAILURE if "ip_to_free" is not allocated by "dhcp"
 *  note: saved host IDs are 1, 0, and 255
 *        undefined behaviour if "dhcp" or "ip_to_free" are NULL
 *  time complexity: O(logn)
*******************************************************************************/
status_ty DHCPFreeIP(dhcp_ty *dhcp, ip_ty ip_to_free);

/*******************************************************************************
 *  returns the number of available IP addresses in "dhcp"
 *  note: undefined behaviour if "dhcp" is NULL
 *  time complexity: O(n)
*******************************************************************************/
size_t DHCPCountFree(const dhcp_ty *dhcp);

#endif /*   __DHCP_H__   */
