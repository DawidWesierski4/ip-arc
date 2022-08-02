#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ip-arg.h"

int ipArg_stringToDec(char* source, unsigned int size)
{
    int i=0;
    int output = 0;
    int PowOfTen = 1;
    for(i=size-1; i>=0; i--)
    {
        output = output + PowOfTen * (source[i] - '0');
        PowOfTen *= 10;
    }

    return output;
}


int ipArg_checkIfCorrectFormat(const char* source)
{
    int srcLen = strlen(source);
    int i,j;
    int countSuccesfulOctets = 0;

    if(srcLen < 12 || srcLen > 21)
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

        if(j > 3) //4 decimal octet case
        {

            return 0;
        }

        if(source[i] == '\\')
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

            if(j == 1 || j > 3 || j == 3 &&
               (source[i+1] > '3' || source[i+1] == '3' && source[i+2] > '2'))
            {
                return 0;
            }

            return 1;
        }
        i++;
        j++;
    }
    return 0;
}

int ipArg_ipConversion(const char* source, unsigned int* ip, unsigned int *mask)
{
    unsigned int maskPrototype = 0xFFFFFFFF;
    int i,j,k;
    char octet;
    char aux[3];
    int sourceLen = strlen(source);
    const char *tmp ;

    i = 0;
    k = 0;
    for(j = 0; source[j] != '\0'; j++)
    {
        if(source[j] == '.' || source[j] == '\\')
        {
            for(int asd = 0;asd < 3;asd++) aux[asd] = 0;
            strncpy(aux,source+k,j-k);
            octet = ipArg_stringToDec(strncpy(aux,source+k,j-k),j-k);
            memset((char*)(ip)+3-i, octet, 1);
            i++;
            k = j+1;
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

void ipArg_printAdress(unsigned int id)
{
    for(int i=0;i<4;i++)
    {
        printf("%d \n",(char)&id+i);
    }
}


unsigned int ipArg_retNetworkId(unsigned int mask, unsigned int id)
{
    return id = id ^ mask;
}