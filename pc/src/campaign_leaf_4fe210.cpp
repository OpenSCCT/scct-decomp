// campaign_leaf_4fe210.cpp -- method at VA 0x10dfe210: true when the key made of the result of
// virtual slot 14 for its first argument and its second argument is in the array at 0x08 (method
// at VA 0x10dfe2a0), or its third argument is a key of the array of word pairs at 0x14; false
// otherwise. The class, method and member names are invented; the offsets, the slot and the
// address are the binary's.

class UnkType_10dfe210_Result
{
public:
    UnkType_10dfe210_Result(bool InValue)
        : Value(InValue)
    {
    }

    bool Value;
};

class UnkType_10dfe210_Key
{
public:
    int unk_00;
    int unk_04;
};

class UnkType_10dfe210_Keys
{
public:
    int* Unk_10dfe2a0(const UnkType_10dfe210_Key& Key);

    void* Data;
    int Num;
    int Max;
};

class UnkType_10dfe210_Pair
{
public:
    int Key;
    int Value;
};

class UnkType_10dfe210_Pairs
{
public:
    int* Find(int Key)
    {
        for ( int i = 0; i < Num; i++ )
        {
            if ( Data[i].Key == Key )
            {
                return &Data[i].Value;
            }
        }
        return 0;
    }

    UnkType_10dfe210_Pair* Data;
    int Num;
    int Max;
};

class UnkType_10dfe210
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual int VirtualSlot14(int Arg);

    UnkType_10dfe210_Result Unk_10dfe210(int Arg0, int Arg1, int Arg2);

    int unk_04;
    UnkType_10dfe210_Keys unk_08;
    UnkType_10dfe210_Pairs unk_14;
};

// UnkType_10dfe210::Unk_10dfe210
UnkType_10dfe210_Result UnkType_10dfe210::Unk_10dfe210(int Arg0, int Arg1, int Arg2)
{
    UnkType_10dfe210_Key Key;
    Key.unk_00 = VirtualSlot14(Arg0);
    Key.unk_04 = Arg1;
    if ( unk_08.Unk_10dfe2a0(Key) != 0 || unk_14.Find(Arg2) != 0 )
    {
        return UnkType_10dfe210_Result(true);
    }
    return UnkType_10dfe210_Result(false);
}
