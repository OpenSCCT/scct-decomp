// campaign_leaf_237a80.cpp -- a member function at VA 0x10b37a80 taking a flag: when the pointer
// at 0x14 is set and the flag is set, unless the member at VA 0x10ad5970 of the object the pointer
// at 0x10 refers to accepts it or the byte at 0x19 is set, it passes the pointer, 1, 1 and 0 to
// that object's member at VA 0x10ad5820, calls the member at VA 0x10bbd180 of the object's target
// (what the member at VA 0x10a45b50 of the object at 0x64 of the entry its pointer at 0x04 gives
// for its byte at 0x0c with the member at VA 0x10a0e220 returns) and sets the byte at 0x19. When
// the flag is clear and that member accepts the pointer or the byte is set, it clears the byte,
// passes the pointer, 0, 1 and 0 to the member at VA 0x10ad5820 and calls the target's member at
// VA 0x10bbd1b0. The class, method, member and parameter names are invented; the offsets and
// addresses are the binary's.

class UnkType_10b37a80_Page;

class UnkType_10b37a80_Target
{
public:
    void Unk_10bbd180();
    void Unk_10bbd1b0();
};

class UnkType_10b37a80_Lookup
{
public:
    UnkType_10b37a80_Target* Unk_10a45b50();
};

class UnkType_10b37a80_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b37a80_Lookup* unk_64;
};

class UnkType_10b37a80_Table
{
public:
    UnkType_10b37a80_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b37a80_Menu
{
public:
    // guess: the current target (an inline accessor; name invented)
    UnkType_10b37a80_Target* GetTarget()
    {
        return unk_04->Unk_10a0e220(unk_0c)->unk_64->Unk_10a45b50();
    }

    void Unk_10ad5820(UnkType_10b37a80_Page* Page, int First, int Second, int Third);
    bool Unk_10ad5970(UnkType_10b37a80_Page* Page);

    int unk_00;
    UnkType_10b37a80_Table* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

class UnkType_10b37a80
{
public:
    void Unk_10b37a80(bool Flag);

private:
    unsigned char unk_00[0x10];
    UnkType_10b37a80_Menu* unk_10;
    UnkType_10b37a80_Page* unk_14;
    unsigned char unk_18;
    bool unk_19;
};

// UnkType_10b37a80::Unk_10b37a80
void UnkType_10b37a80::Unk_10b37a80(bool Flag)
{
    if ( unk_14 )
    {
        if ( Flag )
        {
            if ( !unk_10->Unk_10ad5970(unk_14) && !unk_19 )
            {
                unk_10->Unk_10ad5820(unk_14, 1, 1, 0);
                unk_10->GetTarget()->Unk_10bbd180();
                unk_19 = true;
            }
        }
        else if ( unk_10->Unk_10ad5970(unk_14) || unk_19 )
        {
            unk_19 = false;
            unk_10->Unk_10ad5820(unk_14, 0, 1, 0);
            unk_10->GetTarget()->Unk_10bbd1b0();
        }
    }
}
