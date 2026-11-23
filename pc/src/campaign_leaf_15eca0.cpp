// campaign_leaf_15eca0.cpp -- one function at file offset 0x15eca0, preferred VA 0x10a5eca0.
// It clears the count of the array its second argument refers to and, when its first argument
// selects one of the 0x1c-byte entries of the array at offset 0x1b0 (count at 0x1b4), passes each
// element of that entry's array at offset 0x10 (count at 0x14) to the method at VA 0x10936000 of
// the argument array.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a5eca0_List
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10936000(const int& Item);
};

struct UnkType_10a5eca0_Entry
{
    unsigned char unk_0[0x10];
    int* unk_10;
    int unk_14;
    unsigned char unk_18[0x1c - 0x18];
};

class UnkType_10a5eca0
{
public:
    unsigned char unk_0[0x1b0];
    UnkType_10a5eca0_Entry* unk_1b0;
    int unk_1b4;

    void Unk_10a5eca0(int Index, UnkType_10a5eca0_List& List);
};

// UnkType_10a5eca0::Unk_10a5eca0
void UnkType_10a5eca0::Unk_10a5eca0(int Index, UnkType_10a5eca0_List& List)
{
    List.ArrayNum = 0;
    if ( Index >= 0 && Index < unk_1b4 )
    {
        for ( int i = 0; i < unk_1b0[Index].unk_14; i++ )
        {
            List.Unk_10936000(unk_1b0[Index].unk_10[i]);
        }
    }
}
