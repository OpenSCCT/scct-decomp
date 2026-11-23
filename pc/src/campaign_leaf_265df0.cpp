// campaign_leaf_265df0.cpp -- a member function at VA 0x10b65df0 taking a pointer: when the byte at
// 0x18 is set, it fills a cleared rectangle of four shorts through virtual slot 4 of the object at
// 0x08 of what the pointer refers to, and passes its own member at VA 0x10b65d80 a point of two
// shorts: the first short of the point at 0x16 of what the member at VA 0x10ad4770 of the object
// the pointer at 0x00 refers to returns (copied before the rectangle is filled), and the
// rectangle's third short less 5. The class, method, member and parameter names are invented; the
// offsets, addresses and slot are the binary's.

class UnkType_10b65df0_Point
{
public:
    short unk_00;
    short unk_02;
};

class UnkType_10b65df0_Rect
{
public:
    short unk_00;
    short unk_02;
    short unk_04;
    short unk_06;
};

class UnkType_10b65df0_Source
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(UnkType_10b65df0_Rect* Rect);
};

class UnkType_10b65df0_Event
{
public:
    unsigned char unk_00[0x08];
    UnkType_10b65df0_Source* unk_08;
};

class UnkType_10b65df0_Info
{
public:
    unsigned char unk_00[0x16];
    UnkType_10b65df0_Point unk_16;
};

class UnkType_10b65df0_Owner
{
public:
    UnkType_10b65df0_Info* Unk_10ad4770();
};

class UnkType_10b65df0
{
public:
    void Unk_10b65d80(UnkType_10b65df0_Point* Point);
    void Unk_10b65df0(UnkType_10b65df0_Event* Event);

private:
    UnkType_10b65df0_Owner* unk_00;
    unsigned char unk_04[0x18 - 0x04];
    bool unk_18;
};

// UnkType_10b65df0::Unk_10b65df0
void UnkType_10b65df0::Unk_10b65df0(UnkType_10b65df0_Event* Event)
{
    if ( unk_18 )
    {
        UnkType_10b65df0_Source* Source = Event->unk_08;
        UnkType_10b65df0_Point Origin = unk_00->Unk_10ad4770()->unk_16;
        UnkType_10b65df0_Rect Rect;
        Rect.unk_00 = 0;
        Rect.unk_02 = 0;
        Rect.unk_04 = 0;
        Rect.unk_06 = 0;
        Source->VirtualSlot4(&Rect);
        UnkType_10b65df0_Point Point;
        Point.unk_00 = Origin.unk_00;
        Point.unk_02 = Rect.unk_04 - 5;
        Unk_10b65d80(&Point);
    }
}
