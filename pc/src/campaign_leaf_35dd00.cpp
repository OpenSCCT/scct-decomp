// campaign_leaf_35dd00.cpp -- one function at file offset 0x35dd00, preferred VA 0x10c5dd00. It
// calls the method at 0x10c5d760 with Name, then, when Name equals a function-local static built
// once from the retail string "MotionType" and 2 (constructor at 0x10cd4790), calls the method
// at 0x10c5dc90. The class, method, member, local and parameter names are invented; the
// offsets, the string and the bytes are the binary's.

class UnkType_10c5dd00_Name
{
public:
    UnkType_10c5dd00_Name(const unsigned short* Text, int Flags);

    int unk_0;
};

class UnkType_10c5dd00
{
public:
    void Unk_10c5d760(int Name);
    void Unk_10c5dc90();
    void Unk_10c5dd00(int Name);
};

// UnkType_10c5dd00::Unk_10c5dd00
void UnkType_10c5dd00::Unk_10c5dd00(int Name)
{
    Unk_10c5d760(Name);
    static UnkType_10c5dd00_Name MotionTypeName(L"MotionType", 2);
    if ( Name == MotionTypeName.unk_0 )
    {
        Unk_10c5dc90();
    }
}
