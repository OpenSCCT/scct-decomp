// campaign_leaf_023670.cpp -- method at VA 0x10923670: sets the value of a key in a map keyed by
// strings (0x24-byte pairs in the array at 0x00, hash table at 0x0c, bucket count at 0x10): walks
// the chain of the bucket the free function at VA 0x109013f0 picks for the key text; when the free
// function at VA 0x10ccae30 finds a pair's key equal, copies the second argument into its value at
// 0x10 (a map: its pairs through the method at VA 0x10923730, its bucket count, then its hash
// rebuilt by the method at VA 0x10922b80) and returns that value, otherwise returns what the method
// at VA 0x10923850 returns for both arguments. The class, member and method names are invented; the
// offsets, the sizes and the addresses are the binary's.

unsigned int Unk_109013f0(const unsigned short* Text);
int Unk_10ccae30(const unsigned short* A, const unsigned short* B);

class UnkType_023670_String
{
public:
    bool operator==(const UnkType_023670_String& Other) const
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

class UnkType_10923730_023670
{
public:
    UnkType_10923730_023670& Unk_10923730(const UnkType_10923730_023670& Other);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_023670_Value
{
public:
    UnkType_023670_Value& operator=(const UnkType_023670_Value& Other)
    {
        unk_00.Unk_10923730(Other.unk_00);
        unk_10 = Other.unk_10;
        Unk_10922b80();
        return *this;
    }

    void Unk_10922b80();

private:
    UnkType_10923730_023670 unk_00;
    int* unk_0c;
    int unk_10;
};

class UnkType_10923670_Pair
{
public:
    int unk_00;
    UnkType_023670_String unk_04;
    UnkType_023670_Value unk_10;
};

class UnkType_10923670
{
public:
    UnkType_023670_Value* Unk_10923670(const UnkType_023670_String& Key,
                                  const UnkType_023670_Value& Value);
    UnkType_023670_Value* Unk_10923850(const UnkType_023670_String& Key,
                                   const UnkType_023670_Value& Value);

private:
    UnkType_10923670_Pair* unk_00;
    int unk_04;
    int unk_08;
    int* unk_0c;
    int unk_10;
};

// UnkType_10923670::Unk_10923670
UnkType_023670_Value* UnkType_10923670::Unk_10923670(const UnkType_023670_String& Key,
                                                const UnkType_023670_Value& Value)
{
    for ( int i = unk_0c[Unk_109013f0(*Key) & (unk_10 - 1)]; i != -1; i = unk_00[i].unk_00 )
    {
        if ( unk_00[i].unk_04 == Key )
        {
            unk_00[i].unk_10 = Value;
            return &unk_00[i].unk_10;
        }
    }
    return Unk_10923850(Key, Value);
}
