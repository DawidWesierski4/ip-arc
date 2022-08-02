int ipArg_ipConversion(const char* source, unsigned int* ip,
                       unsigned int *mask);

int ipArg_stringToDec(char* source, unsigned int size);

int ipArg_checkIfCorrectFormat(const char* source);

void ipArg_printAdress(unsigned int id);

unsigned int ipArg_returnTheSubnetId(unsigned int ip, unsigned int mask);

unsigned int ipArg_returnTheBroadcastIp(unsigned int ip, unsigned int mask);
