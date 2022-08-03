#ifndef _IPARG_
#define _IPARG_

#include <stdint.h>

#define IPARG_IPV4_PRINTFORMAT "%u.%u.%u.%u"
#define IPARG_IPV4(x) (x >> 24),(x >> 16) & 0xFF,\
                      (x >> 8) & 0xFF,(x) & 0xFF

uint32_t ipArg_returnTheSubnetIp(uint32_t ip, uint32_t mask);

uint32_t ipArg_returnTheBroadcastIp(uint32_t ip, uint32_t mask);

uint32_t ipArg_nmbOfHosts(uint32_t mask);

int ipArg_ipConversion(const char *source, uint32_t *ip,
                       uint32_t *mask);

int ipArg_stringToDec(char* source, uint32_t size);

int ipArg_checkIfCorrectFormat(const char *source);

void ipArg_printAdress(uint32_t id);

#endif /* Header guard IPARG */


