// versus_leaf_276e80.cpp -- returns -1 when the flag at 0x14 of the object is set, otherwise the value from its
// members at 4, 8 and 0xc, at file offset 0x276e80 (VA 0x10b76e80). The class, record and method names are invented;
// the offsets and the shift are the binary's. The function takes its one pointer argument and pops nothing (ret).

struct UnkObj_10b76e80
{
    int unk_00;
    int unk_04;                         // read by GetUnkRemaining
    int unk_08;                         // read by GetUnkRemaining
    int unk_0c;                         // read by GetUnkRemaining
    int unk_10;
    int unk_14;                         // when set, the function returns -1
};

class UnkType_10b76e80
{
public:
    static int GetUnkRemaining(UnkObj_10b76e80 *Obj);
};

// UnkType_10b76e80::GetUnkRemaining
int UnkType_10b76e80::GetUnkRemaining(UnkObj_10b76e80 *Obj)
{
    if (Obj->unk_14 != 0)
    {
        return -1;
    }
    return Obj->unk_04 - (Obj->unk_08 << 3) - Obj->unk_0c;
}
