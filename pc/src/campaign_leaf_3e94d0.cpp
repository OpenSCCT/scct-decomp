// campaign_leaf_3e94d0.cpp -- a member function at VA 0x10ce94d0 taking four arguments: it formats
// the float its second argument points to with L"%f" into the buffer its first argument points to,
// through the free function at VA 0x10ccb0d0. It does not read this or its last two arguments.
// guess: a float property exporting its value as text. The class, method and parameter names are
// invented; the addresses and the format string are the binary's.

int Unk_10ccb0d0(unsigned short* Dest, const unsigned short* Format, ...);

class UnkType_10ce94d0
{
public:
    void Unk_10ce94d0(unsigned short* ValueText, float* Value, float* DefaultValue, int Flags);
};

// UnkType_10ce94d0::Unk_10ce94d0
void UnkType_10ce94d0::Unk_10ce94d0(unsigned short* ValueText, float* Value, float* DefaultValue,
    int Flags)
{
    Unk_10ccb0d0(ValueText, L"%f", *Value);
}
