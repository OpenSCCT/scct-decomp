// campaign_leaf_08d250.cpp -- free function at VA 0x1098d250: serialises the object its second
// argument refers to: the member at 0x00 through the free function at VA 0x10cce480, the member at
// 0x0c through the free function at VA 0x109724f0 and the members at 0x28 and 0x34 through the free
// function at VA 0x1098c9c0, each on the archive the previous one returns; returns the last
// archive. The class, member and function names are invented; the offsets and the addresses are the
// binary's.

class UnkType_1098d250_Archive;

class UnkType_1098d250_00
{
public:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1098d250_0c
{
public:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1098d250_28
{
public:
    void* unk_00;
    int unk_04;
    int unk_08;
};

UnkType_1098d250_Archive& Unk_10cce480(UnkType_1098d250_Archive& Archive,
                                       UnkType_1098d250_00& Value);
UnkType_1098d250_Archive& Unk_109724f0(UnkType_1098d250_Archive& Archive,
                                       UnkType_1098d250_0c& Value);
UnkType_1098d250_Archive& Unk_1098c9c0(UnkType_1098d250_Archive& Archive,
                                       UnkType_1098d250_28& Value);

class UnkType_1098d250
{
public:
    UnkType_1098d250_00 unk_00;
    UnkType_1098d250_0c unk_0c;
    unsigned char unk_18[0x28 - 0x18];
    UnkType_1098d250_28 unk_28;
    UnkType_1098d250_28 unk_34;
};

// Unk_1098d250
UnkType_1098d250_Archive& Unk_1098d250(UnkType_1098d250_Archive& Archive, UnkType_1098d250& Value)
{
    return Unk_1098c9c0(Unk_1098c9c0(Unk_109724f0(Unk_10cce480(Archive, Value.unk_00),
                                                  Value.unk_0c),
                                     Value.unk_28),
                        Value.unk_34);
}
