// campaign_leaf_29e410.cpp -- one function at file offset 0x29e410, preferred VA 0x10b9e410. It
// returns 1 when the object at offset 0x518 exists, its first argument indexes its array at offset
// 0x68 (count at 0x6c), and the word at offset 0x2c of that 0x3c-byte entry has every bit of the
// second argument set; otherwise 0. The class, method and member names are invented; the offset
// and the bytes are the binary's.

struct UnkType_10b9e410_Entry
{
    unsigned char unk_0[0x2c];
    int unk_2c;
    unsigned char unk_30[0x3c - 0x30];
};

class UnkType_10b9e410_Owner
{
public:
    unsigned char unk_0[0x68];
    UnkType_10b9e410_Entry* unk_68;
    int unk_6c;
};

class UnkType_10b9e410
{
public:
    unsigned char unk_0[0x518];
    UnkType_10b9e410_Owner* unk_518;

    int Unk_10b9e410(int Index, int Mask);
};

// UnkType_10b9e410::Unk_10b9e410
int UnkType_10b9e410::Unk_10b9e410(int Index, int Mask)
{
    if ( unk_518 && unk_518->unk_6c > Index )
    {
        return ( unk_518->unk_68[Index].unk_2c & Mask ) == Mask;
    }
    return 0;
}
