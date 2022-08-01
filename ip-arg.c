#include <stdio.h>
#include <stdlib.h>


void fTest(void)
{
    printf("hello world 1\n");
}


int ip_conversion(char* source, unsigned int** ip, int *mask)
{
    printf("IP conversion ");
    for(int i=0;i<4;i++)
    printf(" %d ",ip[i]);
    printf("\n");
    return 1;
}