// campaign_leaf_49f9e0.cpp -- thiscall method at VA 0x10d9f9e0. It builds a key from the global at
// 0x1131b2ac (0x10d9d3c0) and this object's key at 0x4 (0x10d9d3a0), then a local reference from
// that key (constructor at 0x10d8ef70, destructor at 0x10d8edb0). When the reference is valid
// (0x10d9f1d0) it passes the given value and 0x3ffffe to the method at 0x10dd34d0 of the
// referenced object and returns true, else false. The class, method and parameter names are
// invented.

#include "campaign_global_1131b2ac.h"

struct UnkType_10d9f9e0_Key
{
    UnkType_10d9f9e0_Key(int Value, UnkType_10d9f9e0_Key Other) : unk_0(0)
    {
        Unk_10d9d3c0(Value);
        Unk_10d9d3a0(Other);
    }

    UnkType_10d9f9e0_Key(const UnkType_10d9f9e0_Key& Other) : unk_0(Other.unk_0) {}
    void Unk_10d9d3c0(int Value);
    void Unk_10d9d3a0(UnkType_10d9f9e0_Key Other);

    int unk_0;
};

class UnkType_10d9f9e0_Object
{
public:
    void Unk_10dd34d0(int Value, int Mask);
};

class UnkType_10d9f9e0_Ref
{
public:
    UnkType_10d9f9e0_Ref(UnkType_10d9f9e0_Key Key);
    ~UnkType_10d9f9e0_Ref();
    bool Unk_10d9f1d0();

    UnkType_10d9f9e0_Object* operator->()
    {
        return Unk_10d9f1d0() ? unk_0 : 0;
    }

private:
    UnkType_10d9f9e0_Object* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10d9f9e0
{
public:
    bool Unk_10d9f9e0(int Value);

private:
    int unk_0;
    UnkType_10d9f9e0_Key unk_4;
};

// UnkType_10d9f9e0::Unk_10d9f9e0
bool UnkType_10d9f9e0::Unk_10d9f9e0(int Value)
{
    UnkType_10d9f9e0_Key Key(GUnk_1131b2ac, unk_4);

    UnkType_10d9f9e0_Ref Ref(Key);

    if ( !Ref.Unk_10d9f1d0() )
    {
        return false;
    }
    Ref->Unk_10dd34d0(Value, 0x3ffffe);
    return true;
}
