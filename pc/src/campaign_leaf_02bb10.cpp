// campaign_leaf_02bb10.cpp -- one function at file offset 0x2bb10, preferred VA 0x1092bb10. It
// stores the value 1 through each of its two pointer arguments. It has no this pointer use. The
// class, method and parameter names are invented; the offset and the bytes are the binary's.

class UnkType_1092bb10
{
public:
    void UnkSetPair(int *First, int *Second);
};

// UnkType_1092bb10::UnkSetPair
void UnkType_1092bb10::UnkSetPair(int *First, int *Second)
{
    *First = 1;
    *Second = 1;
}
