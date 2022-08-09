#include <stdlib.h>
#include <stdio.h>
#include "ip-arg.h"

int main(int argc, char *argv[])
{
    uint32_t i;
    uint32_t ip;
    uint32_t mask;

    for(i=1; i<argc; i++)
    {
        ip = 0;
        mask = INT32_MAX;
        switch(ipArg_ipConversion(argv[i], &ip, &mask))
        {
            case IPARG_INVALID_CHARACTER:
                printf("Ip consist erroneous sign \n");
                return 1;
            case IPARG_INVALID_IP:
                printf("Ip is incorrect\n");
                return 1;
            case IPARG_INVALID_MASK:
                printf("Mask is incorrect\n");
                return 1;

        }
        printf("IP = "IPARG_IPV4_PRINTFORMAT"\n", IPARG_IPV4(ip));
        printf("Mask = " IPARG_IPV4_PRINTFORMAT "\n", IPARG_IPV4(mask));
        ip = ipArg_returnTheSubnetIp(ip,mask);
        printf("Subnet Mask = "IPARG_IPV4_PRINTFORMAT"\n",IPARG_IPV4(ip));
        ip = ipArg_returnTheBroadcastIp( ip, mask );
        printf("Broadcast IP = " IPARG_IPV4_PRINTFORMAT "\n", IPARG_IPV4(ip));
        ip = ipArg_nmbOfHosts( mask );
        printf("Number of hosts = %d\n \n", ip);
    }
    return 0;
}