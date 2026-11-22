// versus_leaf_239ce0.cpp -- stores the first int of the object at the pointer at 0 through the out-pointer argument, at file offset 0x239ce0 (VA 0x10b39ce0).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

struct UnkNode_10b39ce0
{
    int unk_00;                         // read by GetUnk00Value
};

class UnkType_10b39ce0
{
public:
    int *GetUnk00Value(int *Out);

private:
    UnkNode_10b39ce0 *unk_00;
};

// UnkType_10b39ce0::GetUnk00Value
// The function pops its one argument (ret 4).
int *UnkType_10b39ce0::GetUnk00Value(int *Out)
{
    *Out = unk_00->unk_00;
    return Out;
}
