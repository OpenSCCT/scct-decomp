// campaign_leaf_023450.cpp -- method at VA 0x10923450: finds the value of a key in a map keyed by
// strings (0x24-byte pairs in the array at 0x00, hash table at 0x0c, bucket count at 0x10): walks
// the chain of the bucket the free function at VA 0x109013f0 picks for the key text, and returns
// the value at 0x10 of the first pair whose key the free function at VA 0x10ccae30 finds equal, or
// 0. The class, member and method names are invented; the offsets, the sizes and the addresses are
// the binary's.

int Unk_10ccae30(const unsigned short* A, const unsigned short* B);

class UnkType_023450_String
{
public:
    bool operator==(const UnkType_023450_String& Other) const
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

class UnkType_10923450_Value
{
private:
    unsigned char unk_00[0x14];
};

class UnkType_10923450_Pair
{
public:
    int unk_00;
    UnkType_023450_String unk_04;
    UnkType_10923450_Value unk_10;
};

unsigned int Unk_109013f0(const unsigned short* Text);
class UnkType_10923450
{
public:
    UnkType_10923450_Value* Unk_10923450(const UnkType_023450_String& Key);

private:
    UnkType_10923450_Pair* unk_00;
    int unk_04;
    int unk_08;
    int* unk_0c;
    int unk_10;
};

// UnkType_10923450::Unk_10923450
UnkType_10923450_Value* UnkType_10923450::Unk_10923450(const UnkType_023450_String& Key)
{
    for ( int i = unk_0c[Unk_109013f0(*Key) & (unk_10 - 1)]; i != -1; i = unk_00[i].unk_00 )
    {
        if ( unk_00[i].unk_04 == Key )
        {
            return &unk_00[i].unk_10;
        }
    }
    return 0;
}
