// versus_cldata_long.cpp -- storing the wire and host forms of a ubi.com integer
#include "versus_cldata.h"
#include <winsock2.h>

// clDataLong::SetNetworkValue
void clDataLong::SetNetworkValue(unsigned long value)
{
    hostValue = ntohl(value);
    networkValue = value;
}
