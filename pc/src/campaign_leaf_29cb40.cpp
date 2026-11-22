// campaign_leaf_29cb40.cpp -- one function at file offset 0x29cb40, preferred VA 0x10b9cb40. It
// returns 0 when its argument is null or lacks bit 0x1 in its byte at offset 0x418, when the
// object at offset 0x42c exists and has a nonzero word at offset 0x790 or bit 0x10 in its byte at
// offset 0x410, or when the byte at offset 0x868 is nonzero; otherwise 1. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkType_10b9cb40_Item
{
public:
    unsigned char unk_0[0x410];
    unsigned char unk_410;
    unsigned char unk_411[0x418 - 0x411];
    unsigned char unk_418;
    unsigned char unk_419[0x790 - 0x419];
    int unk_790;
};

class UnkType_10b9cb40
{
public:
    unsigned char unk_0[0x42c];
    UnkType_10b9cb40_Item* unk_42c;
    unsigned char unk_430[0x868 - 0x430];
    unsigned char unk_868;

    int Unk_10b9cb40(UnkType_10b9cb40_Item* Other);
};

// UnkType_10b9cb40::Unk_10b9cb40
int UnkType_10b9cb40::Unk_10b9cb40(UnkType_10b9cb40_Item* Other)
{
    int Result = 1;
    if ( !Other )
    {
        return 0;
    }
    if ( Other->unk_418 & 1 )
    {
        if ( unk_42c && ( unk_42c->unk_790 || ( unk_42c->unk_410 & 0x10 ) ) )
        {
            Result = 0;
        }
        if ( unk_868 )
        {
            Result = 0;
        }
    }
    else
    {
        Result = 0;
    }
    return Result;
}
