// campaign_leaf_0234f0.cpp -- method at VA 0x109234f0: adds a pair to a map keyed by strings (pairs
// of 0x1c bytes in the array at 0x00, hash table at 0x0c, bucket count at 0x10): appends a pair
// through the method at VA 0x10923570 and constructs it from its two arguments with the constructor
// at VA 0x109235c0, chains it into the bucket the free function at VA 0x109013f0 picks for its key
// text, doubles the bucket count and rebuilds the hash with the method at VA 0x10922b80 when the
// pairs outnumber twice the buckets plus 8, and returns the pair's value at 0x10. The class, member
// and method names are invented; the offsets, the sizes and the addresses are the binary's.

class UnkType_0234f0_String
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

class UnkType_109234f0_Value
{
private:
    unsigned char unk_00[0xc];
};

class UnkType_109235c0_0234f0
{
public:
    UnkType_109235c0_0234f0(const UnkType_0234f0_String& Key, const UnkType_109234f0_Value& Value);

    int unk_00;
    UnkType_0234f0_String unk_04;
    UnkType_109234f0_Value unk_10;
};

class UnkType_10923570_0234f0
{
public:
    int Unk_10923570(int Count, int ElementSize);

    UnkType_109235c0_0234f0* unk_00;
    int unk_04;
    int unk_08;
};

inline void* operator new(unsigned int Size, UnkType_10923570_0234f0& Array)
{
    int Index = Array.Unk_10923570(1, Size);
    return reinterpret_cast<unsigned char*>(Array.unk_00) + Index * Size;
}

unsigned int Unk_109013f0(const unsigned short* Text);

class UnkType_109234f0
{
public:
    UnkType_109234f0_Value* Unk_109234f0(const UnkType_0234f0_String& Key,
                                     const UnkType_109234f0_Value& Value);
    void Unk_10922b80();

private:
    UnkType_10923570_0234f0 unk_00;
    int* unk_0c;
    int unk_10;
};

// UnkType_109234f0::Unk_109234f0
UnkType_109234f0_Value* UnkType_109234f0::Unk_109234f0(const UnkType_0234f0_String& Key,
                                                 const UnkType_109234f0_Value& Value)
{
    UnkType_109235c0_0234f0& Pair = *new(unk_00) UnkType_109235c0_0234f0(Key, Value);
    int Bucket = Unk_109013f0(*Pair.unk_04) & (unk_10 - 1);
    Pair.unk_00 = unk_0c[Bucket];
    unk_0c[Bucket] = unk_00.unk_04 - 1;
    if ( unk_10 * 2 + 8 < unk_00.unk_04 )
    {
        unk_10 *= 2;
        Unk_10922b80();
    }
    return &Pair.unk_10;
}
