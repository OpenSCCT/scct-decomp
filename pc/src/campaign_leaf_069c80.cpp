// campaign_leaf_069c80.cpp -- free function at VA 0x10969c80: serialises the value its second
// argument refers to, four bytes at a time through the archive method at VA 0x10967df0: the floats
// at 0x00-0x08, the 12-byte vector at 0x0c and the floats at 0x18-0x24; returns the archive. The
// class, member and function names are invented; the offsets, the sizes and the address are the
// binary's.

class UnkType_069c80_Archive
{
public:
    void Unk_10967df0(void* Data, int Size);
};

class UnkType_069c80_Vector
{
public:
    float X;
    float Y;
    float Z;
};

inline UnkType_069c80_Archive& operator<<(UnkType_069c80_Archive& Archive,
                                            UnkType_069c80_Vector& Value)
{
    Archive.Unk_10967df0(&Value.X, 4);
    Archive.Unk_10967df0(&Value.Y, 4);
    Archive.Unk_10967df0(&Value.Z, 4);
    return Archive;
}

class UnkType_10969c80_Value
{
public:
    float unk_00;
    float unk_04;
    float unk_08;
    UnkType_069c80_Vector unk_0c;
    float unk_18;
    float unk_1c;
    float unk_20;
    float unk_24;
};

// Unk_10969c80
UnkType_069c80_Archive& Unk_10969c80(UnkType_069c80_Archive& Archive,
                                       UnkType_10969c80_Value& Value)
{
    Archive.Unk_10967df0(&Value.unk_00, 4);
    Archive.Unk_10967df0(&Value.unk_04, 4);
    Archive.Unk_10967df0(&Value.unk_08, 4);
    Archive << Value.unk_0c;
    Archive.Unk_10967df0(&Value.unk_18, 4);
    Archive.Unk_10967df0(&Value.unk_1c, 4);
    Archive.Unk_10967df0(&Value.unk_20, 4);
    Archive.Unk_10967df0(&Value.unk_24, 4);
    return Archive;
}
