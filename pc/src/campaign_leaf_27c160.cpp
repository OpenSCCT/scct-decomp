// campaign_leaf_27c160.cpp -- one function at file offset 0x27c160, preferred VA 0x10b7c160. It
// stores its float argument in the ten-entry array at offset 0x780 at the index held in the byte
// at offset 0x77c, then advances that index, wrapping to 0 at 10. The class, method and member
// names are invented; the offset and the bytes are the binary's.

class UnkType_10b7c160
{
public:
    unsigned char unk_0[0x77c];
    unsigned char unk_77c;
    unsigned char unk_77d[3];
    float unk_780[10];

    void Unk_10b7c160(float Value);
};

// UnkType_10b7c160::Unk_10b7c160
void UnkType_10b7c160::Unk_10b7c160(float Value)
{
    unk_780[unk_77c] = Value;
    unk_77c++;
    if ( unk_77c >= 10 )
    {
        unk_77c = 0;
    }
}
