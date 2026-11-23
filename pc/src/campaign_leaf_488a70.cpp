// campaign_leaf_488a70.cpp -- thiscall method at VA 0x10d88a70 that does not use this. It builds
// a local reference from the 4-byte key it is given by value (constructor at 0x10d8ef70,
// destructor at 0x10d8edb0); when the reference is valid (0x10d88810) it returns the result of
// the method at 0x10d84880 of the referenced object, else false. The class, method and parameter
// names are invented.

struct UnkType_10d88a70_Key
{
    UnkType_10d88a70_Key(const UnkType_10d88a70_Key& Other) : unk_0(Other.unk_0) {}

    int unk_0;
};

class UnkType_10d88a70_Object
{
public:
    bool Unk_10d84880();
};

class UnkType_10d88a70_Ref
{
public:
    UnkType_10d88a70_Ref(UnkType_10d88a70_Key Key);
    ~UnkType_10d88a70_Ref();
    bool Unk_10d88810();

    UnkType_10d88a70_Object* operator->()
    {
        return Unk_10d88810() ? unk_0 : 0;
    }

private:
    UnkType_10d88a70_Object* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10d88a70
{
public:
    bool Unk_10d88a70(UnkType_10d88a70_Key Key);
};

// UnkType_10d88a70::Unk_10d88a70
bool UnkType_10d88a70::Unk_10d88a70(UnkType_10d88a70_Key Key)
{
    UnkType_10d88a70_Ref Ref(Key);

    if ( !Ref.Unk_10d88810() )
    {
        return false;
    }
    return Ref->Unk_10d84880();
}
