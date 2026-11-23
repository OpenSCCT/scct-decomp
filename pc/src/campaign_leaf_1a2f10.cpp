// campaign_leaf_1a2f10.cpp -- thiscall method at VA 0x10aa2f10 taking a target. When the queue at
// 0xf80 (inside the member at 0xaf0) is empty it returns false. Otherwise it passes the queue's
// front entry to the target's method at VA 0x10b03840, calls the member's method at VA 0x10aa2630
// and returns true. The class, method and member names are invented; the queue is the compiler's
// library.

#include <deque>

class UnkType_10aa2f10_Entry
{
public:
    virtual void VirtualSlot0();

    char unk_4;
    char unk_5;
    int unk_8;
};

class UnkType_10aa2f10_Target
{
public:
    void Unk_10b03840(const UnkType_10aa2f10_Entry& Entry);
};

class UnkType_10aa2f10_Channel
{
public:
    // UnkType_10aa2f10_Channel::Unk_SendFront
    void Unk_SendFront(UnkType_10aa2f10_Target* Target)
    {
        if ( !unk_490.empty() )
        {
            Target->Unk_10b03840(unk_490.front());
        }
        Unk_10aa2630();
    }

    void Unk_10aa2630();

    char unk_000[0x490];
    std::deque<UnkType_10aa2f10_Entry> unk_490;
};

class UnkType_10aa2f10
{
public:
    bool Unk_10aa2f10(UnkType_10aa2f10_Target* Target);

private:
    char unk_000[0xaf0];
    UnkType_10aa2f10_Channel unk_af0;
};

// UnkType_10aa2f10::Unk_10aa2f10
bool UnkType_10aa2f10::Unk_10aa2f10(UnkType_10aa2f10_Target* Target)
{
    if ( !unk_af0.unk_490.empty() )
    {
        unk_af0.Unk_SendFront(Target);
        return true;
    }
    return false;
}
