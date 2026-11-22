// campaign_leaf_560050.cpp -- one function at file offset 0x560050, preferred VA 0x10e60050.
// It copies six 16-byte rows of Value into the object in a different order (rows 1-6 of Value go
// to rows 2, 5, 3, 6, 4 and 7 of the object), then the six ints after them. The class, structure,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10e60050_Row
{
    float X;
    float Y;
    float Z;
    float W;

    UnkType_10e60050_Row& operator=(const UnkType_10e60050_Row& Other)
    {
        X = Other.X;
        Y = Other.Y;
        Z = Other.Z;
        W = Other.W;
        return *this;
    }
};

struct UnkType_10e60050_Value
{
    UnkType_10e60050_Row unk_0;
    UnkType_10e60050_Row unk_10;
    UnkType_10e60050_Row unk_20;
    UnkType_10e60050_Row unk_30;
    UnkType_10e60050_Row unk_40;
    UnkType_10e60050_Row unk_50;
    UnkType_10e60050_Row unk_60;
    int unk_70;
    int unk_74;
    int unk_78;
    int unk_7c;
    int unk_80;
    int unk_84;
};

class UnkType_10e60050
{
public:
    UnkType_10e60050_Row unk_0;
    UnkType_10e60050_Row unk_10;
    UnkType_10e60050_Row unk_20;
    UnkType_10e60050_Row unk_30;
    UnkType_10e60050_Row unk_40;
    UnkType_10e60050_Row unk_50;
    UnkType_10e60050_Row unk_60;
    UnkType_10e60050_Row unk_70;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8c;
    int unk_90;
    int unk_94;

    void Unk_10e60050(const UnkType_10e60050_Value& Value);
};

// UnkType_10e60050::Unk_10e60050
void UnkType_10e60050::Unk_10e60050(const UnkType_10e60050_Value& Value)
{
    unk_20 = Value.unk_10;
    unk_50 = Value.unk_20;
    unk_40 = Value.unk_50;
    unk_70 = Value.unk_60;
    unk_30 = Value.unk_30;
    unk_60 = Value.unk_40;
    unk_80 = Value.unk_70;
    unk_84 = Value.unk_74;
    unk_88 = Value.unk_78;
    unk_8c = Value.unk_7c;
    unk_90 = Value.unk_80;
    unk_94 = Value.unk_84;
}
