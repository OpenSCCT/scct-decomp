// campaign_leaf_3e9190.cpp -- a member function at VA 0x10ce9190 taking two arguments: it passes
// the wide string L"BYTE" to the member at VA 0x10ccdfb0 of the object its first argument refers
// to. It does not read this or its second argument. guess: a property class writing its C++ type
// name to an output device. The class, method and parameter names are invented; the addresses and
// the string are the binary's.

class UnkType_10ccdfb0
{
public:
    void Unk_10ccdfb0(const unsigned short* Text);
};

class UnkType_10ce9190
{
public:
    void Unk_10ce9190(UnkType_10ccdfb0& Out, int Flags);
};

// UnkType_10ce9190::Unk_10ce9190
void UnkType_10ce9190::Unk_10ce9190(UnkType_10ccdfb0& Out, int Flags)
{
    Out.Unk_10ccdfb0(L"BYTE");
}
