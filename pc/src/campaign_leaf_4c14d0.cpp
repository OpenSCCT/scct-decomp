// campaign_leaf_4c14d0.cpp -- one function at file offset 0x4c14d0, preferred VA 0x10dc14d0.
// It stores State at offset 0x18 and, when State is 4 and the callback at offset 8 is set, calls
// the callback with the object and the address of the member at offset 0xc. The class, method,
// member and parameter names are invented; the offset and the bytes are the binary's.

class UnkType_10dc14d0;

typedef void (*UnkType_10dc14d0_Callback)(UnkType_10dc14d0* Item, int* Data);

class UnkType_10dc14d0
{
public:
    int unk_0;
    int unk_4;
    UnkType_10dc14d0_Callback unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    int unk_18;

    void Unk_10dc14d0(int State);
};

// UnkType_10dc14d0::Unk_10dc14d0
void UnkType_10dc14d0::Unk_10dc14d0(int State)
{
    unk_18 = State;
    if ( State == 4 && unk_8 != 0 )
    {
        unk_8(this, &unk_c);
    }
}
