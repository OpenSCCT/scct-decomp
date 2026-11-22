// campaign_leaf_749330.cpp -- one function at file offset 0x749330, preferred VA 0x11049330. It
// parses an optionally negative decimal integer from the start of a string and returns it, or 0
// for an empty string; it stops at the first character that is not a digit. It has no this
// pointer. The function and parameter names are invented; the offset and the bytes are the
// binary's.

// Unk_11049330
int Unk_11049330(const char* Text)
{
    const char* Cursor;
    int Negative;
    int Value;

    Cursor = Text;
    Value = 0;
    if ( *Text == 0 )
    {
        return 0;
    }
    if ( *Text == '-' )
    {
        Negative = 1;
        Cursor = Text + 1;
    }
    else
    {
        Negative = 0;
    }
    while ( *Cursor >= '0' && *Cursor <= '9' )
    {
        Value = Value * 10 + *Cursor - '0';
        Cursor++;
    }
    if ( Negative )
    {
        Value = -Value;
    }
    return Value;
}
