// campaign_leaf_069550.cpp -- free function at VA 0x10969550: serialises the three floats of the
// 12-byte value its second argument refers to, four bytes each, through the archive method at VA
// 0x10967df0; returns the archive. The class, member and function names are invented; the offsets,
// the size and the address are the binary's.

class UnkType_10969550_Archive
{
public:
    void Unk_10967df0(void* Data, int Size);
};

class UnkType_10969550_Vector
{
public:
    float X;
    float Y;
    float Z;
};

// Unk_10969550
UnkType_10969550_Archive& Unk_10969550(UnkType_10969550_Archive& Archive,
                                       UnkType_10969550_Vector& Value)
{
    Archive.Unk_10967df0(&Value.X, 4);
    Archive.Unk_10967df0(&Value.Y, 4);
    Archive.Unk_10967df0(&Value.Z, 4);
    return Archive;
}
