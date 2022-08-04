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
    return ~mask - 1;
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
            aux[2] = '\0';

            octet = atoi(strncpy(aux, source+k, j-k+1));
            //printf("octet = %d %s  ",octet,strncpy(aux,source+k,j-k+1));
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