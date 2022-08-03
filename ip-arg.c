#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ip-arg.h"

int ipArg_stringToDec(char *source, uint32_t size)
{
    int i=0;
    int output = 0;
    int PowOfTen = 1;
    for(i=size-1; i>0; i--)
    {
        output = output + PowOfTen * (source[i] - '0');
        PowOfTen *= 10;
    }
    if(source[i] == '-')
    {
        return output * -1;
    }
    else
    {
        return output + PowOfTen * (source[i] - '0');
    }
}

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
    return ~mask -2;
}

int ipArg_checkIfCorrectFormat(const char *source)
{
    uint32_t srcLen = strlen(source);
    uint32_t i,j;
    uint32_t countSuccesfulOctets = 0;

    if(srcLen < 9 || srcLen > 18)
    {
        return 0;
    }

    i = 0;
    j = 1;

    while(source[i] != '\0')
    {
        if(source[i] == '.')
        {
            if(j == 1)
            {
                return 0;
            }

            if(j == 4 && 
               source[i-3] > '2' &&
               source[i-2] > '5' &&
               source[i-1] > '5')
            {
                return 0;
            }
            j = 1;
            i++;

            countSuccesfulOctets++;
            if(countSuccesfulOctets > 4)
            {
                return 0;
            }
            continue;
        }

        if(source[i] == '/')
        {
            if(countSuccesfulOctets != 3)
            {
                return 0;
            }
            j = 1;

            while( source[i+j] != '\0')
            {
                if(source[i+j] < '0' || source[i+j] > '9')
                {
                    return 0;
                }
                j++;
            }

            /*this if says that if the value is greater than
             32 return 0 */
            if(j == 1 || j > 3 || 
              (j == 3 && (source[i+1] > '3' || 
              ( (source[i+1] == '3') && (source[i+2] > '2') ))))
            {
                return 0;
            }

            return 1;
        }

        if(j > 3) //4 decimal octet case
        {
            return 0;
        }
        i++;
        j++;
    }
    return 0;
}

int ipArg_ipConversion(const char *source, uint32_t *ip, uint32_t *mask)
{
    uint32_t maskPrototype = 0xFFFFFFFF;
    int i,j,k;
    unsigned char octet;
    char aux[3];

    i = 0;
    k = 0;
    for(j = 0; source[j] != '\0'; j++)
    {
        if(source[j] == '.' || source[j] == '/')
        {
            octet = ipArg_stringToDec(strncpy(aux, source+k, j-k), j-k);
            *ip = *ip << 8;
            *ip = *ip | octet;
            i++;
            k = j + 1;
        }

        if(source[j+1] == '\0')
        {
            octet = ipArg_stringToDec(strncpy(aux,source+k,j-k+1),j-k+1);
            //printf("octet = %d %s  ",octet,strncpy(aux,source+k,j-k+1));
            octet = 32 - octet;
            *mask = maskPrototype;
            while(octet--)
            {
                *mask = *mask << 1;
            }
        }
    }
    return 1;
}

void ipArg_printAdress(uint32_t id)
{
    int i;
    uint32_t mask = 0xFF;
    for(i = 24; i > 0; i -= 8)
    {
        printf("%u.",(id >> i) & mask);
    }
    printf("%u \n",(id >> i) & mask);
}