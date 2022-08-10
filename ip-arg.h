#ifndef _IPARG_
#define _IPARG_

#include <stdint.h>

#define IPARG_IPV4_PRINTFORMAT "%u.%u.%u.%u"
#define IPARG_IPV4(x) ((x) >> 24),(((x) >> 16) & 0xFF),\
                      (((x) >> 8) & 0xFF),((x) & 0xFF)

enum IPARG_ERROR_NAMES
{
    IPARG_INVALID_CHARACTER = 1,
    IPARG_INVALID_IP,
    IPARG_INVALID_MASK
};

uint32_t ipArg_returnTheSubnetIp(uint32_t ip, uint32_t mask);

uint32_t ipArg_returnTheBroadcastIp(uint32_t ip, uint32_t mask);

uint32_t ipArg_returnNmbOfHosts(uint32_t mask);

int ipArg_ipConversion(const char *source, uint32_t *ip,
                       uint32_t *mask);

#endif /* Header guard IPARG */