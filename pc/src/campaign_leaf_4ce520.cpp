// campaign_leaf_4ce520.cpp -- thiscall at VA 0x10dce520: passes its argument to the method at
// VA 0x10dd9cf0 on the same object and returns the argument. All names are invented.

class UnkType_10dce520
{
public:
    void Unk_10dd9cf0(void* Value);
    void* Unk_10dce520(void* Value);
};

// UnkType_10dce520::Unk_10dce520
void* UnkType_10dce520::Unk_10dce520(void* Value)
{
    Unk_10dd9cf0(Value);
    return Value;
}
