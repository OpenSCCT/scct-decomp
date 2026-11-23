// campaign_leaf_3d8f20.cpp -- one function at file offset 0x3d8f20, preferred VA 0x10cd8f20. It
// writes this object's dotted path up to Stop into Out (a buffer from the function at 0x10ccb530
// when Out is null) and returns Out: the retail "None" when this object is Stop; otherwise the
// path of the object at 0x18 (unless that is Stop) and ".", followed by the name from the method
// at 0x10907eb0, appended through the function at 0x10ccae10. The class, function, method,
// member and parameter names are invented; the offsets, the strings and the bytes are the
// binary's.

unsigned short* Unk_10ccb530();
unsigned short* Unk_10ccae10(unsigned short* Out, const unsigned short* Text);
int Unk_10ccb0d0(unsigned short* Out, const unsigned short* Format, ...);

class UnkType_10cd8f20
{
public:
    const unsigned short* Unk_10907eb0() const;
    unsigned short* Unk_10cd8f20(const UnkType_10cd8f20* Stop, unsigned short* Out) const;

    unsigned char unk_0[0x18];
    UnkType_10cd8f20* unk_18;
};

// UnkType_10cd8f20::Unk_10cd8f20
unsigned short* UnkType_10cd8f20::Unk_10cd8f20(const UnkType_10cd8f20* Stop,
                                               unsigned short* Out) const
{
    if ( Out == 0 )
    {
        Out = Unk_10ccb530();
    }
    if ( this != Stop )
    {
        *Out = 0;
        if ( unk_18 != Stop )
        {
            unk_18->Unk_10cd8f20(Stop, Out);
            Unk_10ccae10(Out, L".");
        }
        Unk_10ccae10(Out, Unk_10907eb0());
    }
    else
    {
        Unk_10ccb0d0(Out, L"None");
    }
    return Out;
}
