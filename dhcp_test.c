#include <stdio.h>

#include "dhcp.h"
#include "tests.h"

static void TestDHCP(void);

int main(void)
{
	TestDHCP();
	PASS;
	return 0;
}


static void TestDHCP(void)
{
	 ip_ty ip_subnet = {1, 2, 3, 0};
	 ip_ty ip1 = {1, 2, 3, 5};
	 ip_ty ip2 = {1, 2, 4, 5};
	
	ip_ty ip1_res;
	dhcp_ty *dhcp = NULL;
	
	dhcp = DHCPCreate(ip_subnet, 24);
	
	if (NULL == dhcp)
	{
		printf("Create Failed\n");
	}
	
	TEST("DHCPAllocateIP", DHCPAllocateIP(dhcp, ip1, ip1_res), SUCCESS);
	TEST("DHCPAllocateIP", DHCPAllocateIP(dhcp, ip2, ip1_res), FAILURE);
	
	TEST("DHCPFreeIP", DHCPFreeIP(dhcp, ip1), SUCCESS);
	
	TEST("DHCPFreeIP", DHCPFreeIP(dhcp, ip1), DOUBLE_FREE_FAILURE);
	
	TEST("DHCPFreeIP", DHCPFreeIP(dhcp, ip_subnet), FAILURE);
	
	TEST("DHCPCountFree", DHCPCountFree(dhcp), 253);
	
	DHCPDestroy(dhcp);
}
