#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ip-arg.h"

uint32_t ipArg_returnTheSubnetIp(uint32_t ip, uint32_t mask)
{
    return (ip & mask);
}

uint32_t ipArg_returnTheBroadcastIp(uint32_t ip, uint32_t mask)
{
    return (ip | ~mask);
}

uint32_t ipArg_nmbOfHosts(uint32_t mask)
{
    //guard againt 32 /31 bit mask case where this case would return -1
    if(~mask > 0)
    {
        return ~mask - 1;
    }
    else 
    {
        return 0;
    }
}

int ipArg_ipConversion(const char *source, uint32_t *ip, uint32_t *mask)
{
    uint32_t maskPrototype = 0xFFFFFFFF;
    int i,j,k;
    unsigned short octet;
    char aux[3];
    int octetWatches = 0;

    i = 0;
    k = 0;
    for(j = 0; source[j] != '\0'; j++)
    {
        /*checking if the sign is corrent)*/
        if( !(source[j] == '.' ||
              source[j] == '/' ||
              (source[j] >= '0' && source[j] <= '9') ) )
        {
            return 1;
        }

        //terminating early in case of oversized octet 
        if(j-k > 3)
        {
            return 2;
        }

        if(source[j] == '.' || source[j] == '/')
        {
            octet = atoi(strncpy(aux, source+k, j-k));

            if(octet > 255 ||
               octetWatches > 4 ||
               (octetWatches == 4 && source[j] != '/'))
            {
                return 2;
            }
            *ip = *ip << 8;
            *ip = *ip | octet;
            i++;
            k = j + 1;
            octetWatches++;
        }

        if(source[j+1] == '\0')
        {
            if( ((j-k+1) > 2) || ((j-k+1) < 1) )
                return 3;

            aux[2] = '\0';
            aux[1] = 0;

            octet = atoi(strncpy(aux, source+k, j-k+1));

            if(octet > 32 || octet < 1)
                return 3;
            octet = 32 - octet;
            *mask = maskPrototype;
            while(octet--)
            {
                *mask = *mask << 1;
            }
        }
    }
    return 0;
}