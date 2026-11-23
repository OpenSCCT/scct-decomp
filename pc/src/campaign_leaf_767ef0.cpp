// campaign_leaf_767ef0.cpp -- one function at file offset 0x767ef0, preferred VA 0x11067ef0. When
// the object its argument points to is set it calls the method at VA 0x11067c80 on it, passes it
// to the stdcall function at VA 0x1103c870 (which forwards it to slot 2 of the object at VA
// 0x111c88a0) and clears the pointer. The type and function names are invented; the offset and
// the addresses are the binary's.

void __stdcall Unk_1103c870(void* Pointer);

class UnkType_11067ef0
{
public:
    void Unk_11067c80();
};

// Unk_11067ef0
void Unk_11067ef0(UnkType_11067ef0** Object)
{
    UnkType_11067ef0* Current;

    Current = *Object;
    if ( Current != 0 )
    {
        Current->Unk_11067c80();
        Unk_1103c870(Current);
        *Object = 0;
    }
}
