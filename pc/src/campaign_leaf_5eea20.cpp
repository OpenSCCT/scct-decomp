// campaign_leaf_5eea20.cpp -- one function at file offset 0x5eea20, preferred VA 0x10eeea20. When
// the byte at offset 8 is set it copies the 16-byte value at offset 0x10 to Out and returns true;
// otherwise it returns false. The class, method, structure and member names are invented; the
// offset and the bytes are the binary's.

struct UnkType_10eeea20_Value
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_10eeea20
{
public:
    unsigned char unk_0[8];
    bool unk_8;
    unsigned char unk_9[7];
    UnkType_10eeea20_Value unk_10;

    bool GetUnk10(UnkType_10eeea20_Value& Out);
};

// UnkType_10eeea20::GetUnk10
bool UnkType_10eeea20::GetUnk10(UnkType_10eeea20_Value& Out)
{
    if ( !unk_8 )
    {
        return false;
    }
    Out = unk_10;
    return true;
}
