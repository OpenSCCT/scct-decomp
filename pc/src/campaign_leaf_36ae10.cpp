// campaign_leaf_36ae10.cpp -- one function at file offset 0x36ae10, preferred VA 0x10c6ae10. It
// passes (Other, Index) to the method at 0x1099f3f0, builds a function-local static name once
// from the retail string "Toggle" and 2 (constructor at 0x10cd4790), and passes this object,
// Other's word at 0x2b4 and the name to the method at 0x1099a240 of entry Index of the pointer
// table at 0x3fc of the object at 0x2c8. The class, method, member, local and parameter names
// are invented; the offsets, the string and the bytes are the binary's.

class UnkType_10c6ae10_Name
{
public:
    UnkType_10c6ae10_Name(const unsigned short* Text, int Flags);

    int unk_0;
};

class UnkType_10c6ae10;

class UnkType_10c6ae10_Other
{
public:
    unsigned char unk_0[0x2b4];
    int unk_2b4;
};

class UnkType_10c6ae10_Switch
{
public:
    void Unk_1099a240(UnkType_10c6ae10* Owner, int Value, UnkType_10c6ae10_Name Name);
};

class UnkType_10c6ae10_Group
{
public:
    unsigned char unk_0[0x3fc];
    UnkType_10c6ae10_Switch** unk_3fc;
};

class UnkType_10c6ae10
{
public:
    void Unk_1099f3f0(UnkType_10c6ae10_Other* Other, unsigned char Index);
    void Unk_10c6ae10(UnkType_10c6ae10_Other* Other, unsigned char Index);

    unsigned char unk_0[0x2c8];
    UnkType_10c6ae10_Group* unk_2c8;
};

// UnkType_10c6ae10::Unk_10c6ae10
void UnkType_10c6ae10::Unk_10c6ae10(UnkType_10c6ae10_Other* Other, unsigned char Index)
{
    Unk_1099f3f0(Other, Index);
    static UnkType_10c6ae10_Name ToggleName(L"Toggle", 2);
    unk_2c8->unk_3fc[Index]->Unk_1099a240(this, Other->unk_2b4, ToggleName);
}
