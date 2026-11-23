// campaign_leaf_18afc0.cpp -- one function at file offset 0x18afc0, preferred VA 0x10a8afc0.
// When the object at offset 0x2b4 exists it copies its last argument into bit field 9 of that
// object's word at offset 0x2c0; then it passes all its arguments, the vector by value, to its own
// method at VA 0x10a8ade0.
// The class, method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10a8afc0_Vector
{
    float X;
    float Y;
    float Z;
};

class UnkType_10a8afc0_Owner
{
public:
    unsigned char unk_0[0x2c0];
    unsigned int unk_2c0_0 : 9;
    unsigned int unk_2c0_9 : 1;
};

class UnkType_10a8afc0
{
public:
    unsigned char unk_0[0x2b4];
    UnkType_10a8afc0_Owner* unk_2b4;

    void Unk_10a8ade0(int First, int Second, UnkType_10a8afc0_Vector Vector, unsigned int Flag);
    void Unk_10a8afc0(int First, int Second, UnkType_10a8afc0_Vector Vector, unsigned int Flag);
};

// UnkType_10a8afc0::Unk_10a8afc0
void UnkType_10a8afc0::Unk_10a8afc0(int First, int Second, UnkType_10a8afc0_Vector Vector,
    unsigned int Flag)
{
    if ( unk_2b4 )
    {
        unk_2b4->unk_2c0_9 = Flag;
    }
    Unk_10a8ade0(First, Second, Vector, Flag);
}
