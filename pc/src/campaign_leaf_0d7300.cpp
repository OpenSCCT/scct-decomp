// campaign_leaf_0d7300.cpp -- one function at file offset 0xd7300, preferred VA 0x109d7300. It
// returns the word at offset 0xc of the element at the index in its second argument of the array
// that the pointer at offset 0x1c of its first argument designates, or 0 for a null first
// argument. The class, struct and method names are invented; the offset and the bytes are the
// binary's.

struct UnkType_109d7300_Elem
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

struct UnkType_109d7300_Obj
{
    unsigned char unk_00[0x1c];     // not read by this function
    UnkType_109d7300_Elem *unk_1c;
};

class UnkType_109d7300
{
public:
    int UnkGetElement(const UnkType_109d7300_Obj *Obj, int Index) const;
};

// UnkType_109d7300::UnkGetElement
int UnkType_109d7300::UnkGetElement(const UnkType_109d7300_Obj *Obj, int Index) const
{
    if ( Obj != 0 )
    {
        return Obj->unk_1c[Index].unk_0c;
    }
    return 0;
}
