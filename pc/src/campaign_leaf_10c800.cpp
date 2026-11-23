// campaign_leaf_10c800.cpp -- one function at file offset 0x10c800, preferred VA 0x10a0c800.
// guess: passes a copy of its own value at offset 0x34, then a copy of the value at 0x4c of each
// entry of its owner's list (the owner at 0x28, its array of pointers at 0x2c), with both arguments to
// its method at VA 0x10a0c080. The value is copied by the constructor at VA 0x10a0bb90.
// The class, member, parameter and callee names are invented; the offset and the bytes are the
// binary's.

class UnkType_10a0c800_Value
{
public:
    unsigned char unk_0[0xc];

    UnkType_10a0c800_Value(const UnkType_10a0c800_Value& Other);
};

class UnkType_10a0c800_Entry
{
public:
    unsigned char unk_0[0x4c];
    UnkType_10a0c800_Value unk_4c;
};

class UnkType_10a0c800_List
{
public:
    UnkType_10a0c800_Entry** Data;
    int ArrayNum;
    int ArrayMax;

    int Num() const
    {
        return ArrayNum;
    }
    UnkType_10a0c800_Entry*& operator()(int Index)
    {
        return Data[Index];
    }
};

class UnkType_10a0c800_Owner
{
public:
    unsigned char unk_0[0x2c];
    UnkType_10a0c800_List unk_2c;
};

class UnkType_10a0c800
{
public:
    unsigned char unk_0[0x28];
    UnkType_10a0c800_Owner* unk_28;
    unsigned char unk_2c[0x34 - 0x2c];
    UnkType_10a0c800_Value unk_34;

    void Unk_10a0c800(int First, int Second);
    void Unk_10a0c080(int First, int Second, UnkType_10a0c800_Value Value);
};

// UnkType_10a0c800::Unk_10a0c800
void UnkType_10a0c800::Unk_10a0c800(int First, int Second)
{
    Unk_10a0c080(First, Second, unk_34);
    for ( int Index = 0; Index < unk_28->unk_2c.Num(); Index++ )
    {
        Unk_10a0c080(First, Second, unk_28->unk_2c(Index)->unk_4c);
    }
}
