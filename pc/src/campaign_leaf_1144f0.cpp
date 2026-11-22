// campaign_leaf_1144f0.cpp -- method at VA 0x10a144f0: assigns the wide string "Combine material",
// in double quotes, to the object its argument refers to through the method at VA 0x10907a00, and
// returns true. It does not use this. The class and method names are invented; the string and the
// addresses are the binary's.

class UnkType_10a144f0_10907a00
{
public:
    void Unk_10907a00(const unsigned short* Text);
};

class UnkType_10a144f0
{
public:
    bool Unk_10a144f0(UnkType_10a144f0_10907a00& Out);
};

// UnkType_10a144f0::Unk_10a144f0
bool UnkType_10a144f0::Unk_10a144f0(UnkType_10a144f0_10907a00& Out)
{
    Out.Unk_10907a00(L"\"Combine material\"");
    return true;
}
