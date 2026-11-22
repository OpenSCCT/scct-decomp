// versus_leaf_012690.cpp -- the function at file offset 0x12690, VA 0x10912690, 37 bytes. It moves
// the 16-bit text cursor whose address arrives in EDX past spaces, tabs, carriage returns and line
// feeds. ECX is loaded from the cursor and never read as an argument.
// The class and method names are invented; the offset and the bytes are the binary's.

class UnkType_10912690
{
public:
    void __fastcall UnkFunc_10912690(unsigned short **Cursor);
};

// UnkType_10912690::UnkFunc_10912690
void __fastcall UnkType_10912690::UnkFunc_10912690(unsigned short **Cursor)
{
    while ( **Cursor == 0x20 || **Cursor == 9 || **Cursor == 0xd || **Cursor == 0xa )
    {
        *Cursor = *Cursor + 1;
    }
}
