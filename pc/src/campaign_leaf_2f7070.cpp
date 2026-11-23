// campaign_leaf_2f7070.cpp -- method at VA 0x10bf7070 taking two pointers to words: passes them to
// the method at VA 0x10bf80a0; then, through the object at 0x554, calls its method at VA 0x10990270
// with its own three floats at 0x404 when the first word is 1 and the second is zero, or with a
// copy of them whose first float is raised by 7.3 when the first word is 2 and the second is
// nonzero. The class, member and method names are invented; the offsets and the addresses are the
// binary's.

class UnkType_10bf7070_Vector
{
public:
    UnkType_10bf7070_Vector()
    {
    }

    UnkType_10bf7070_Vector(float First, float Second, float Third)
        : unk_00(First), unk_04(Second), unk_08(Third)
    {
    }

    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_10bf7070_554
{
public:
    void Unk_10990270(const UnkType_10bf7070_Vector& Location);

    unsigned char unk_00[0x404];
    UnkType_10bf7070_Vector unk_404;
};

class UnkType_10bf7070
{
public:
    void Unk_10bf7070(int* Kind, int* Value);
    void Unk_10bf80a0(int* Kind, int* Value);

private:
    unsigned char unk_00[0x554];
    UnkType_10bf7070_554* unk_554;
};

// UnkType_10bf7070::Unk_10bf7070
void UnkType_10bf7070::Unk_10bf7070(int* Kind, int* Value)
{
    Unk_10bf80a0(Kind, Value);
    switch ( *Kind )
    {
    case 1:
        if ( !*Value )
        {
            unk_554->Unk_10990270(unk_554->unk_404);
        }
        break;
    case 2:
        if ( *Value )
        {
            unk_554->Unk_10990270(UnkType_10bf7070_Vector(unk_554->unk_404.unk_00 + 7.3f,
                                                          unk_554->unk_404.unk_04,
                                                          unk_554->unk_404.unk_08));
        }
        break;
    }
}
