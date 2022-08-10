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

uint32_t ipArg_returnNmbOfHosts(uint32_t mask)
{
    //guard against 32   bit mask case where this case would return -1
    if(~mask)
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
    char aux[4];
    int octetWatches = 0;

    aux[3] = '\0';
    i = 0;
    k = 0;
    for(j = 0; source[j] != '\0'; j++)
    {
        //checking if the sign is correct
        if( !(source[j] == '.' ||
              source[j] == '/' ||
              (source[j] >= '0' && source[j] <= '9') ) )
        {
            return IPARG_INVALID_CHARACTER;
        }

        //terminating early in case of oversized octet
        if(j-k > 3)
        {
            return IPARG_INVALID_IP;
        }

        if(source[j] == '.' || source[j] == '/')
        {
            octet = atoi(strncpy(aux, source+k, j-k));

            if(octet > 255 ||
               octetWatches > 4 ||
               (octetWatches !=3 && source[j] == '/') )
            {
                return IPARG_INVALID_IP;
            }
            *ip <<= 8;
            *ip |= octet;
            i++;
            k = j + 1;
            octetWatches++;
        }

        if(source[j+1] == '\0')
        {
            if( ((j-k+1) > 2) || ((j-k+1) < 1) )
                return IPARG_INVALID_MASK;

            aux[2] = '\0';
            aux[1] = 0;

            octet = atoi(strncpy(aux, source+k, j-k+1));

            if(octet > 32 || octet < 1)
                return IPARG_INVALID_MASK;

            octet = 32 - octet;
            *mask = maskPrototype;
            *mask <<= octet;
        }
    }
    return 0;
}