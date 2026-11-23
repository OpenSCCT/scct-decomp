// campaign_leaf_023b40.cpp -- method at VA 0x10923b40: sets the value of a key in a map keyed by
// strings (0x2c-byte pairs in the array at 0x00, hash table at 0x0c, bucket count at 0x10): walks
// the chain of the bucket the free function at VA 0x109013f0 picks for the key text; when the free
// function at VA 0x10ccae30 finds a pair's key equal, assigns the second argument to its value at
// 0x10 with the operator at VA 0x10923bf0 and returns that value, otherwise returns what the method
// at VA 0x10923d10 returns for both arguments. The class, member and method names are invented; the
// offsets, the sizes and the addresses are the binary's.

unsigned int Unk_109013f0(const unsigned short* Text);
int Unk_10ccae30(const unsigned short* A, const unsigned short* B);

class UnkType_023b40_String
{
public:
    bool operator==(const UnkType_023b40_String& Other) const
    {
        return Unk_10ccae30(**this, *Other) == 0;
    }

    const unsigned short* operator*() const
    {
        return unk_04 ? unk_00 : L"";
    }

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_023b40_Value
{
public:
    UnkType_023b40_Value& operator=(const UnkType_023b40_Value& Other);

private:
    unsigned char unk_00[0x1c];
};

class UnkType_10923b40_Pair
{
public:
    int unk_00;
    UnkType_023b40_String unk_04;
    UnkType_023b40_Value unk_10;
};

class UnkType_10923b40
{
public:
    UnkType_023b40_Value* Unk_10923b40(const UnkType_023b40_String& Key,
                                  const UnkType_023b40_Value& Value);
    UnkType_023b40_Value* Unk_10923d10(const UnkType_023b40_String& Key,
                                   const UnkType_023b40_Value& Value);

private:
    UnkType_10923b40_Pair* unk_00;
    int unk_04;
    int unk_08;
    int* unk_0c;
    int unk_10;
};

// UnkType_10923b40::Unk_10923b40
UnkType_023b40_Value* UnkType_10923b40::Unk_10923b40(const UnkType_023b40_String& Key,
                                                const UnkType_023b40_Value& Value)
{
    for ( int i = unk_0c[Unk_109013f0(*Key) & (unk_10 - 1)]; i != -1; i = unk_00[i].unk_00 )
    {
        if ( unk_00[i].unk_04 == Key )
        {
            unk_00[i].unk_10 = Value;
            return &unk_00[i].unk_10;
        }
    }
    return Unk_10923d10(Key, Value);
}
