// campaign_leaf_480a10.cpp -- thiscall at VA 0x10d80a10: returns the address of element n of the
// array the pointer at offset 8 points to, n being the result of the free function at
// VA 0x10d98f30, or of the element at offset 0x0c when n is zero. All names are invented.

struct UnkType_10d80a10_Element
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

int Unk_10d98f30();

class UnkType_10d80a10
{
public:
    UnkType_10d80a10_Element* Unk_10d80a10();

private:
    int unk_00;
    int unk_04;
    UnkType_10d80a10_Element* unk_08;
    UnkType_10d80a10_Element unk_0c;
};

// UnkType_10d80a10::Unk_10d80a10
UnkType_10d80a10_Element* UnkType_10d80a10::Unk_10d80a10()
{
    int Index = Unk_10d98f30();
    if (!Index) {
        return &unk_0c;
    }
    return &unk_08[Index];
}
