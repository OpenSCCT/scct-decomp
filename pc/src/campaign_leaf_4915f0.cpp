// campaign_leaf_4915f0.cpp -- thiscall at VA 0x10d915f0: passes the dword its argument refers to
// to the method at VA 0x10d91210 on the same object, and returns the object. All names are
// invented.

class UnkType_10d915f0
{
public:
    void Unk_10d91210(int Value);
    UnkType_10d915f0& Unk_10d915f0(const int& Value);
};

// UnkType_10d915f0::Unk_10d915f0
UnkType_10d915f0& UnkType_10d915f0::Unk_10d915f0(const int& Value)
{
    Unk_10d91210(Value);
    return *this;
}
