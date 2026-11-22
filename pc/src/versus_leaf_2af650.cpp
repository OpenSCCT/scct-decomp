// versus_leaf_2af650.cpp -- clears the int at 0x38 when it is nonzero and the byte at 0x3c is zero, at file offset 0x2af650 (VA 0x10baf650).
// The class, member, argument and method names are invented; the offsets, the argument
// sizes and the return convention are the binary's.

class UnkType_10baf650
{
public:
    void ClearUnk38IfIdle();

private:
    unsigned char unk_00[0x38];         // not read by this function
    int unk_38;                         // cleared by ClearUnk38IfIdle when unk_3c is zero
    unsigned char unk_3c;               // tested by ClearUnk38IfIdle
};

// UnkType_10baf650::ClearUnk38IfIdle
void UnkType_10baf650::ClearUnk38IfIdle()
{
    if ( unk_38 != 0 && unk_3c == 0 )
    {
        unk_38 = 0;
    }
}
