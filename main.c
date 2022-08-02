#include "ip-arg.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i;
    unsigned int ip;
    int mask;

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
        ipArg_printAdress(ip);
        ipArg_printAdress(mask);
        ip = ipArg_returnTheSubnetId(ip,mask);
        ipArg_printAdress(ip);
        ip = ipArg_returnTheBroadcastIp(ip,mask);
        ipArg_printAdress(ip);
    }
    return 0;
}