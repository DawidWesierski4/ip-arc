#include "ip-arg.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i;
    unsigned int ip;
    int mask;

    for(i=1;i<argc;i++)
    {
        ip = 0;
        mask = 0;
        if(!ipArg_checkIfCorrectFormat("172.168.0.1\\24"))
        {
            printf("IP is incorrect exiting now\n");
        }
        if(!ipArg_ipConversion(argv[i],&ip,&mask))
        {
            printf("idk smthing failed \n");
        }
    }
    return 0;
}