// campaign_leaf_1e7320.cpp -- thiscall method at VA 0x10ae7320. Working on the object returned by
// the function at VA 0x10c38440 each time: when its byte at 0xaa is set it calls its method at VA
// 0x10c38480; when the method at VA 0x10c36de0 reports true it calls, depending on the method at VA
// 0x10c36da0, either the method at VA 0x10c36c00 with two zeros or the one at VA 0x10c36f70; it
// then calls virtual slot 7 and clears the byte at 0x04. The class, method and member names are
// invented.

class UnkType_10ae7320_Source
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

    void Unk_10c38480();
    bool Unk_10c36de0();
    bool Unk_10c36da0();
    void Unk_10c36c00(int First, int Second);
    void Unk_10c36f70();

    char unk_04[0xaa - 0x04];
    bool unk_aa;
};

UnkType_10ae7320_Source* Unk_10c38440();

class UnkType_10ae7320
{
public:
    void Unk_10ae7320();

private:
    int unk_0;
    bool unk_4;
};

// UnkType_10ae7320::Unk_10ae7320
void UnkType_10ae7320::Unk_10ae7320()
{
    if ( Unk_10c38440()->unk_aa )
    {
        Unk_10c38440()->Unk_10c38480();
    }
    if ( Unk_10c38440()->Unk_10c36de0() )
    {
        if ( Unk_10c38440()->Unk_10c36da0() )
        {
            Unk_10c38440()->Unk_10c36c00(0, 0);
        }
        else
        {
            Unk_10c38440()->Unk_10c36f70();
        }
    }
    Unk_10c38440()->VirtualSlot7();
    unk_4 = false;
}
