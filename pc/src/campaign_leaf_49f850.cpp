// campaign_leaf_49f850.cpp -- thiscall method at VA 0x10d9f850. It builds a key from the global at
// 0x1131b2ac (0x10d9d3c0) and this object's key at 0x4 (0x10d9d3a0), then a local reference from
// that key (constructor at 0x10d8ef70, destructor at 0x10d8edb0), and returns true when the
// reference is valid (0x10d9f1d0) and the method at 0x10d84880 of the referenced object returns
// true. The class, method and parameter names are invented.

#include "campaign_global_1131b2ac.h"

struct UnkType_10d9f850_Key
{
    UnkType_10d9f850_Key(int Value, UnkType_10d9f850_Key Other) : unk_0(0)
    {
        Unk_10d9d3c0(Value);
        Unk_10d9d3a0(Other);
    }

    UnkType_10d9f850_Key(const UnkType_10d9f850_Key& Other) : unk_0(Other.unk_0) {}
    void Unk_10d9d3c0(int Value);
    void Unk_10d9d3a0(UnkType_10d9f850_Key Other);

    int unk_0;
};

class UnkType_10d9f850_Object
{
public:
    bool Unk_10d84880();
};

class UnkType_10d9f850_Ref
{
public:
    UnkType_10d9f850_Ref(UnkType_10d9f850_Key Key);
    ~UnkType_10d9f850_Ref();
    bool Unk_10d9f1d0();

    UnkType_10d9f850_Object* operator->()
    {
        return Unk_10d9f1d0() ? unk_0 : 0;
    }

private:
    UnkType_10d9f850_Object* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10d9f850
{
public:
    bool Unk_10d9f850();

private:
    int unk_0;
    UnkType_10d9f850_Key unk_4;
};

// UnkType_10d9f850::Unk_10d9f850
bool UnkType_10d9f850::Unk_10d9f850()
{
    UnkType_10d9f850_Key Key(GUnk_1131b2ac, unk_4);

    UnkType_10d9f850_Ref Ref(Key);

    if ( !Ref.Unk_10d9f1d0() )
    {
        return false;
    }
    if ( Ref->Unk_10d84880() )
    {
        return true;
    }
    return false;
}
