// campaign_leaf_072710.cpp -- method at VA 0x10972710: passes its archive argument to the method at
// VA 0x10cd9030, the member at 0x28 to the free function at VA 0x109724f0, and then the four values
// from 0x44 to 0x50 (four bytes each) to virtual slot 1 (vtable offset 0x04) of the archive that
// function returns. The class, member and method names are invented; the offsets, the slot and the
// addresses are the binary's.

class UnkType_109724f0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);
};

class UnkType_109724f0_Plane
{
public:
    float X;
    float Y;
    float Z;
    float W;
};

inline UnkType_109724f0_Archive& operator<<(UnkType_109724f0_Archive& Archive, float& Value)
{
    Archive.VirtualSlot1(&Value, 4);
    return Archive;
}

inline UnkType_109724f0_Archive& operator<<(UnkType_109724f0_Archive& Archive,
                                            UnkType_109724f0_Plane& Plane)
{
    return Archive << Plane.X << Plane.Y << Plane.Z << Plane.W;
}

class UnkType_10972710_28
{
public:
    int unk_00;
};

UnkType_109724f0_Archive& Unk_109724f0(UnkType_109724f0_Archive& Archive,
                                       UnkType_10972710_28& Value);

class UnkType_10972710
{
public:
    void Unk_10972710(UnkType_109724f0_Archive& Archive);
    void Unk_10cd9030(UnkType_109724f0_Archive& Archive);

private:
    unsigned char unk_00[0x28];
    UnkType_10972710_28 unk_28;
    unsigned char unk_2c[0x44 - 0x2c];
    UnkType_109724f0_Plane unk_44;
};

// UnkType_10972710::Unk_10972710
void UnkType_10972710::Unk_10972710(UnkType_109724f0_Archive& Archive)
{
    Unk_10cd9030(Archive);
    Unk_109724f0(Archive, unk_28) << unk_44;
}
