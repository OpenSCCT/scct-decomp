// campaign_leaf_3e9270.cpp -- a member function at VA 0x10ce9270 taking four arguments: it formats
// the int its second argument points to with L"%i" into the buffer its first argument points to,
// through the free function at VA 0x10ccb0d0. It does not read this or its last two arguments.
// guess: an integer property exporting its value as text. The class, method and parameter names are
// invented; the addresses and the format string are the binary's.

int Unk_10ccb0d0(unsigned short* Dest, const unsigned short* Format, ...);

class UnkType_10ce9270
{
public:
    void Unk_10ce9270(unsigned short* ValueText, int* Value, int* DefaultValue, int Flags);
};

// UnkType_10ce9270::Unk_10ce9270
void UnkType_10ce9270::Unk_10ce9270(unsigned short* ValueText, int* Value, int* DefaultValue,
    int Flags)
{
    Unk_10ccb0d0(ValueText, L"%i", *Value);
}
