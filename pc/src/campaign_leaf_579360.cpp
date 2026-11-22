// campaign_leaf_579360.cpp -- one function at file offset 0x579360, preferred VA 0x10e79360. The
// constructor zeroes three rows of four floats, sets their diagonal elements to 1 and then zeroes
// a fourth row of the derived class. The class, structure and member names are invented; the
// offset and the bytes are the binary's.

struct UnkType_10e79360_Row
{
    float X;
    float Y;
    float Z;
    float W;

    UnkType_10e79360_Row()
    {
        X = Y = Z = W = 0.0f;
    }

    float& Component(int Index)
    {
        return ( &X )[Index];
    }
};

class UnkType_10e79360_Base
{
public:
    UnkType_10e79360_Row unk_0;
    UnkType_10e79360_Row unk_10;
    UnkType_10e79360_Row unk_20;

    UnkType_10e79360_Base()
    {
        unk_0.Component(0) = 1.0f;
        unk_10.Component(1) = 1.0f;
        unk_20.Component(2) = 1.0f;
    }
};

class UnkType_10e79360 : public UnkType_10e79360_Base
{
public:
    UnkType_10e79360_Row unk_30;

    UnkType_10e79360();
};

// UnkType_10e79360::UnkType_10e79360
UnkType_10e79360::UnkType_10e79360()
{
}
