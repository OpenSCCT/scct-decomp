// campaign_leaf_472880.cpp -- thiscall method at VA 0x10d72880. After its own method at 0x10d6c450
// it walks the list whose first node is at 0x138; for each node's item it calls its own method at
// 0x10d6c510 when the item's word at 0x64 or 0x70 is set, the item's method at 0x10d6eea0 when
// both 0x9c and 0x70 are set, and the item's method at 0x10d6f050 when 0x64 is above 10. It then
// calls its own method at 0x10d727f0 and passes the word at 0xf0 to 0x110478c0. The class,
// method and member names are invented.

class UnkType_10d72880_Item
{
public:
    void Unk_10d6eea0();
    void Unk_10d6f050();

    unsigned char unk_0[0x64];
    unsigned int unk_64;
    unsigned char unk_68[0x8];
    int unk_70;
    unsigned char unk_74[0x28];
    int unk_9c;
};

struct UnkType_10d72880_Node
{
    UnkType_10d72880_Node* unk_0;
    int unk_4;
    UnkType_10d72880_Item* unk_8;
};

struct UnkType_10d72880_Iterator
{
    UnkType_10d72880_Item* operator*()
    {
        return unk_0->unk_8;
    }

    UnkType_10d72880_Iterator operator++(int)
    {
        UnkType_10d72880_Iterator Old = *this;
        unk_0 = unk_0->unk_0;
        return Old;
    }

    UnkType_10d72880_Node* unk_0;
};

void __stdcall Unk_110478c0(int Value);

class UnkType_10d72880
{
public:
    void Unk_10d72880();
    void Unk_10d6c450();
    void Unk_10d6c510(UnkType_10d72880_Item* Item);
    void Unk_10d727f0();

private:
    unsigned char unk_0[0xf0];
    int unk_f0;
    unsigned char unk_f4[0x44];
    UnkType_10d72880_Node* unk_138;
};

// UnkType_10d72880::Unk_10d72880
void UnkType_10d72880::Unk_10d72880()
{
    UnkType_10d72880_Iterator Next;
    UnkType_10d72880_Item* Item;

    Unk_10d6c450();
    Next.unk_0 = unk_138;
    while ( Next.unk_0 )
    {
        Item = *Next++;
        if ( Item->unk_64 || Item->unk_70 )
        {
            Unk_10d6c510(Item);
        }
        if ( Item->unk_9c && Item->unk_70 )
        {
            Item->Unk_10d6eea0();
        }
        if ( Item->unk_64 > 10 )
        {
            Item->Unk_10d6f050();
        }
    }
    Unk_10d727f0();
    Unk_110478c0(unk_f0);
}
