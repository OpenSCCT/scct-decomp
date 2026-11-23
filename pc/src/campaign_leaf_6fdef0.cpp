// campaign_leaf_6fdef0.cpp -- cdecl function at VA 0x10ffdef0 taking a pointer: when it is not null,
// constructs an object there in place: the base constructor at VA 0x10e10d90 runs, then 0x04 is set to 0, 0x08 is set to 0, 0x0c is set to 0x80000000.
// It reads like a template's construct-in-place helper. The type and function names are invented;
// the offsets and addresses are the binary's.

inline void* __cdecl operator new(unsigned int Size, void* Where) throw()
{
    return Where;
}

class UnkType_10ffdef0_Base
{
public:
    UnkType_10ffdef0_Base();

private:
    int unk_00;
};

class UnkType_10ffdef0 : public UnkType_10ffdef0_Base
{
public:
    UnkType_10ffdef0()
        : unk_04(0)
        , unk_08(0)
        , unk_0c(0x80000000)
    {
    }

private:
    int unk_04;
    int unk_08;
    unsigned int unk_0c;
};

// Unk_10ffdef0
void __cdecl Unk_10ffdef0(void* Memory)
{
    new(Memory) UnkType_10ffdef0;
}
