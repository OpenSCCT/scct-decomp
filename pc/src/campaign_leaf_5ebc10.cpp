// campaign_leaf_5ebc10.cpp -- free function at VA 0x10eebc10: when the global at VA 0x11321b30 is set,
// deletes the object it points to through its virtual destructor and clears the global. All names
// are invented.

class UnkType_11321b30
{
public:
    virtual ~UnkType_11321b30();
};

extern UnkType_11321b30* GUnk_11321b30;

// Unk_10eebc10
void Unk_10eebc10()
{
    if ( GUnk_11321b30 )
    {
        delete GUnk_11321b30;
        GUnk_11321b30 = 0;
    }
}
