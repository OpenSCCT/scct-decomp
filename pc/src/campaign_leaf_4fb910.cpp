// campaign_leaf_4fb910.cpp -- method at VA 0x10dfb910: returns the performance counter from
// QueryPerformanceCounter times the double at 0x8 (seconds per count). The class, member and
// method names are invented; the import is named by the retail import table.

#include "campaign_import_QueryPerformanceCounter.h"

class UnkType_10dfb910
{
public:
    double Unk_10dfb910();

private:
    LARGE_INTEGER unk_0;
    double unk_8;
};

// UnkType_10dfb910::Unk_10dfb910
double UnkType_10dfb910::Unk_10dfb910()
{
    LARGE_INTEGER Count;

    QueryPerformanceCounter(&Count);
    return Count.QuadPart * unk_8;
}
