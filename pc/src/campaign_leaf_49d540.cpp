// campaign_leaf_49d540.cpp -- free function at VA 0x10d9d540: calls the method at VA 0x10d9df90 of
// its first argument with the address of a local dword, stores that dword through its second
// argument and returns the first. All names are invented.

class UnkType_10d9df90
{
public:
    void Unk_10d9df90(int* Result);
};

// Unk_10d9d540
UnkType_10d9df90* Unk_10d9d540(UnkType_10d9df90* Object, int& Result)
{
    int Value;
    Object->Unk_10d9df90(&Value);
    Result = Value;
    return Object;
}
