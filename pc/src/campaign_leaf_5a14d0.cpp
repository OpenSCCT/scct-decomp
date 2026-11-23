// campaign_leaf_5a14d0.cpp -- free function at VA 0x10ea14d0: when its argument is not null, calls
// the method at VA 0x10e9a2a0 on it and clears its first byte. All names are invented.

class UnkType_10e9a2a0
{
public:
    void Unk_10e9a2a0();

    char unk_00;
};

// Unk_10ea14d0
void Unk_10ea14d0(UnkType_10e9a2a0* Object)
{
    if ( Object )
    {
        Object->Unk_10e9a2a0();
        Object->unk_00 = 0;
    }
}
