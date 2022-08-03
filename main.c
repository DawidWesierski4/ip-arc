#include <stdlib.h>
#include <stdio.h>
#include "ip-arg.h"

int main(int argc, char *argv[])
{
    uint32_t i;
    uint32_t ip;
    uint32_t mask;

    for(i=1;i<argc;i++)
    {
        ip = 0;
        mask = INT32_MAX;
        if(!ipArg_checkIfCorrectFormat(argv[i]))
        {
            printf("IP is incorrect exiting now\n");
            return 0;
        }
        if(!ipArg_ipConversion(argv[i],&ip,&mask))
        {
            printf("idk smthing failed \n");
            return 0;
        }
        printf("IP = "IPARG_IPV4_PRINTFORMAT"\n",IPARG_IPV4(ip));
        printf("Mask = "IPARG_IPV4_PRINTFORMAT"\n",IPARG_IPV4(ip));
        ip = ipArg_returnTheSubnetIp(ip,mask);
        printf("Subnet Mask = "IPARG_IPV4_PRINTFORMAT"\n",IPARG_IPV4(ip));
        ip = ipArg_returnTheBroadcastIp(ip,mask);
        printf("Broadcast IP = "IPARG_IPV4_PRINTFORMAT"\n",IPARG_IPV4(ip));
        ip = ipArg_nmbOfHosts(mask);
        printf("Number of hosts = %d\n \n",ip);
    }
    return 0;
}