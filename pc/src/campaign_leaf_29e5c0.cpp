// campaign_leaf_29e5c0.cpp -- method at VA 0x10b9e5c0 taking an index: makes a function-local
// static name L"s_PlayerWalking" on first use (through the name constructor at VA 0x10cd4790 with
// 2); returns 1 when the pawn of the 100-byte entry at that index of the array at 0x4f0 is set and
// has bit 5 of its word at 0x2c set, the word at 0x42c is set, the pawn's float at 0x304 is at most
// 0.15, bit 1 of its word at 0x2b8 is set, the entry's word at 0x2c is clear, the pawn's method at
// VA 0x10b84be0 returns 0, its method at VA 0x10b802a0 accepts 2.5, its method at VA 0x10b84b40
// rejects, its controller at 0x2b4 accepts the name through the method at VA 0x10cd72b0, and bit 0
// of the controller's word at 0x550 is clear; otherwise 0. The class, member and method names are
// invented; the offsets, the string, the constants and the addresses are the binary's.

class UnkType_10b9e5c0_Name
{
public:
    UnkType_10b9e5c0_Name(const unsigned short* Text, int FindType);

private:
    int unk_00;
};

class UnkType_10b9e5c0_Controller
{
public:
    int Unk_10cd72b0(const UnkType_10b9e5c0_Name& Name);

    unsigned char unk_00[0x550];
    int unk_550;
};

class UnkType_10b9e5c0_Pawn
{
public:
    int Unk_10b84be0();
    bool Unk_10b802a0(float Range);
    bool Unk_10b84b40();

    unsigned char unk_00[0x2c];
    int unk_2c;
    unsigned char unk_30[0x2b4 - 0x30];
    UnkType_10b9e5c0_Controller* unk_2b4;
    int unk_2b8;
    unsigned char unk_2bc[0x304 - 0x2bc];
    float unk_304;
};

class UnkType_10b9e5c0_Entry
{
public:
    UnkType_10b9e5c0_Pawn* unk_00;
    unsigned char unk_04[0x2c - 0x04];
    int unk_2c;
    unsigned char unk_30[0x64 - 0x30];
};

class UnkType_10b9e5c0
{
public:
    int Unk_10b9e5c0(int Index);

private:
    unsigned char unk_00[0x42c];
    int unk_42c;
    unsigned char unk_430[0x4f0 - 0x430];
    UnkType_10b9e5c0_Entry* unk_4f0;
};

// UnkType_10b9e5c0::Unk_10b9e5c0
int UnkType_10b9e5c0::Unk_10b9e5c0(int Index)
{
    static UnkType_10b9e5c0_Name PlayerWalking(L"s_PlayerWalking", 2);
    UnkType_10b9e5c0_Entry* Entry = &unk_4f0[Index];
    UnkType_10b9e5c0_Pawn* Pawn = Entry->unk_00;
    int Result = 0;
    if ( Pawn && ( Pawn->unk_2c & 0x20 ) && unk_42c && Pawn->unk_304 <= 0.15f
        && ( Pawn->unk_2b8 & 2 ) && !Entry->unk_2c && !Pawn->Unk_10b84be0()
        && Pawn->Unk_10b802a0(2.5f) && !Pawn->Unk_10b84b40() )
    {
        UnkType_10b9e5c0_Controller* Controller = Pawn->unk_2b4;
        if ( Controller->Unk_10cd72b0(PlayerWalking) && !( Controller->unk_550 & 1 ) )
        {
            Result = 1;
        }
    }
    return Result;
}
