// campaign_leaf_4dc3a0.cpp -- free function at VA 0x10ddc3a0: calls the method at VA 0x10d9df90 of
// its argument with the address of a local dword and returns that dword. All names are invented.

class UnkType_10d9df90
{
public:
    void Unk_10d9df90(int* Result);
};

// Unk_10ddc3a0
int Unk_10ddc3a0(UnkType_10d9df90* Object)
{
    int Result;
    Object->Unk_10d9df90(&Result);
    return Result;
}
