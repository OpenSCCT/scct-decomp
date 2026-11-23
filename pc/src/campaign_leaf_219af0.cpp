// campaign_leaf_219af0.cpp -- a member function at VA 0x10b19af0: inside the critical section the
// global at VA 0x112238a4 holds (entered and left with the Win32 EnterCriticalSection and
// LeaveCriticalSection), it passes the narrow string at 0x1f5a and the unsigned short at 0x1fdc to
// the member at VA 0x10efdfe0. When that returns true and the byte at 0x23e9 is set, it sets the
// int at 0x16f0 to 1 and calls the member at VA 0x10efe000 inside the critical section; when it
// returns true and the byte is clear, it sets the int to 8. It stores the result in the byte at
// 0x23eb and returns it. The class, method, member and global names are invented; the offsets and
// addresses are the binary's, and the two imports are named by the import table.

#include "campaign_global_112238a4.h"
#include "campaign_import_EnterCriticalSection.h"
#include "campaign_import_LeaveCriticalSection.h"

class UnkType_10b19af0
{
public:
    bool Unk_10efdfe0(const char* Text, unsigned short Value);
    void Unk_10efe000();
    bool Unk_10b19af0();

private:
    unsigned char unk_0000[0x16f0];
    int unk_16f0;
    unsigned char unk_16f4[0x1f5a - 0x16f4];
    char unk_1f5a[0x1fdc - 0x1f5a];
    unsigned short unk_1fdc;
    unsigned char unk_1fde[0x23e9 - 0x1fde];
    bool unk_23e9;
    unsigned char unk_23ea;
    bool unk_23eb;
};

// UnkType_10b19af0::Unk_10b19af0
bool UnkType_10b19af0::Unk_10b19af0()
{
    EnterCriticalSection(&GUnk_112238a4);
    bool Result = Unk_10efdfe0(unk_1f5a, unk_1fdc);
    LeaveCriticalSection(&GUnk_112238a4);
    if ( Result )
    {
        if ( unk_23e9 )
        {
            unk_16f0 = 1;
            EnterCriticalSection(&GUnk_112238a4);
            Unk_10efe000();
            LeaveCriticalSection(&GUnk_112238a4);
        }
        else
        {
            unk_16f0 = 8;
        }
    }
    unk_23eb = Result;
    return Result;
}
