// campaign_leaf_5ec0f0.cpp -- free function at VA 0x10eec0f0: when the global at VA 0x11321b38 is set,
// deletes the object it points to through its virtual destructor and clears the global. All names
// are invented.

class UnkType_11321b38
{
public:
    virtual ~UnkType_11321b38();
};

extern UnkType_11321b38* GUnk_11321b38;

// Unk_10eec0f0
void Unk_10eec0f0()
{
    if ( GUnk_11321b38 )
    {
        delete GUnk_11321b38;
        GUnk_11321b38 = 0;
    }
}
