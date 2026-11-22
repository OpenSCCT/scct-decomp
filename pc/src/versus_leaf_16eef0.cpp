// versus_leaf_16eef0.cpp -- stores its two arguments at 0xc98 and 0xc9c of the object that the member at 0x30 points to, at file offset 0x16eef0 (VA 0x10a6eef0).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkPointee_10a6eef0
{
    unsigned char unk_00[0xc98];
    int unk_c98;                        // written by SetUnk30_C98C9C
    int unk_c9c;                        // written by SetUnk30_C98C9C
};

class UnkType_10a6eef0
{
public:
    void SetUnk30_C98C9C(int A, int B);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6eef0 *unk_30;
};

// UnkType_10a6eef0::SetUnk30_C98C9C
// Both arguments are read; the function pops both (ret 8).
void UnkType_10a6eef0::SetUnk30_C98C9C(int A, int B)
{
    UnkPointee_10a6eef0 *pointee = unk_30;
    pointee->unk_c9c = B;
    pointee->unk_c98 = A;
}
