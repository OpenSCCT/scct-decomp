// campaign_leaf_023bf0.cpp -- method at VA 0x10923bf0: copies the object its argument refers to
// into this one: passes it to the method at VA 0x10923c20, copies the value at 0x10, calls the
// method at VA 0x10922a80, then copies the values at 0x14 and 0x18; returns this object. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

class UnkType_10923bf0
{
public:
    UnkType_10923bf0& Unk_10923bf0(const UnkType_10923bf0& Other);
    void Unk_10923c20(const UnkType_10923bf0& Other);
    void Unk_10922a80();

private:
    unsigned char unk_00[0x10];
    int unk_10;
    int unk_14;
    int unk_18;
};

// UnkType_10923bf0::Unk_10923bf0
UnkType_10923bf0& UnkType_10923bf0::Unk_10923bf0(const UnkType_10923bf0& Other)
{
    Unk_10923c20(Other);
    unk_10 = Other.unk_10;
    Unk_10922a80();
    unk_14 = Other.unk_14;
    unk_18 = Other.unk_18;
    return *this;
}
