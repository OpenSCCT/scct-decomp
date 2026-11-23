// campaign_leaf_48f580.cpp -- thiscall method at VA 0x10d8f580. For each of its parts at 0x44,
// 0x68, 0x78 and 0x80 in turn: with no target it passes the value to the part's method at
// 0x10d9d5c0, and when the target is that part it passes the value to the target and returns.
// A target that is none of them goes to its own method at 0x10da0990 with the value. The class,
// method and parameter names are invented.

class UnkType_10d8f580_Part
{
public:
    void Unk_10d9d5c0(int Value);
};

class UnkType_10d8f580_Part44 : public UnkType_10d8f580_Part
{
    unsigned char unk_0[0x24];
};

class UnkType_10d8f580_Part68 : public UnkType_10d8f580_Part
{
    unsigned char unk_0[0x10];
};

class UnkType_10d8f580_Part78 : public UnkType_10d8f580_Part
{
    unsigned char unk_0[0x8];
};

class UnkType_10d8f580
{
public:
    void Unk_10d8f580(UnkType_10d8f580_Part* Target, int Value);
    void Unk_10da0990(UnkType_10d8f580_Part* Target, int Value);

private:
    unsigned char unk_0[0x44];
    UnkType_10d8f580_Part44 unk_44;
    UnkType_10d8f580_Part68 unk_68;
    UnkType_10d8f580_Part78 unk_78;
    UnkType_10d8f580_Part unk_80;
};

// UnkType_10d8f580::Unk_10d8f580
void UnkType_10d8f580::Unk_10d8f580(UnkType_10d8f580_Part* Target, int Value)
{
    if ( Target == 0 )
    {
        unk_44.Unk_10d9d5c0(Value);
    }
    if ( Target == &unk_44 )
    {
        unk_44.Unk_10d9d5c0(Value);
        return;
    }
    if ( Target == 0 )
    {
        unk_68.Unk_10d9d5c0(Value);
    }
    if ( Target == &unk_68 )
    {
        unk_68.Unk_10d9d5c0(Value);
        return;
    }
    if ( Target == 0 )
    {
        unk_78.Unk_10d9d5c0(Value);
    }
    if ( Target == &unk_78 )
    {
        unk_78.Unk_10d9d5c0(Value);
        return;
    }
    if ( Target == 0 )
    {
        unk_80.Unk_10d9d5c0(Value);
    }
    if ( Target == &unk_80 )
    {
        unk_80.Unk_10d9d5c0(Value);
        return;
    }
    Unk_10da0990(Target, Value);
}
