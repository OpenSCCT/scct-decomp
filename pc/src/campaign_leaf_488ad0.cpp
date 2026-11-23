// campaign_leaf_488ad0.cpp -- thiscall method at VA 0x10d88ad0. It builds a local reference from
// the 4-byte key it is given by value (constructor at 0x10d8ef70, destructor at 0x10d8edb0) and
// returns false when the reference is not valid (0x10d88810). Otherwise it returns the result of
// the method at 0x10d83dc0 of the referenced object, inverted unless its flag at 0x8 is set. The
// class, method and parameter names are invented.

struct UnkType_10d88ad0_Key
{
    UnkType_10d88ad0_Key(const UnkType_10d88ad0_Key& Other) : unk_0(Other.unk_0) {}

    int unk_0;
};

class UnkType_10d88ad0_Object
{
public:
    bool Unk_10d83dc0();
};

class UnkType_10d88ad0_Ref
{
public:
    UnkType_10d88ad0_Ref(UnkType_10d88ad0_Key Key);
    ~UnkType_10d88ad0_Ref();
    bool Unk_10d88810();

    UnkType_10d88ad0_Object* operator->()
    {
        return Unk_10d88810() ? unk_0 : 0;
    }

private:
    UnkType_10d88ad0_Object* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10d88ad0
{
public:
    bool Unk_10d88ad0(UnkType_10d88ad0_Key Key);

private:
    unsigned char unk_0[0x8];
    bool unk_8;
};

// UnkType_10d88ad0::Unk_10d88ad0
bool UnkType_10d88ad0::Unk_10d88ad0(UnkType_10d88ad0_Key Key)
{
    UnkType_10d88ad0_Ref Ref(Key);

    if ( !Ref.Unk_10d88810() )
    {
        return false;
    }
    if ( unk_8 )
    {
        return Ref->Unk_10d83dc0();
    }
    return !Ref->Unk_10d83dc0();
}
