// campaign_leaf_6ed7e0.cpp -- thiscall method at VA 0x10fed7e0: stores a value under a string key
// in an open-addressing hash table. The block at 0x00 holds three arrays of (mask at 0x08 + 1)
// ints: the key hashes (-1 marks a free slot), the key pointers and the values; the count is at
// 0x04. The hash is h * 31 + c over the key's characters, without the sign bit. The table grows
// through the method at VA 0x10fedb50 when the count is more than half the mask, and keys are
// compared with the function at VA 0x10dffc00. The class, method and member names are invented;
// the offsets and addresses are the binary's.

int Unk_10dffc00(const char* First, const char* Second);

// guess: the string hash, h * 31 + c over the characters.
inline int HashString(const char* String)
{
    int Hash;
    int i;

    Hash = 0;
    for ( i = 0; String[i] != 0; i++ )
    {
        Hash = Hash * 31 + String[i];
    }
    return Hash;
}

class UnkType_10fed7e0
{
public:
    void Unk_10fed7e0(const char* Key, int Value);
    void Unk_10fedb50(int Count);

private:
    int* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10fed7e0::Unk_10fed7e0
void UnkType_10fed7e0::Unk_10fed7e0(const char* Key, int Value)
{
    int Hash;
    int i;

    Hash = HashString(Key) & 0x7fffffff;
    if ( unk_4 * 2 > unk_8 )
    {
        Unk_10fedb50(unk_8 * 2 + 2);
    }
    i = Hash & unk_8;
    while ( unk_0[i] != -1 )
    {
        if ( unk_0[i] == Hash && Unk_10dffc00(Key, (const char*)unk_0[unk_8 + 1 + i]) == 0 )
        {
            goto Found;
        }
        i = ( i + 1 ) & unk_8;
    }
    unk_4++;
Found:
    unk_0[i] = Hash;
    unk_0[unk_8 + 1 + i] = (int)Key;
    unk_0[( unk_8 + 1 ) * 2 + i] = Value;
}
