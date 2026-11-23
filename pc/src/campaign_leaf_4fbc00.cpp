// campaign_leaf_4fbc00.cpp -- constructor at VA 0x10dfbc00: stores the performance-counter
// frequency from QueryPerformanceFrequency at 0x0 and 1000 over it, the milliseconds per count, at
// 0x8. The class and member names are invented; the import is named by the retail import table.

#include "campaign_import_QueryPerformanceFrequency.h"

class UnkType_10dfbc00
{
public:
    UnkType_10dfbc00();

private:
    LARGE_INTEGER unk_0;
    double unk_8;
};

// UnkType_10dfbc00::UnkType_10dfbc00
UnkType_10dfbc00::UnkType_10dfbc00()
{
    QueryPerformanceFrequency(&unk_0);
    unk_8 = 1000.0 / unk_0.QuadPart;
}
