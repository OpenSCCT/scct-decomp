// campaign_leaf_5ebeb0.cpp -- free function at VA 0x10eebeb0: when the global at VA 0x11321b34 is set,
// deletes the object it points to through its virtual destructor and clears the global. All names
// are invented.

class UnkType_11321b34
{
public:
    virtual ~UnkType_11321b34();
};

extern UnkType_11321b34* GUnk_11321b34;

// Unk_10eebeb0
void Unk_10eebeb0()
{
    if ( GUnk_11321b34 )
    {
        delete GUnk_11321b34;
        GUnk_11321b34 = 0;
    }
}
