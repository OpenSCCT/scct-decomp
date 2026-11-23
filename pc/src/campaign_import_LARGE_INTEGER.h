// campaign_import_LARGE_INTEGER.h -- the Win32 LARGE_INTEGER union, as KERNEL32 declares it.

#ifndef CAMPAIGN_IMPORT_LARGE_INTEGER_H
#define CAMPAIGN_IMPORT_LARGE_INTEGER_H

union _LARGE_INTEGER
{
    struct
    {
        unsigned long LowPart;
        long HighPart;
    } u;
    __int64 QuadPart;
};
typedef union _LARGE_INTEGER LARGE_INTEGER;

#endif
