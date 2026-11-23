// campaign_global_1122da60.h -- the global at VA 0x1122da60, a string of wide characters (data,
// count and capacity). Name and type invented from its uses.
#ifndef CAMPAIGN_GLOBAL_1122DA60_H
#define CAMPAIGN_GLOBAL_1122DA60_H

class UnkType_1122da60
{
public:
    // guess: the text, or L"" when empty (an inline accessor)
    const unsigned short* operator*() const
    {
        return unk_04 ? unk_00 : L"";
    }

    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

extern UnkType_1122da60 GUnk_1122da60;

#endif
