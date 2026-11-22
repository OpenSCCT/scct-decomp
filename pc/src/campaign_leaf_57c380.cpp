// campaign_leaf_57c380.cpp -- thiscall method at VA 0x10e7c380: when the count at 0x20 of the
// 12-byte member at 0x1c is positive, calls the method at VA 0x10e53150 on the object it is given
// with 0 and the address of that member. The class and method names are invented.

struct UnkType_10e7c380_1c
{
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10e53150
{
public:
    void Unk_10e53150(int Value, UnkType_10e7c380_1c* List);
};

class UnkType_10e7c380
{
public:
    void Unk_10e7c380(UnkType_10e53150* Target);

private:
    int unk_00[7];
    UnkType_10e7c380_1c unk_1c;
};

// UnkType_10e7c380::Unk_10e7c380
void UnkType_10e7c380::Unk_10e7c380(UnkType_10e53150* Target)
{
    if ( unk_1c.unk_04 > 0 )
    {
        Target->Unk_10e53150(0, &unk_1c);
    }
}
