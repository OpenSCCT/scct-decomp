// campaign_leaf_00d6e0.cpp -- method at VA 0x1090d6e0: closes the handle at 0x04 with CloseHandle
// unless it is invalid, opens the file its argument names with CreateFileW for reading (shared for
// reading, existing files only, flags 0x60000000), stores the handle at 0x04 and returns whether it
// is valid. The class, member and method names are invented; the offset and the constants are the
// binary's.

#include "campaign_import_CloseHandle.h"
#include "campaign_import_CreateFileW.h"

class UnkType_1090d6e0
{
public:
    int Unk_1090d6e0(const unsigned short* FileName);

private:
    int unk_00;
    HANDLE unk_04;
};

// UnkType_1090d6e0::Unk_1090d6e0
int UnkType_1090d6e0::Unk_1090d6e0(const unsigned short* FileName)
{
    if ( unk_04 != INVALID_HANDLE_VALUE )
    {
        CloseHandle(unk_04);
    }
    unk_04 = CreateFileW(FileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING,
                         FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING, 0);
    return unk_04 != INVALID_HANDLE_VALUE;
}
