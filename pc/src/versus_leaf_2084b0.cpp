// versus_leaf_2084b0.cpp -- stores its byte argument in the byte member at 0x15c of the object, at file offset 0x2084b0 (VA 0x10b084b0).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b084b0
{
public:
    void SetUnk15C(unsigned char Value);

private:
    unsigned char unk_00[0x15c];  // not read by this function
    unsigned char unk_15c;        // written by SetUnk15C
};

// UnkType_10b084b0::SetUnk15C
// The function pops its one argument (ret 4).
void UnkType_10b084b0::SetUnk15C(unsigned char Value)
{
    unk_15c = Value;
}
