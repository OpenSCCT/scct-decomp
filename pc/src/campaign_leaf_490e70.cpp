// campaign_leaf_490e70.cpp -- function at VA 0x10d90e70. It copies a wide string of the given
// length into the destination buffer and terminates it, returning a result built (0x10dab010)
// from 0x10001; with no destination it returns 0x8001000a, and when the string and its terminator
// do not fit the capacity, 0x8001000f. The class, function and parameter names are invented.

unsigned short* __cdecl wcsncpy(unsigned short* Dest, const unsigned short* Source,
                                unsigned int Count);

class UnkType_10d90e70_Result
{
public:
    UnkType_10d90e70_Result(const unsigned int& Code);

private:
    unsigned int unk_0;
};

// Unk_10d90e70
UnkType_10d90e70_Result Unk_10d90e70(unsigned short* Dest, unsigned int Capacity,
                                     const unsigned short* Source, unsigned int Length)
{
    if ( Dest == 0 )
    {
        return UnkType_10d90e70_Result(0x8001000a);
    }
    if ( Length + 1 > Capacity )
    {
        return UnkType_10d90e70_Result(0x8001000f);
    }
    wcsncpy(Dest, Source, Length);
    Dest[Length] = 0;
    return UnkType_10d90e70_Result(0x10001);
}
