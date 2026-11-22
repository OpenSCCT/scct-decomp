// campaign_leaf_4f1d10.cpp -- one function at file offset 0x4f1d10, preferred VA 0x10df1d10.
// The constructor passes the address of the function at 0x10df1cf0 to the cdecl function at
// 0x10d830b0. guess: it registers a callback. The class and function names are invented; the
// offset and the bytes are the binary's.

void Unk_10df1cf0();
void Unk_10d830b0(void (*Function)());

class UnkType_10df1d10
{
public:
    UnkType_10df1d10();
};

// UnkType_10df1d10::UnkType_10df1d10
UnkType_10df1d10::UnkType_10df1d10()
{
    Unk_10d830b0(Unk_10df1cf0);
}
