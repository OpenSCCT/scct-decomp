// campaign_leaf_456940.cpp -- thiscall at VA 0x10d56940: when the pointer at offset 0x58 is set,
// replaces it with the result of the stdcall function at VA 0x10d565e0 called with it and returns
// true; otherwise returns false. All names are invented.

void* __stdcall Unk_10d565e0(void* Pointer);

class UnkType_10d56940
{
public:
    bool Unk_10d56940();

private:
    unsigned char unk_00[0x58];
    void* unk_58;
};

// UnkType_10d56940::Unk_10d56940
bool UnkType_10d56940::Unk_10d56940()
{
    if (unk_58) {
        unk_58 = Unk_10d565e0(unk_58);
        return true;
    }
    return false;
}
