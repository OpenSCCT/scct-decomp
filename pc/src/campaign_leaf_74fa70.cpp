// campaign_leaf_74fa70.cpp -- one function at file offset 0x74fa70, preferred VA 0x1104fa70. It
// passes the words at 0x14 and 0x0 of the record its argument points to at 0x3c to the stdcall
// function at VA 0x1104b1f0 and returns the result. It has no this pointer. The class and function
// names are invented; the offset and the callee's address are the binary's.

int __stdcall Unk_1104b1f0(int First, int Second);

struct UnkType_1104fa70_Record
{
    int unk_0;
    unsigned char unk_4[0x14 - 0x4];
    int unk_14;
};

struct UnkType_1104fa70
{
    unsigned char unk_0[0x3c];
    UnkType_1104fa70_Record* unk_3c;
};

// Unk_1104fa70
int Unk_1104fa70(UnkType_1104fa70* Object)
{
    return Unk_1104b1f0(Object->unk_3c->unk_14, Object->unk_3c->unk_0);
}
