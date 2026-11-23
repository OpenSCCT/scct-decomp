// campaign_leaf_092290.cpp -- method at VA 0x10992290 assigning a zero-terminated wide string to a
// dynamic array of wide characters (data pointer at 0x00, count at 0x04, capacity at 0x08): unless
// the string is the array's own data, sets count and capacity to its length plus one (the function
// at VA 0x10ccadc0) or to 0 for an empty string, reallocates the data through virtual slot 1 of the
// allocator global at VA 0x111c88a0 with the tag "FArray::_WORD" and copies the characters; returns
// the array. guess: the engine's FString assignment from a character string. The class, member and
// method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

int Unk_10ccadc0(const unsigned short* String);

extern "C" void* __cdecl memcpy(void* Dest, const void* Source, unsigned int Count);

class UnkType_10992290_String
{
public:
    UnkType_10992290_String& Unk_10992290(const unsigned short* Other);

    void Realloc()
    {
        unk_00 = (unsigned short*)GUnk_111c88a0->Realloc(
            unk_00, unk_08 * sizeof(unsigned short), L"FArray::_WORD");
    }

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10992290_String::Unk_10992290
UnkType_10992290_String& UnkType_10992290_String::Unk_10992290(const unsigned short* Other)
{
    if ( unk_00 != Other )
    {
        unk_04 = unk_08 = *Other ? Unk_10ccadc0(Other) + 1 : 0;
        Realloc();
        if ( unk_04 )
        {
            memcpy(unk_00, Other, unk_04 * sizeof(unsigned short));
        }
    }
    return *this;
}
