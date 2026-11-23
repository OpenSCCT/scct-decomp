// campaign_leaf_20aaa0.cpp -- thiscall method at VA 0x10b0aaa0 taking an identifier and two
// bytes. Inside the critical section at VA 0x112238a4 it finds the first entry of the list at
// 0x15cc whose word at 0x18 equals the identifier and stores the two bytes at 0x14 and 0x15. The
// class, method and member names are invented; the list is the compiler's library.

#include <list>

#include "campaign_global_112238a4.h"
#include "campaign_import_EnterCriticalSection.h"
#include "campaign_import_LeaveCriticalSection.h"

struct UnkType_10b0aaa0_Entry
{
    int unk_00[5];
    unsigned char unk_14;
    unsigned char unk_15;
    int unk_18;
};

class UnkType_10b0aaa0
{
public:
    void Unk_10b0aaa0(int Id, unsigned char First, unsigned char Second);

private:
    char unk_0000[0x15cc];
    std::list<UnkType_10b0aaa0_Entry> unk_15cc;
};

// UnkType_10b0aaa0::Unk_10b0aaa0
void UnkType_10b0aaa0::Unk_10b0aaa0(int Id, unsigned char First, unsigned char Second)
{
    std::list<UnkType_10b0aaa0_Entry>::iterator It;

    EnterCriticalSection(&GUnk_112238a4);
    for ( It = unk_15cc.begin(); It != unk_15cc.end(); ++It )
    {
        if ( Id == It->unk_18 )
        {
            It->unk_14 = First;
            It->unk_15 = Second;
            break;
        }
    }
    LeaveCriticalSection(&GUnk_112238a4);
}
