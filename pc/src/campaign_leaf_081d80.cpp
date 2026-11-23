// campaign_leaf_081d80.cpp -- method at VA 0x10981d80: searches the array of 12-byte vectors at
// 0x00 (count at 0x04) for one equal to the vector its argument refers to and returns its index;
// when none is equal, returns the method at VA 0x10929980 called with the vector. The class, member
// and method names are invented; the offsets and the address are the binary's.

class UnkType_10981d80_Vector
{
public:
    float X;
    float Y;
    float Z;
};

class UnkType_10981d80
{
public:
    int Unk_10981d80(const UnkType_10981d80_Vector& Value);
    int Unk_10929980(const UnkType_10981d80_Vector& Value);

private:
    UnkType_10981d80_Vector* unk_00;
    int unk_04;
};

// UnkType_10981d80::Unk_10981d80
int UnkType_10981d80::Unk_10981d80(const UnkType_10981d80_Vector& Value)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        if ( unk_00[i].X == Value.X && unk_00[i].Y == Value.Y && unk_00[i].Z == Value.Z )
        {
            return i;
        }
    }
    return Unk_10929980(Value);
}
