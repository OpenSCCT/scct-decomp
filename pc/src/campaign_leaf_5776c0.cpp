// campaign_leaf_5776c0.cpp -- one function at file offset 0x5776c0, preferred VA 0x10e776c0. It
// finds Value in the pointer array at offset 8 (count at offset 0xc) and, when found, removes it by
// moving the last element into its place. The class, method and member names are invented; the
// offset and the bytes are the binary's.

struct UnkType_10e776c0_Array
{
    void** Data;
    int Num;

    int FindIndex(void* Value) const
    {
        int i;

        for ( i = 0; i < Num; i++ )
        {
            if ( Data[i] == Value )
            {
                return i;
            }
        }
        return -1;
    }
};

class UnkType_10e776c0
{
public:
    int unk_0;
    int unk_4;
    UnkType_10e776c0_Array unk_8;

    void Unk_10e776c0(void* Value);
};

// UnkType_10e776c0::Unk_10e776c0
void UnkType_10e776c0::Unk_10e776c0(void* Value)
{
    int Index = unk_8.FindIndex(Value);

    if ( Index >= 0 )
    {
        unk_8.Data[Index] = unk_8.Data[--unk_8.Num];
    }
}
