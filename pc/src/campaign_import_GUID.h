// campaign_import_GUID.h -- the Win32 GUID structure, as guiddef.h declares it.

#ifndef CAMPAIGN_IMPORT_GUID_H
#define CAMPAIGN_IMPORT_GUID_H

struct _GUID
{
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
};
typedef struct _GUID GUID;

#endif
