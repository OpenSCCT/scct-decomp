// campaign_leaf_1327f0.cpp -- one function at file offset 0x1327f0, preferred VA 0x10a327f0.
// guess: empties its array at offset 0x39d8 (tag "FArray", through the allocator at VA
// 0x111c88a0) and refills it with every non-null object of its array at 0x28 that virtual slot
// 152 accepts, adding each through the method at VA 0x1098c4f0.
// The class, member and callee names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a327f0_Object
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
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void VirtualSlot63();
    virtual void VirtualSlot64();
    virtual void VirtualSlot65();
    virtual void VirtualSlot66();
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void VirtualSlot73();
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual void VirtualSlot80();
    virtual void VirtualSlot81();
    virtual void VirtualSlot82();
    virtual void VirtualSlot83();
    virtual void VirtualSlot84();
    virtual void VirtualSlot85();
    virtual void VirtualSlot86();
    virtual void VirtualSlot87();
    virtual void VirtualSlot88();
    virtual void VirtualSlot89();
    virtual void VirtualSlot90();
    virtual void VirtualSlot91();
    virtual void VirtualSlot92();
    virtual void VirtualSlot93();
    virtual void VirtualSlot94();
    virtual void VirtualSlot95();
    virtual void VirtualSlot96();
    virtual void VirtualSlot97();
    virtual void VirtualSlot98();
    virtual void VirtualSlot99();
    virtual void VirtualSlot100();
    virtual void VirtualSlot101();
    virtual void VirtualSlot102();
    virtual void VirtualSlot103();
    virtual void VirtualSlot104();
    virtual void VirtualSlot105();
    virtual void VirtualSlot106();
    virtual void VirtualSlot107();
    virtual void VirtualSlot108();
    virtual void VirtualSlot109();
    virtual void VirtualSlot110();
    virtual void VirtualSlot111();
    virtual void VirtualSlot112();
    virtual void VirtualSlot113();
    virtual void VirtualSlot114();
    virtual void VirtualSlot115();
    virtual void VirtualSlot116();
    virtual void VirtualSlot117();
    virtual void VirtualSlot118();
    virtual void VirtualSlot119();
    virtual void VirtualSlot120();
    virtual void VirtualSlot121();
    virtual void VirtualSlot122();
    virtual void VirtualSlot123();
    virtual void VirtualSlot124();
    virtual void VirtualSlot125();
    virtual void VirtualSlot126();
    virtual void VirtualSlot127();
    virtual void VirtualSlot128();
    virtual void VirtualSlot129();
    virtual void VirtualSlot130();
    virtual void VirtualSlot131();
    virtual void VirtualSlot132();
    virtual void VirtualSlot133();
    virtual void VirtualSlot134();
    virtual void VirtualSlot135();
    virtual void VirtualSlot136();
    virtual void VirtualSlot137();
    virtual void VirtualSlot138();
    virtual void VirtualSlot139();
    virtual void VirtualSlot140();
    virtual void VirtualSlot141();
    virtual void VirtualSlot142();
    virtual void VirtualSlot143();
    virtual void VirtualSlot144();
    virtual void VirtualSlot145();
    virtual void VirtualSlot146();
    virtual void VirtualSlot147();
    virtual void VirtualSlot148();
    virtual void VirtualSlot149();
    virtual void VirtualSlot150();
    virtual void VirtualSlot151();
    virtual int VirtualSlot152();
};

class UnkType_10a327f0_Array
{
public:
    UnkType_10a327f0_Object** Data;
    int ArrayNum;
    int ArrayMax;

    void Empty()
    {
        ArrayNum = 0;
        ArrayMax = 0;
        Data = (UnkType_10a327f0_Object**)GUnk_111c88a0->Realloc(Data,
            ArrayMax * sizeof(UnkType_10a327f0_Object*), L"FArray");
    }
    void Unk_1098c4f0(UnkType_10a327f0_Object* const& Item);
};

class UnkType_10a327f0
{
public:
    unsigned char unk_0[0x28];
    UnkType_10a327f0_Array unk_28;
    unsigned char unk_34[0x39d8 - 0x34];
    UnkType_10a327f0_Array unk_39d8;

    void Unk_10a327f0();
};

// UnkType_10a327f0::Unk_10a327f0
void UnkType_10a327f0::Unk_10a327f0()
{
    unk_39d8.Empty();
    for ( int i = 0; i < unk_28.ArrayNum; i++ )
    {
        UnkType_10a327f0_Object* Object = unk_28.Data[i];
        if ( Object && Object->VirtualSlot152() )
        {
            unk_39d8.Unk_1098c4f0(unk_28.Data[i]);
        }
    }
}
