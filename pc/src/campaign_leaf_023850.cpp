// campaign_leaf_023850.cpp -- method at VA 0x10923850: adds a pair to a map keyed by strings (pairs
// of 0x24 bytes in the array at 0x00, hash table at 0x0c, bucket count at 0x10): appends a pair
// through the method at VA 0x109238e0 and constructs it from its two arguments with the constructor
// at VA 0x10923930, chains it into the bucket the free function at VA 0x109013f0 picks for its key
// text, doubles the bucket count and rebuilds the hash with the method at VA 0x10922a80 when the
// pairs outnumber twice the buckets plus 8, and returns the pair's value at 0x10. The class, member
// and method names are invented; the offsets, the sizes and the addresses are the binary's.

class UnkType_023850_String
{
public:
    const unsigned short* operator*() const
    {
        return unk_04 ? unk_00 : L"";
    }

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10923850_Value
{
private:
    unsigned char unk_00[0x14];
};

class UnkType_10923930_023850
{
public:
    UnkType_10923930_023850(const UnkType_023850_String& Key, const UnkType_10923850_Value& Value);

    int unk_00;
    UnkType_023850_String unk_04;
    UnkType_10923850_Value unk_10;
};

class UnkType_109238e0_023850
{
public:
    int Unk_109238e0(int Count, int ElementSize);

    UnkType_10923930_023850* unk_00;
    int unk_04;
    int unk_08;
};

inline void* operator new(unsigned int Size, UnkType_109238e0_023850& Array)
{
    int Index = Array.Unk_109238e0(1, Size);
    return reinterpret_cast<unsigned char*>(Array.unk_00) + Index * Size;
}

unsigned int Unk_109013f0(const unsigned short* Text);

class UnkType_10923850
{
public:
    UnkType_10923850_Value* Unk_10923850(const UnkType_023850_String& Key,
                                     const UnkType_10923850_Value& Value);
    void Unk_10922a80();

private:
    UnkType_109238e0_023850 unk_00;
    int* unk_0c;
    int unk_10;
};

// UnkType_10923850::Unk_10923850
UnkType_10923850_Value* UnkType_10923850::Unk_10923850(const UnkType_023850_String& Key,
                                                 const UnkType_10923850_Value& Value)
{
    UnkType_10923930_023850& Pair = *new(unk_00) UnkType_10923930_023850(Key, Value);
    int Bucket = Unk_109013f0(*Pair.unk_04) & (unk_10 - 1);
    Pair.unk_00 = unk_0c[Bucket];
    unk_0c[Bucket] = unk_00.unk_04 - 1;
    if ( unk_10 * 2 + 8 < unk_00.unk_04 )
    {
        unk_10 *= 2;
        Unk_10922a80();
    }
    return &Pair.unk_10;
}
