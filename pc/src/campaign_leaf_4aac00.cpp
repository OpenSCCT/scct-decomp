// campaign_leaf_4aac00.cpp -- one function at file offset 0x4aac00, preferred VA 0x10daac00.
// The copy constructor runs the base constructor at 0x10d8b2d0 and copies the member at offset 4
// of Other with the constructor at 0x10daa830. The class, member and parameter names are invented;
// the offset and the bytes are the binary's.

class UnkType_10daac00_Base
{
public:
    int unk_0;

    UnkType_10daac00_Base();
};

class UnkType_10daac00_Member
{
public:
    int unk_0;

    UnkType_10daac00_Member(const UnkType_10daac00_Member& Other);
};

class UnkType_10daac00 : public UnkType_10daac00_Base
{
public:
    UnkType_10daac00_Member unk_4;

    UnkType_10daac00(const UnkType_10daac00& Other);
};

// UnkType_10daac00::UnkType_10daac00
UnkType_10daac00::UnkType_10daac00(const UnkType_10daac00& Other)
    : unk_4(Other.unk_4)
{
}
