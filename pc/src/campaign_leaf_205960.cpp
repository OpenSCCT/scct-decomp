// campaign_leaf_205960.cpp -- thiscall method at VA 0x10b05960. When the state word at 0x16f4 is 5,
// it enters the critical section at VA 0x112238a4, passes the word at 0x15d8, the buffers at 0x15dc
// and 0x1660, and the 16-bit value at 0x16e8 to the stdcall function at VA 0x10f27f80, leaves the
// critical section and clears the state word. The class, method and member names are invented.

#include "campaign_global_112238a4.h"
#include "campaign_import_EnterCriticalSection.h"
#include "campaign_import_LeaveCriticalSection.h"

void __stdcall Unk_10f27f80(int Value, void* First, void* Second, unsigned short Count);

class UnkType_10b05960
{
public:
    void Unk_10b05960();

private:
    char unk_0000[0x15d8];
    int unk_15d8;
    char unk_15dc[0x1660 - 0x15dc];
    char unk_1660[0x16e8 - 0x1660];
    unsigned short unk_16e8;
    char unk_16ea[0x16f4 - 0x16ea];
    int unk_16f4;
};

// UnkType_10b05960::Unk_10b05960
void UnkType_10b05960::Unk_10b05960()
{
    if ( unk_16f4 == 5 )
    {
        EnterCriticalSection(&GUnk_112238a4);
        Unk_10f27f80(unk_15d8, unk_15dc, unk_1660, unk_16e8);
        LeaveCriticalSection(&GUnk_112238a4);
        unk_16f4 = 0;
    }
}
