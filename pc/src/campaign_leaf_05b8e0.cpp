// campaign_leaf_05b8e0.cpp -- free function at VA 0x1095b8e0: returns 0 when the global at VA
// 0x111f55f0 is 0; otherwise reads the global at VA 0x111f55ec inside the critical section at VA
// 0x111f555c and returns it. The function name is invented; the addresses are the binary's.

#include "campaign_global_111f555c.h"
#include "campaign_global_111f55ec.h"
#include "campaign_global_111f55f0.h"
#include "campaign_import_EnterCriticalSection.h"
#include "campaign_import_LeaveCriticalSection.h"

// Unk_1095b8e0
int Unk_1095b8e0()
{
    int Value = 0;
    if ( GUnk_111f55f0 )
    {
        EnterCriticalSection(&GUnk_111f555c);
        Value = GUnk_111f55ec;
        LeaveCriticalSection(&GUnk_111f555c);
    }
    return Value;
}
