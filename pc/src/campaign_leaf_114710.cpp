// campaign_leaf_114710.cpp -- method at VA 0x10a14710: assigns the wide string "Depth material", in
// double quotes, to the object its argument refers to through the method at VA 0x10907a00, and
// returns true. It does not use this. The class and method names are invented; the string and the
// addresses are the binary's.

class UnkType_10907a00
{
public:
    void Unk_10907a00(const unsigned short* Text);
};

class UnkType_10a14710
{
public:
    bool Unk_10a14710(UnkType_10907a00& Out);
};

// UnkType_10a14710::Unk_10a14710
bool UnkType_10a14710::Unk_10a14710(UnkType_10907a00& Out)
{
    Out.Unk_10907a00(L"\"Depth material\"");
    return true;
}
