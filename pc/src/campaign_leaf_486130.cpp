// campaign_leaf_486130.cpp -- thiscall method at VA 0x10d86130. Between the two calls on the
// object at 0x1131a678 (each skipped while the flag at 0x1131a67c is set) it decrements the
// 16-bit count at 0x04; when the count reaches zero it stores 1 back and, after the second call,
// tail-calls the method at 0x10d86030. The class and method names are invented.

#include "campaign_global_1131a678.h"
#include "campaign_global_1131a67c.h"

class UnkType_10d86130
{
public:
    void Unk_10d86130();
    void Unk_10d86030();

private:
    int unk_0;
    short unk_4;
};

// UnkType_10d86130::Unk_10d86130
void UnkType_10d86130::Unk_10d86130()
{
    bool bAlive = true;

    if ( !GUnk_1131a67c )
    {
        GUnk_1131a678.Unk_10d8b2f0();
    }
    if ( --unk_4 == 0 )
    {
        unk_4 = 1;
        bAlive = false;
    }
    if ( !GUnk_1131a67c )
    {
        GUnk_1131a678.Unk_10d8b300();
    }
    if ( !bAlive )
    {
        Unk_10d86030();
    }
}
