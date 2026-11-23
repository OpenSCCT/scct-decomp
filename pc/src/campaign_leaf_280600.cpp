// campaign_leaf_280600.cpp -- method at VA 0x10b80600: makes two function-local static names on
// first use (L"BF L Eye" and L"BF R Eye", through the name constructor at VA 0x10cd4790 with 2);
// when the object at 0x184 is set, its chain of pointers (from 0x24, following 0x28) reaches the
// object the global at VA 0x111f8ae8 holds (filled in first from L"Engine" by the function at VA
// 0x10a031a0 followed by the function at VA 0x109d0630), and the object at 0x64 is set, passes each
// name with the three words made of the word at 0x93c, 0 and the word at 0x940, then 0, 1.0, 1.0,
// 1.0 and 0, to that object's method at VA 0x109d16e0. The class, member and method names are
// invented; the offsets, the strings, the constants and the addresses are the binary's.

#include "campaign_global_111f8ae8.h"

UnkType_111f8ae8* Unk_10a031a0(const unsigned short* Package);
void Unk_109d0630();

class UnkType_10b80600_Name
{
public:
    UnkType_10b80600_Name(const unsigned short* Text, int FindType);

private:
    int unk_00;
};

class UnkType_10b80600_Rotator
{
public:
    UnkType_10b80600_Rotator(int First, int Second, int Third)
        : unk_00(First), unk_04(Second), unk_08(Third)
    {
    }

    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b80600_184
{
public:
    int UnkInheritsFrom(UnkType_111f8ae8* Target)
    {
        for ( UnkType_111f8ae8* Link = unk_24; Link; Link = Link->unk_28 )
        {
            if ( Link == Target )
            {
                return 1;
            }
        }
        return Target == 0;
    }

    unsigned char unk_00[0x24];
    UnkType_111f8ae8* unk_24;
};

class UnkType_10b80600_64
{
public:
    void Unk_109d16e0(UnkType_10b80600_Name Name, UnkType_10b80600_Rotator Rotation, int Space,
                      float First, float Second, float Third, int Last);
};

class UnkType_10b80600
{
public:
    void Unk_10b80600();

    static UnkType_111f8ae8* UnkLazyTarget()
    {
        if ( !GUnk_111f8ae8 )
        {
            GUnk_111f8ae8 = Unk_10a031a0(L"Engine");
            Unk_109d0630();
        }
        return GUnk_111f8ae8;
    }

private:
    unsigned char unk_00[0x64];
    UnkType_10b80600_64* unk_64;
    unsigned char unk_68[0x184 - 0x68];
    UnkType_10b80600_184* unk_184;
    unsigned char unk_188[0x93c - 0x188];
    int unk_93c;
    int unk_940;
};

// UnkType_10b80600::Unk_10b80600
void UnkType_10b80600::Unk_10b80600()
{
    static UnkType_10b80600_Name LeftEye(L"BF L Eye", 2);
    static UnkType_10b80600_Name RightEye(L"BF R Eye", 2);
    if ( unk_184 && unk_184->UnkInheritsFrom(UnkLazyTarget()) && unk_64 )
    {
        unk_64->Unk_109d16e0(LeftEye, UnkType_10b80600_Rotator(unk_93c, 0, unk_940), 0,
                             1.0f, 1.0f, 1.0f, 0);
        unk_64->Unk_109d16e0(RightEye, UnkType_10b80600_Rotator(unk_93c, 0, unk_940), 0,
                             1.0f, 1.0f, 1.0f, 0);
    }
}
