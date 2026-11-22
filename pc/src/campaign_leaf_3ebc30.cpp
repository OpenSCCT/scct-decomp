// campaign_leaf_3ebc30.cpp -- a member function at VA 0x10cebc30 taking three arguments: it passes
// the second to the member at VA 0x109097e0 of the object the first refers to. It does not read
// this or its third argument. The class, method and parameter names are invented; the addresses
// are the binary's.

class UnkType_109097e0
{
public:
    void Unk_109097e0(void* Value);
};

class UnkType_10cebc30
{
public:
    void Unk_10cebc30(UnkType_109097e0& Ar, void* Value, int MaxBytes);
};

// UnkType_10cebc30::Unk_10cebc30
void UnkType_10cebc30::Unk_10cebc30(UnkType_109097e0& Ar, void* Value, int MaxBytes)
{
    Ar.Unk_109097e0(Value);
}
