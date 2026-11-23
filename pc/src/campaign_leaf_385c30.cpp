// campaign_leaf_385c30.cpp -- method at VA 0x10c85c30: advances a ring index at 0x04 modulo the
// count at 0x00, then for each 12-byte entry of the vector at 0x0c stores the entry's interface
// for that index through the entry's slot pointer and, when the entry has a second interface slot,
// calls slot 2 on the interface it holds and then slot 18 of the stored interface with 0 and that
// slot. The calls are __stdcall interface methods. The class, member, method and interface names
// are invented; the offsets, the slots and the vector of the compiler's library are the binary's.

#include <vector>

class UnkType_10c85c30_Second
{
public:
    virtual void __stdcall VirtualSlot0();
    virtual void __stdcall VirtualSlot1();
    virtual unsigned long __stdcall VirtualSlot2();
};

class UnkType_10c85c30_First
{
public:
    virtual void __stdcall VirtualSlot0();
    virtual void __stdcall VirtualSlot1();
    virtual void __stdcall VirtualSlot2();
    virtual void __stdcall VirtualSlot3();
    virtual void __stdcall VirtualSlot4();
    virtual void __stdcall VirtualSlot5();
    virtual void __stdcall VirtualSlot6();
    virtual void __stdcall VirtualSlot7();
    virtual void __stdcall VirtualSlot8();
    virtual void __stdcall VirtualSlot9();
    virtual void __stdcall VirtualSlot10();
    virtual void __stdcall VirtualSlot11();
    virtual void __stdcall VirtualSlot12();
    virtual void __stdcall VirtualSlot13();
    virtual void __stdcall VirtualSlot14();
    virtual void __stdcall VirtualSlot15();
    virtual void __stdcall VirtualSlot16();
    virtual void __stdcall VirtualSlot17();
    virtual long __stdcall VirtualSlot18(unsigned int Index, UnkType_10c85c30_Second **Slot);
};

struct UnkType_10c85c30_Entry
{
    UnkType_10c85c30_First **unk_00;
    UnkType_10c85c30_Second **unk_04;
    UnkType_10c85c30_First **unk_08;
};

class UnkType_10c85c30
{
public:
    void Unk_10c85c30();

private:
    unsigned int unk_00;
    unsigned int unk_04;
    int unk_08;
    std::vector<UnkType_10c85c30_Entry> unk_0c;
};

// UnkType_10c85c30::Unk_10c85c30
void UnkType_10c85c30::Unk_10c85c30()
{
    unsigned int Index;

    unk_04 = (unk_04 + 1) % unk_00;
    for ( Index = 0; Index < unk_0c.size(); Index++ )
    {
        UnkType_10c85c30_Entry &Entry = unk_0c[Index];

        *Entry.unk_00 = Entry.unk_08[unk_04];
        if ( Entry.unk_04 != NULL )
        {
            (*Entry.unk_04)->VirtualSlot2();
            (*Entry.unk_00)->VirtualSlot18(0, Entry.unk_04);
        }
    }
}
