// campaign_leaf_1d20b0.cpp -- function at VA 0x10ad20b0 with no this pointer. It serializes an
// object through an archive: the strings at 0x00, 0x0c, 0x1c and 0x34 through the function at VA
// 0x10cce480, the member at 0x28 through the function at VA 0x109f32a0, then the words at 0x18 and
// 0x40 through the archive's slot 1 with 4 bytes each. It returns the archive. The class, function
// and member names are invented.

class UnkType_10ad20b0_Archive
{
public:
    virtual ~UnkType_10ad20b0_Archive();
    virtual void Serialize(void* Data, int Length);
};

// operator<<
inline UnkType_10ad20b0_Archive& operator<<(UnkType_10ad20b0_Archive& Ar, int& Value)
{
    Ar.Serialize(&Value, 4);
    return Ar;
}

struct UnkType_10ad20b0_String
{
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

struct UnkType_10ad20b0_Other
{
    int unk_0;
    int unk_4;
    int unk_8;
};

UnkType_10ad20b0_Archive& operator<<(UnkType_10ad20b0_Archive& Ar, UnkType_10ad20b0_String& Value);
UnkType_10ad20b0_Archive& operator<<(UnkType_10ad20b0_Archive& Ar, UnkType_10ad20b0_Other& Value);

struct UnkType_10ad20b0
{
    UnkType_10ad20b0_String unk_00;
    UnkType_10ad20b0_String unk_0c;
    int unk_18;
    UnkType_10ad20b0_String unk_1c;
    UnkType_10ad20b0_Other unk_28;
    UnkType_10ad20b0_String unk_34;
    int unk_40;
};

// Unk_10ad20b0
UnkType_10ad20b0_Archive& Unk_10ad20b0(UnkType_10ad20b0_Archive& Ar, UnkType_10ad20b0& Value)
{
    Ar << Value.unk_00 << Value.unk_0c << Value.unk_1c << Value.unk_34 << Value.unk_28
       << Value.unk_18 << Value.unk_40;
    return Ar;
}
