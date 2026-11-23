// campaign_leaf_344140.cpp -- one function at file offset 0x344140, preferred VA 0x10c44140. When
// the object at 0x444 is set it copies that object's vector at 0x134, passes the copy's first
// component with First and Third to the method at 0x10c43d60, then its second component with the
// negated Second and Third, and passes the copy to the object's method at 0x10990480. The class,
// method, member, local and parameter names are invented; the offsets and the bytes are the
// binary's.

class UnkType_10c44140_Vector
{
public:
    float unk_0;
    float unk_4;
    float unk_8;
};

class UnkType_10c44140_Target
{
public:
    void Unk_10990480(const UnkType_10c44140_Vector& Vector);

    unsigned char unk_0[0x134];
    UnkType_10c44140_Vector unk_134;
};

class UnkType_10c44140
{
public:
    void Unk_10c43d60(float& Value, const float& Amount, int Mode);
    void Unk_10c44140(const float& First, const float& Second, int Third);

    unsigned char unk_0[0x444];
    UnkType_10c44140_Target* unk_444;
};

// UnkType_10c44140::Unk_10c44140
void UnkType_10c44140::Unk_10c44140(const float& First, const float& Second, int Third)
{
    UnkType_10c44140_Target* Target = unk_444;
    UnkType_10c44140_Vector Vector;

    if ( Target != 0 )
    {
        Vector = Target->unk_134;
        Unk_10c43d60(Vector.unk_0, First, Third);
        Unk_10c43d60(Vector.unk_4, -Second, Third);
        Target->Unk_10990480(Vector);
    }
}
