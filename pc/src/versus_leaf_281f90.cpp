// versus_leaf_281f90.cpp -- clears four dwords of the object and sets the float at 0x10 to 1.0, at file offset
// 0x281f90 (VA 0x10b81f90). The class, record and method names are invented; the offsets and the constant are the
// binary's. The function takes its one pointer argument and pops nothing (ret).

struct UnkObj_10b81f90
{
    int unk_00;                         // cleared by ResetUnkObj
    int unk_04;                         // cleared by ResetUnkObj
    int unk_08;                         // cleared by ResetUnkObj
    int unk_0c;                         // cleared by ResetUnkObj
    float unk_10;                       // set to 1.0 by ResetUnkObj
};

class UnkType_10b81f90
{
public:
    static void ResetUnkObj(UnkObj_10b81f90 *Obj);
};

// UnkType_10b81f90::ResetUnkObj
// The stores are in the order of the binary.
void UnkType_10b81f90::ResetUnkObj(UnkObj_10b81f90 *Obj)
{
    Obj->unk_00 = 0;
    Obj->unk_0c = 0;
    Obj->unk_08 = 0;
    Obj->unk_04 = 0;
    Obj->unk_10 = 1.0f;
}
