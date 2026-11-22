// campaign_leaf_32e250.cpp -- a member function at VA 0x10c2e250: when its argument is not zero it
// passes a reference to it to the member at VA 0x10c2e1b0 of the object at 0x28. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10c2e1b0
{
public:
    void Unk_10c2e1b0(void* const& Item);
};

class UnkType_10c2e250
{
public:
    void Unk_10c2e250(void* Item);

private:
    unsigned char unk_00[0x28];
    UnkType_10c2e1b0 unk_28;
};

// UnkType_10c2e250::Unk_10c2e250
void UnkType_10c2e250::Unk_10c2e250(void* Item)
{
    if ( Item )
    {
        unk_28.Unk_10c2e1b0(Item);
    }
}
