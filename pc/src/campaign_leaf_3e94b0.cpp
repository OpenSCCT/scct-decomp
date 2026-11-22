// campaign_leaf_3e94b0.cpp -- a member function at VA 0x10ce94b0 taking two arguments: it passes
// the wide string L"FLOAT" to the member at VA 0x10ccdfb0 of the object its first argument refers
// to. It does not read this or its second argument. guess: a property class writing its C++ type
// name to an output device. The class, method and parameter names are invented; the addresses and
// the string are the binary's.

class UnkType_10ccdfb0
{
public:
    void Unk_10ccdfb0(const unsigned short* Text);
};

class UnkType_10ce94b0
{
public:
    void Unk_10ce94b0(UnkType_10ccdfb0& Out, int Flags);
};

// UnkType_10ce94b0::Unk_10ce94b0
void UnkType_10ce94b0::Unk_10ce94b0(UnkType_10ccdfb0& Out, int Flags)
{
    Out.Unk_10ccdfb0(L"FLOAT");
}
