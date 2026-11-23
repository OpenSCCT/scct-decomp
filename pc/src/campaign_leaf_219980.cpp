// campaign_leaf_219980.cpp -- a member function at VA 0x10b19980: inside the critical section the
// global at VA 0x112238a4 holds (entered and left with the Win32 EnterCriticalSection and
// LeaveCriticalSection), it calls the member at VA 0x10efe000 after setting the int at 0x16f0 to 1
// when the byte at 0x23e9 is set; otherwise it sets the byte at 0x23ec and passes the narrow
// strings at 0x2406 and 0x2416, the global at VA 0x110dc79c and 1 to the member at VA 0x10efe010.
// The class, method, member and global names are invented; the offsets and addresses are the
// binary's, and the two imports are named by the import table.

#include "campaign_global_112238a4.h"
#include "campaign_global_110dc79c.h"
#include "campaign_import_EnterCriticalSection.h"
#include "campaign_import_LeaveCriticalSection.h"

class UnkType_10b19980
{
public:
    void Unk_10efe000();
    void Unk_10efe010(const char* First, const char* Second, int Value, int Flags);
    void Unk_10b19980();

private:
    unsigned char unk_0000[0x16f0];
    int unk_16f0;
    unsigned char unk_16f4[0x23e9 - 0x16f4];
    bool unk_23e9;
    unsigned char unk_23ea[0x23ec - 0x23ea];
    bool unk_23ec;
    unsigned char unk_23ed[0x2406 - 0x23ed];
    char unk_2406[0x10];
    char unk_2416[0x10];
};

// UnkType_10b19980::Unk_10b19980
void UnkType_10b19980::Unk_10b19980()
{
    if ( unk_23e9 )
    {
        unk_16f0 = 1;
        EnterCriticalSection(&GUnk_112238a4);
        Unk_10efe000();
        LeaveCriticalSection(&GUnk_112238a4);
        return;
    }
    unk_23ec = true;
    EnterCriticalSection(&GUnk_112238a4);
    Unk_10efe010(unk_2406, unk_2416, GUnk_110dc79c, 1);
    LeaveCriticalSection(&GUnk_112238a4);
}
