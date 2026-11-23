// campaign_leaf_07a640.cpp -- method at VA 0x1097a640: passes its archive argument to the method at
// VA 0x10cd9030, then serialises the member at 0x28 through the free function at VA 0x10978490. The
// class, member and function names are invented; the offsets and the addresses are the binary's.

class UnkType_1097a640_Archive
{
};

class UnkType_1097a640_28
{
public:
    void* unk_00;
    int unk_04;
    int unk_08;
};

UnkType_1097a640_Archive& Unk_10978490(UnkType_1097a640_Archive& Archive,
                                       UnkType_1097a640_28& Value);

class UnkType_1097a640
{
public:
    void Unk_1097a640(UnkType_1097a640_Archive& Archive);
    void Unk_10cd9030(UnkType_1097a640_Archive& Archive);

private:
    unsigned char unk_00[0x28];
    UnkType_1097a640_28 unk_28;
};

// UnkType_1097a640::Unk_1097a640
void UnkType_1097a640::Unk_1097a640(UnkType_1097a640_Archive& Archive)
{
    Unk_10cd9030(Archive);
    Unk_10978490(Archive, unk_28);
}
