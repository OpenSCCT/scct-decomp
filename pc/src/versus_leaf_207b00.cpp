// versus_leaf_207b00.cpp -- stores its byte argument in the byte member at 0x154 of the object, at file offset 0x207b00 (VA 0x10b07b00).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b07b00
{
public:
    void SetUnk154(unsigned char Value);

private:
    unsigned char unk_00[0x154];  // not read by this function
    unsigned char unk_154;        // written by SetUnk154
};

// UnkType_10b07b00::SetUnk154
// The function pops its one argument (ret 4).
void UnkType_10b07b00::SetUnk154(unsigned char Value)
{
    unk_154 = Value;
}
