// campaign_leaf_3e9720.cpp -- a member function at VA 0x10ce9720 taking three arguments: it passes
// the first two to the free function at VA 0x10cce480. It does not read this or its third argument.
// The class, method and parameter names are invented; the addresses are the binary's.

class UnkType_10cce480;

void Unk_10cce480(UnkType_10cce480& Ar, void* Value);

class UnkType_10ce9720
{
public:
    void Unk_10ce9720(UnkType_10cce480& Ar, void* Value, int MaxBytes);
};

// UnkType_10ce9720::Unk_10ce9720
void UnkType_10ce9720::Unk_10ce9720(UnkType_10cce480& Ar, void* Value, int MaxBytes)
{
    Unk_10cce480(Ar, Value);
}
