// campaign_leaf_6fe020.cpp -- cdecl function at VA 0x10ffe020 taking a pointer: when it is not null,
// constructs an object there in place: the base constructor at VA 0x10e10d90 runs, then 0x04 is set to 0.
// It reads like a template's construct-in-place helper. The type and function names are invented;
// the offsets and addresses are the binary's.

inline void* __cdecl operator new(unsigned int Size, void* Where) throw()
{
    return Where;
}

class UnkType_10ffe020_Base
{
public:
    UnkType_10ffe020_Base();

private:
    int unk_00;
};

class UnkType_10ffe020 : public UnkType_10ffe020_Base
{
public:
    UnkType_10ffe020()
        : unk_04(0)
    {
    }

private:
    int unk_04;
};

// Unk_10ffe020
void __cdecl Unk_10ffe020(void* Memory)
{
    new(Memory) UnkType_10ffe020;
}
