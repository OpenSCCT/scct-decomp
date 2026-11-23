// campaign_leaf_6fe290.cpp -- cdecl function at VA 0x10ffe290 taking a pointer: when it is not
// null, constructs an object there in place: the base constructor at VA 0x10ffe2d0 runs, then three
// groups of four values at 0x10-0x3c are cleared, last member of each group first. The object has
// the shape the constructor at VA 0x10ffe220 builds. The type and function names are invented; the
// offsets and addresses are the binary's.

inline void* __cdecl operator new(unsigned int Size, void* Where) throw()
{
    return Where;
}

class UnkType_10ffe290_Base
{
public:
    UnkType_10ffe290_Base();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

class UnkType_10ffe290 : public UnkType_10ffe290_Base
{
public:
    UnkType_10ffe290()
    {
        unk_10 = unk_14 = unk_18 = unk_1c = 0;
        unk_20 = unk_24 = unk_28 = unk_2c = 0;
        unk_30 = unk_34 = unk_38 = unk_3c = 0;
    }

private:
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
};

// Unk_10ffe290
void __cdecl Unk_10ffe290(void* Memory)
{
    new(Memory) UnkType_10ffe290;
}
