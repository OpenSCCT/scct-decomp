// campaign_leaf_2ffc30.cpp -- method at VA 0x10bffc30 taking a pawn and a second, unread value:
// stores this object at 0x284 of the pawn and passes the pawn and 0 to the method at VA 0x1099f3f0;
// then, when bit 0 of the word at 0x2c8 is set, makes a function-local static name
// L"EReviveSyringe" on first use (through the name constructor at VA 0x10cd4790 with 2) and asks
// the inventory reached through 0x4a0 and 0x6dc of the pawn for it (method at VA 0x10c267c0): if
// found, copies the word at 0x2d4 to 0x2e4; otherwise asks the inventory of the pawn its method at
// VA 0x10a037c0 returns, and if that finds an item copies the word at 0x2d8 to 0x2e4, passes the
// item, 1 and 0 to that inventory's method at VA 0x10c274d0 and the item to the pawn's method at VA
// 0x10bfeee0. The class, member and method names are invented; the offsets, the string and the
// addresses are the binary's.

class UnkType_10bffc30_Name
{
public:
    UnkType_10bffc30_Name(const unsigned short* Text, int FindType);

private:
    int unk_00;
};

class UnkType_10bffc30_Item;

class UnkType_10bffc30_Inventory
{
public:
    UnkType_10bffc30_Item* Unk_10c267c0(UnkType_10bffc30_Name Name);
    void Unk_10c274d0(UnkType_10bffc30_Item* Item, int First, int Second);
};

class UnkType_10bffc30_4a0
{
public:
    unsigned char unk_00[0x6dc];
    UnkType_10bffc30_Inventory* unk_6dc;
};

class UnkType_10bffc30;

class UnkType_10bffc30_Pawn
{
public:
    UnkType_10bffc30_Pawn* Unk_10a037c0();
    void Unk_10bfeee0(UnkType_10bffc30_Item* Item);

    unsigned char unk_00[0x284];
    UnkType_10bffc30* unk_284;
    unsigned char unk_288[0x4a0 - 0x288];
    UnkType_10bffc30_4a0* unk_4a0;
};

class UnkType_10bffc30
{
public:
    void Unk_10bffc30(UnkType_10bffc30_Pawn* Pawn, int Unused);
    void Unk_1099f3f0(UnkType_10bffc30_Pawn* Pawn, int Value);

private:
    unsigned char unk_00[0x2c8];
    int unk_2c8;
    unsigned char unk_2cc[0x2d4 - 0x2cc];
    int unk_2d4;
    int unk_2d8;
    unsigned char unk_2dc[0x2e4 - 0x2dc];
    int unk_2e4;
};

// UnkType_10bffc30::Unk_10bffc30
void UnkType_10bffc30::Unk_10bffc30(UnkType_10bffc30_Pawn* Pawn, int Unused)
{
    Pawn->unk_284 = this;
    Unk_1099f3f0(Pawn, 0);
    if ( unk_2c8 & 1 )
    {
        static UnkType_10bffc30_Name ReviveSyringe(L"EReviveSyringe", 2);
        if ( Pawn->unk_4a0->unk_6dc->Unk_10c267c0(ReviveSyringe) )
        {
            unk_2e4 = unk_2d4;
            return;
        }
        UnkType_10bffc30_Pawn* Other = Pawn->Unk_10a037c0();
        UnkType_10bffc30_Item* Item = Other->unk_4a0->unk_6dc->Unk_10c267c0(ReviveSyringe);
        if ( Item )
        {
            unk_2e4 = unk_2d8;
            Other->unk_4a0->unk_6dc->Unk_10c274d0(Item, 1, 0);
            Pawn->Unk_10bfeee0(Item);
        }
    }
}
