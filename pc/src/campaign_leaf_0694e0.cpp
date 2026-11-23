// campaign_leaf_0694e0.cpp -- free function at VA 0x109694e0: serialises the object its second
// argument refers to through the archive its first argument refers to: the 12-byte members at 0x00
// and 0x0c through the free function at VA 0x10969550, then the five values from 0x18 to 0x28 (four
// bytes each) through the archive method at VA 0x10967df0; returns the archive. The class, member
// and function names are invented; the offsets, the sizes and the addresses are the binary's.

class UnkType_109694e0_Archive
{
public:
    void Unk_10967df0(void* Data, int Size);
};

class UnkType_109694e0_Vector
{
public:
    float X;
    float Y;
    float Z;
};

UnkType_109694e0_Archive& Unk_10969550(UnkType_109694e0_Archive& Archive,
                                       UnkType_109694e0_Vector& Value);

class UnkType_109694e0
{
public:
    UnkType_109694e0_Vector unk_00;
    UnkType_109694e0_Vector unk_0c;
    float unk_18;
    float unk_1c;
    float unk_20;
    float unk_24;
    float unk_28;
};

// Unk_109694e0
UnkType_109694e0_Archive& Unk_109694e0(UnkType_109694e0_Archive& Archive, UnkType_109694e0& Value)
{
    UnkType_109694e0_Archive& Out = Unk_10969550(Unk_10969550(Archive, Value.unk_00), Value.unk_0c);
    Out.Unk_10967df0(&Value.unk_18, 4);
    Out.Unk_10967df0(&Value.unk_1c, 4);
    Out.Unk_10967df0(&Value.unk_20, 4);
    Out.Unk_10967df0(&Value.unk_24, 4);
    Out.Unk_10967df0(&Value.unk_28, 4);
    return Out;
}
