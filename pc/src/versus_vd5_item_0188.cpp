// RVA 0xe1e50: operator= of an unidentified struct (neutral name) holding a
// TArray<BYTE> at 0x40 and two WORD fields at 0x4c/0x4e. LTCG: this in EBX.
typedef int INT;
typedef unsigned short WORD;
typedef unsigned char BYTE;

void __cdecl appMemcpy(void *Dest, const void *Src, INT Count);

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Empty(INT ElementSize, INT Slack);
};

class FByteArray : public FArray
{
public:
    FByteArray &operator=(const FByteArray &Other)
    {
        if (this != &Other) {
            Empty(sizeof(BYTE), Other.ArrayNum);
            appMemcpy(Data, Other.Data, Other.ArrayNum * sizeof(BYTE));
            ArrayNum = Other.ArrayNum;
        }
        return *this;
    }
};

class UnnamedClass_e1e50
{
public:
    BYTE Pad[0x40];
    FByteArray Bytes;
    WORD A;
    WORD B;
    __declspec(noinline) UnnamedClass_e1e50 &Assign(const UnnamedClass_e1e50 &Other);
};

UnnamedClass_e1e50 &UnnamedClass_e1e50::Assign(const UnnamedClass_e1e50 &Other)
{
    Bytes = Other.Bytes;
    A = Other.A;
    B = Other.B;
    return *this;
}

// Scaffolding for the link, not part of the unit.
void Driver_e1e50(UnnamedClass_e1e50 *D, const UnnamedClass_e1e50 *S, UnnamedClass_e1e50 *E, const UnnamedClass_e1e50 *F) { D->Assign(*S); E->Assign(*F); D->Assign(*F); E->Assign(*S); }
