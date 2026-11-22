// campaign_leaf_5eb980.cpp -- free function at VA 0x10eeb980: when the global at VA 0x11321b2c is set,
// deletes the object it points to through its virtual destructor and clears the global. All names
// are invented.

class UnkType_11321b2c
{
public:
    virtual ~UnkType_11321b2c();
};

extern UnkType_11321b2c* GUnk_11321b2c;

// Unk_10eeb980
void Unk_10eeb980()
{
    if ( GUnk_11321b2c )
    {
        delete GUnk_11321b2c;
        GUnk_11321b2c = 0;
    }
}
