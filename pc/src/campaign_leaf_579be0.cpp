// campaign_leaf_579be0.cpp -- thiscall method at VA 0x10e79be0: finds the entry of the table at
// 0x0c (12-byte entries, count at 0x10) whose name the cdecl function at VA 0x10dffc00 reports
// equal to the name it is given, creates an object with the entry's function, passes the third
// argument to the object's method at VA 0x10e7a5f0 and the second to its second virtual method, and
// returns it; null when no entry matches. guess: a factory by class name. All names are invented.

int Unk_10dffc00(const char* First, const char* Second);

class UnkType_10e79be0_Object
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(int Value);

    void Unk_10e7a5f0(int Value);
};

typedef UnkType_10e79be0_Object* (*UnkType_10e79be0_Create)();

struct UnkType_10e79be0_Entry
{
    const char* unk_00;
    UnkType_10e79be0_Create unk_04;
    int unk_08;
};

class UnkType_10e79be0
{
public:
    UnkType_10e79be0_Object* Unk_10e79be0(const char* Name, int First, int Second);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e79be0_Entry* unk_0c;
    int unk_10;
};

// UnkType_10e79be0::Unk_10e79be0
UnkType_10e79be0_Object* UnkType_10e79be0::Unk_10e79be0(const char* Name, int First, int Second)
{
    for ( int Index = 0; Index < unk_10; Index++ )
    {
        const char* EntryName = unk_0c[Index].unk_00;
        if ( Unk_10dffc00(EntryName, Name) == 0 )
        {
            UnkType_10e79be0_Object* Object = unk_0c[Index].unk_04();
            Object->Unk_10e7a5f0(Second);
            Object->VirtualSlot1(First);
            return Object;
        }
    }
    return 0;
}
